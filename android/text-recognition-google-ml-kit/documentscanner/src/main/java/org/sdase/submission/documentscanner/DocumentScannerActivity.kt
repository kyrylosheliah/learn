package org.sdase.submission.documentscanner

import android.annotation.SuppressLint
import android.app.Activity
import android.content.Intent
import android.content.SharedPreferences
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.graphics.Rect
import android.net.Uri
import android.os.Bundle
import android.os.Environment
import android.provider.MediaStore
import android.provider.OpenableColumns
import android.util.DisplayMetrics
import android.widget.ImageButton
import androidx.appcompat.app.AppCompatActivity
import org.opencv.android.OpenCVLoader
import org.opencv.android.Utils
import org.opencv.core.CvType
import org.opencv.core.Mat
import org.opencv.core.MatOfPoint2f
import org.opencv.core.Point
import org.opencv.core.Size
import org.opencv.imgcodecs.Imgcodecs
import org.opencv.imgproc.Imgproc
import org.sdase.submission.documentscanner.constants.DocumentScannerExtra
import org.sdase.submission.documentscanner.models.Quad
import org.sdase.submission.documentscanner.ui.ImageCropView
import org.sdase.submission.documentscanner.utils.FileUtil
import org.sdase.submission.documentscanner.utils.PointUtil
import java.io.File
import java.io.FileOutputStream
import java.text.SimpleDateFormat
import java.util.Date
import java.util.Locale
import kotlin.math.min


/**
 * This class contains the main document scanner code. It opens the camera, lets the user take a
 * photo of a document (homework paper, business card, etc.), detects document corners, allows user
 * to make adjustments to the detected corners, depending on options, and saves the cropped
 * document. It allows the user to do this for 1 or more documents.
 *
 * @constructor creates document scanner activity
 */
class DocumentScannerActivity : AppCompatActivity() {
    /** @property letUserAdjustCrop whether or not to let user move automatically detected corners */
    private var letUserAdjustCrop = true

    private val cropperOffsetWhenCornersNotFound = 100.0

    private lateinit var originalPhotoUri: Uri

    private lateinit var fileUtil: FileUtil

    @Suppress("DEPRECATION")
    /** @property screenBounds the screen bounds (used to get screen width and height) */
    private fun screenBounds(): Rect {
        // currentWindowMetrics was added in Android R
        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.R) {
            return windowManager.currentWindowMetrics.bounds
        }
        // fall back to get screen width and height if using a version before Android R
        val displayMetrics = DisplayMetrics()
        windowManager.defaultDisplay.getMetrics(displayMetrics)
        return Rect(0, 0, displayMetrics.widthPixels, displayMetrics.heightPixels)
    }

    /** @property imageView container with original photo and cropper */
    private lateinit var imageView: ImageCropView

    /**
     * This function adds an on click listener to the button. It makes the button not clickable, calls
     * the on click function, and then makes the button clickable. This prevents the on click function
     * from being called while it runs.
     *
     * @param onClick the click event handler
     */
    private fun imageButtonOnClickOverride(imageButton: ImageButton, onClick: () -> Unit) {
        imageButton.setOnClickListener {
            imageButton.isClickable = false
            onClick()
            imageButton.isClickable = true
        }
    }

    private fun getOpenCVImageMat() : Mat? {
        try {
            val fileName = fileUtil.getPath(originalPhotoUri)
            return Imgcodecs.imread(fileName)
             /*
            val bmpFactoryOptions = BitmapFactory.Options();
            bmpFactoryOptions.inPreferredConfig = Bitmap.Config.ARGB_8888;
            val bmp = MediaStore.Images.Media.getBitmap(
                    this.contentResolver, originalPhotoUri);
            return Mat(bmp.width, bmp.height, CvType.CV_8UC4)*/
        } catch (e: Exception) {
            finishIntentWithError("Image file not found")
            return null
        }
    }

    private fun tryLoadOpenCV() {
        try {
            // load OpenCV
            OpenCVLoader.initDebug()
        } catch (exception: Exception) {
            finishIntentWithError("error starting OpenCV: ${exception.message}")
        }
    }

    /**
     * called when activity is created
     *
     * @param savedInstanceState persisted data that maintains state
     */
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        tryLoadOpenCV()

        try {
            // validate letUserAdjustCrop option, and update default if user sets it
            intent.extras?.getBoolean(DocumentScannerExtra.EXTRA_LET_USER_ADJUST_CROP)?.let {
                letUserAdjustCrop = it
            }
            if (letUserAdjustCrop == null) {
                throw Exception("${DocumentScannerExtra.EXTRA_LET_USER_ADJUST_CROP} not defined")
            }
        } catch (exception: Exception) {
            finishIntentWithError("invalid extra: ${exception.message}")
            return
        }

        try {
            // validate letUserAdjustCrop option, and update default if user sets it
            intent.extras?.getString(MediaStore.EXTRA_OUTPUT)?.let {
                originalPhotoUri = Uri.parse(it)
            }
            if (originalPhotoUri == null) {
                throw Exception("${MediaStore.EXTRA_OUTPUT} not defined")
            }
        } catch (exception: Exception) {
            finishIntentWithError("invalid extra: ${exception.message}")
            return
        }

        fileUtil = FileUtil(this)

        // Show cropper, accept crop button, add new document button, and
        // retake photo button. Since we open the camera in a few lines, the user
        // doesn't see this until they finish taking a photo
        setContentView(R.layout.activity_image_crop)
        imageView = findViewById(R.id.image_view)

        // set click event handlers for new document button, accept and crop document button,
        // and retake document photo button
        val cropOkButton: ImageButton = findViewById(R.id.crop_ok_button)
        val cropBackButton: ImageButton = findViewById(R.id.crop_back_button)
        imageButtonOnClickOverride(cropOkButton) { cropDocumentAndFinishIntent() }
        imageButtonOnClickOverride(cropBackButton) { finishIntentWithCancel("Crop cancelled") }

        val image: Mat = getOpenCVImageMat()!!
        // convert image to RGB color space since OpenCV reads it using BGR color space
        Imgproc.cvtColor(image, image, Imgproc.COLOR_RGB2BGR)
        // convert image matrix to bitmap
        val bitmap = Bitmap.createBitmap(image.cols(), image.rows(), Bitmap.Config.ARGB_8888)
        Utils.matToBitmap(image, bitmap)
        val photo: Bitmap = bitmap

        // get document corners by detecting them, or falling back to photo corners with
        // slight margin if we can't find the corners
        val corners =
                try {
                    val (topLeft, topRight, bottomLeft, bottomRight) = getDocumentCorners(photo)
                    Quad(topLeft, topRight, bottomRight, bottomLeft)
                } catch (exception: Exception) {
                    finishIntentWithError("unable to get document corners: ${exception.message}")
                    return
                }

        // user is allowed to move corners to make corrections
        try {
            // set preview image height based off of photo dimensions
            imageView.setImagePreviewHeight(photo, screenBounds().width())
            // display original photo, so user can adjust detected corners
            imageView.setImageBitmap(photo)
            // display cropper, and allow user to move corners
            imageView.setCropper(corners)
        } catch (exception: Exception) {
            finishIntentWithError("unable get image preview ready: ${exception.message}")
        }
        if (!letUserAdjustCrop) {
            imageView.initCropper()
            // user isn't allowed to move corners, so accept automatically detected corners
            // create cropped document image, and return file path
            cropDocumentAndFinishIntent(corners)
        }
    }

    /**
     * called when we return to activity (user switches to another app and then returns for example)
     */
    override fun onResume() {
        super.onResume()
        tryLoadOpenCV()
        imageView.initCropper()
    }

    /**
     * Pass in a photo of a document, and get back 4 corner points (top left, top right, bottom right,
     * bottom left). This tries to detect document corners, but falls back to photo corners with
     * slight margin in case we can't detect document corners.
     *
     * @param photo the original photo with a rectangular document
     * @return a List of 4 OpenCV points (document corners)
     */
    private fun getDocumentCorners(photo: Bitmap): List<Point> {
        val cornerPoints: List<Point>? = DocumentDetector().findDocumentCorners(photo)
        // if cornerPoints is null then default the corners to the photo bounds with a margin
        return cornerPoints
                ?: listOf(
                        PointUtil.move(Point(0.0, 0.0), cropperOffsetWhenCornersNotFound, cropperOffsetWhenCornersNotFound),
                        PointUtil.move(Point(0.0, 0.0), -cropperOffsetWhenCornersNotFound, cropperOffsetWhenCornersNotFound),
                        PointUtil.move(Point(0.0, 0.0), cropperOffsetWhenCornersNotFound, -cropperOffsetWhenCornersNotFound),
                        PointUtil.move(Point(0.0, 0.0), -cropperOffsetWhenCornersNotFound, -cropperOffsetWhenCornersNotFound),
                )
    }

    /**
     * This crops original document photo, saves cropped document photo, deletes original document
     * photo, and returns cropped document photo file path. It repeats that for all document photos.
     */
    private fun cropDocumentAndFinishIntent() {
        cropDocumentAndFinishIntent(null);
    }
    private fun cropDocumentAndFinishIntent(imageNativeCorners: Quad?) {
        val corners :Quad;
        if (imageNativeCorners == null) {
            corners = imageView.corners
        } else {
            corners = imageNativeCorners
        }
        val croppedImage: Bitmap =
                try {
                    // read image with OpenCV
                    val image : Mat = getOpenCVImageMat()!!
                    // convert image to RGB color space since OpenCV reads it using BGR color space
                    Imgproc.cvtColor(image, image, Imgproc.COLOR_RGB2BGR)
                    // convert top left, top right, bottom right, and bottom left document corners from
                    // Android points to OpenCV points
                    val tLC = PointUtil.toOpenCVPoint(corners.topLeftCorner)
                    val tRC = PointUtil.toOpenCVPoint(corners.topRightCorner)
                    val bRC = PointUtil.toOpenCVPoint(corners.bottomRightCorner)
                    val bLC = PointUtil.toOpenCVPoint(corners.bottomLeftCorner)
                    // Calculate the document edge distances. The user might take a skewed photo of the
                    // document, so the top left corner to top right corner distance might not be the same
                    // as the bottom left to bottom right corner. We could take an average of the 2, but
                    // this takes the smaller of the 2. It does the same for height.
                    val width = min(PointUtil.distance(tLC, tRC), PointUtil.distance(bLC, bRC))
                    val height = min(PointUtil.distance(tLC, bLC), PointUtil.distance(tRC, bRC))
                    // create empty image matrix with cropped and warped document width and height
                    val croppedImage =
                            MatOfPoint2f(
                                    Point(0.0, 0.0),
                                    Point(width, 0.0),
                                    Point(width, height),
                                    Point(0.0, height),
                            )
                    // This crops the document out of the rest of the photo. Since the user might take a
                    // skewed photo instead of a straight on photo, the document might be rotated and
                    // skewed. This corrects that problem. output is an image matrix that contains the
                    // corrected image after this fix.
                    val output = Mat()
                    Imgproc.warpPerspective(
                            image,
                            output,
                            Imgproc.getPerspectiveTransform(MatOfPoint2f(tLC, tRC, bRC, bLC), croppedImage),
                            Size(width, height)
                    )
                    // convert output image matrix to bitmap
                    val croppedBitmap = Bitmap.createBitmap(output.cols(), output.rows(), Bitmap.Config.ARGB_8888)
                    Utils.matToBitmap(output, croppedBitmap)
                    croppedBitmap
                } catch (exception: Exception) {
                    finishIntentWithError("unable to crop image: ${exception.message}")
                    return
                }

        // delete original document photo
        // File(document.originalPhotoFilePath).delete()

        // save cropped document photo
        val croppedImageFile =
                try {
                    // use current time to make file name more unique
                    val dateTime: String = SimpleDateFormat("yyyyMMdd_HHmmss", Locale.US).format(Date())
                    // create file in pictures directory
                    val storageDir: File? = this.getExternalFilesDir(Environment.DIRECTORY_PICTURES)
                    val croppedImageFile = File.createTempFile("DOCUMENT_SCAN_${dateTime}", ".jpg", storageDir)
                    val fileOutputStream = FileOutputStream(croppedImageFile)
                    croppedImage.compress(Bitmap.CompressFormat.JPEG, 100, fileOutputStream)
                    fileOutputStream.close()
                    croppedImageFile
                } catch (exception: Exception) {
                    finishIntentWithError("unable to save cropped image: ${exception.message}")
                    return
                }

        if (croppedImageFile != null) {
            // return array of cropped document photo file paths
            val cropImageFileUri = Uri.fromFile(croppedImageFile);
            setResult(Activity.RESULT_OK, Intent().setData(cropImageFileUri));
            finish()
        }
    }

    private fun finishIntentWithCancel(errorMessage: String) {
        setResult(Activity.RESULT_CANCELED, Intent().putExtra("cancel", errorMessage))
        finish()
    }

    private fun finishIntentWithError(errorMessage: String) {
        setResult(Activity.RESULT_CANCELED, Intent().putExtra("error", errorMessage))
        finish()
    }
}
