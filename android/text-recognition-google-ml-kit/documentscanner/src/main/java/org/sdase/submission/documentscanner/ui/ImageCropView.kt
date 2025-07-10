package org.sdase.submission.documentscanner.ui

import android.annotation.SuppressLint
import android.content.Context
import android.graphics.*
import android.util.AttributeSet
import android.view.MotionEvent
import androidx.appcompat.widget.AppCompatImageView
import org.sdase.submission.documentscanner.enums.QuadCorner
import org.sdase.submission.documentscanner.models.Quad
import android.graphics.Canvas
import android.graphics.Paint
import android.graphics.PointF
import org.sdase.submission.documentscanner.models.Line

/**
 * This class contains the original document photo, and a cropper. The user can drag the corners to
 * make adjustments to the detected corners.
 *
 * @param context view context
 * @param attrs view attributes
 * @constructor creates image crop view
 */
class ImageCropView(context: Context, attrs: AttributeSet) : AppCompatImageView(context, attrs) {

  /** @property quad the 4 document corners */
  private var quad: Quad? = null
  private var cropperInitCorners: Quad? = null

  /**
   * @property prevTouchPoint keep track of where the user touches, so we know how much to move
   * corners on drag
   */
  private var prevTouchPoint: PointF? = null

  /**
   * @property closestCornerToTouch if the user touches close to the top left corner for example,
   * that corner should move on drag
   */
  private var closestCornerToTouch: QuadCorner? = null

  /** @property cropper 4 corners and connecting lines */
  private val cropper = Paint(Paint.ANTI_ALIAS_FLAG)

  private var imagePreviewHeight = height
  private var imagePreviewWidth = width

  private var imageRatio = 1.0f

  /**
   * @property ratio image container height to image height ratio used to map container to image
   * coordinates and vice versa
   */
  private val ratio: Float
    get() = imagePreviewHeight.toFloat() / drawable.intrinsicHeight.toFloat()

  /**
   * @property corners document corners in original image coordinates (original image is probably
   * bigger than the preview image)
   */
  val corners: Quad
    get() = quad!!.mapPreviewToOriginalImageCoordinates(imagePreviewBounds, ratio)

  init {
    // set cropper style
    cropper.color = Color.RED
    cropper.style = Paint.Style.FILL_AND_STROKE
    cropper.strokeWidth = 6f
  }

  /**
   * Initially the image preview height is 0. This calculates the height by using the photo
   * dimensions. It maintains the photo aspect ratio (we likely need to scale the photo down to fit
   * the preview container).
   *
   * @param photo the original photo with a rectangular document
   * @param screenWidth the device width
   */
  fun setImagePreviewHeight(photo: Bitmap, screenWidth: Int) {
    // image width to height aspect ratio
    imageRatio = photo.width.toFloat() / photo.height.toFloat()

    imagePreviewWidth = screenWidth
    val screenWidthFloat = screenWidth.toFloat()
    if (photo.height > photo.width) {
      // if user takes the photo in portrait
      imagePreviewHeight = (screenWidthFloat / imageRatio).toInt()
    } else {
      // if user takes the photo in landscape
      imagePreviewHeight = (screenWidthFloat * imageRatio).toInt()
    }

    // image container initially has a 0 height, once we calculate the height we can set it
    layoutParams.height = imagePreviewHeight

    // refresh layout after we change height
    requestLayout()
  }

  fun setCropper(cropperCorners: Quad) {
    cropperInitCorners = cropperCorners
  }
  fun initCropper() {
    // corner points are in original image coordinates, so we need to scale and move the
    // points to account for blank space (caused by photo and photo container having different
    // aspect ratios)
    if (cropperInitCorners != null) {
      quad = cropperInitCorners!!.mapOriginalToPreviewImageCoordinates(imagePreviewBounds, ratio)
    }
  }

  override fun onLayout(changed: Boolean, left: Int, top: Int, right: Int, bottom: Int) {
    super.onLayout(changed, left, top, right, bottom)
    initCropper()
  }

  /**
   * @property imagePreviewBounds image coordinates - if the image ratio is different than the image
   * container ratio then there's blank space either at the top and bottom of the image or the left
   * and right of the image
   */
  private val imagePreviewBounds: RectF
    get() {
      // image container width to height ratio
      val imageViewRatio: Float = width.toFloat() / imagePreviewHeight.toFloat()

      // image width to height ratio
      //val imageRatio = drawable.intrinsicWidth.toFloat() / drawable.intrinsicHeight.toFloat()

      var left = 0f
      var top = 0f
      var right = width.toFloat()
      var bottom = imagePreviewHeight.toFloat()

      if (imageRatio > imageViewRatio) {
        // if the image is really wide, there's blank space at the top and bottom
        val offset = (imagePreviewHeight - (width / imageRatio)) / 2
        top += offset
        bottom -= offset
      } else {
        // if the image is really tall, there's blank space at the left and right
        // it's also possible that the image ratio matches the image container ratio
        // in which case there's no blank space
        val offset = (width - (imagePreviewHeight * imageRatio)) / 2
        left += offset
        right -= offset
      }

      return RectF(left, top, right, bottom)
    }

  /**
   * This ensures that the user doesn't drag a corner outside the image
   *
   * @param point a point
   * @return true if the point is inside the image preview container, false it's not
   */
  private fun isPointInsideImage(point: PointF): Boolean {
    val bounds = imagePreviewBounds
    return point.x >= bounds.left &&
            point.y >= bounds.top &&
            point.x <= bounds.right &&
            point.y <= bounds.bottom
  }

  /**
   * This gets called constantly, and we use it to update the cropper corners
   *
   * @param canvas the image preview canvas
   */
  override fun onDraw(canvas: Canvas) {
    super.onDraw(canvas)

    if (quad !== null) {
      // draw 4 corners and connecting lines
      val pointRadius = 10f
      val quadnn = quad!!;
      // draw 4 connecting lines
      for (edge: Line in quadnn.edges) {
        canvas.drawLine(edge.from.x, edge.from.y, edge.to.x, edge.to.y, cropper)
      }
      // draw 4 corner points
      for ((_, cornerPoint: PointF) in quadnn.corners) {
        canvas.drawCircle(cornerPoint.x, cornerPoint.y, pointRadius, cropper)
      }
    }
  }

  /**
   * This gets called when the user touches, drags, and stops touching screen. We use this to figure
   * out which corner we need to move, and how far we need to move it.
   *
   * @param event the touch event
   */
  @SuppressLint("ClickableViewAccessibility")
  override fun onTouchEvent(event: MotionEvent): Boolean {
    // keep track of the touched point
    val touchPoint = PointF(event.x, event.y)

    when (event.action) {
      MotionEvent.ACTION_DOWN -> {
        // when the user touches the screen record the point, and find the closest
        // corner to the touch point
        prevTouchPoint = touchPoint
        closestCornerToTouch = quad!!.getCornerClosestToPoint(touchPoint)
      }
      MotionEvent.ACTION_UP -> {
        // when the user stops touching the screen reset these values
        prevTouchPoint = null
        closestCornerToTouch = null
      }
      MotionEvent.ACTION_MOVE -> {
        // when the user drags their finger, update the closest corner position
        val touchMoveXDistance = touchPoint.x - prevTouchPoint!!.x
        val touchMoveYDistance = touchPoint.y - prevTouchPoint!!.y
        val cornerNewPosition =
                PointF(
                        quad!!.corners[closestCornerToTouch]!!.x + touchMoveXDistance,
                        quad!!.corners[closestCornerToTouch]!!.y + touchMoveYDistance
                )

        // make sure the user doesn't drag the corner outside the image preview container
        if (isPointInsideImage(cornerNewPosition)) {
          quad!!.moveCorner(closestCornerToTouch!!, touchMoveXDistance, touchMoveYDistance)
        }

        // record the point touched, so we can use it to calculate how far to move corner
        // next time the user drags (assuming they don't stop touching the screen)
        prevTouchPoint = touchPoint

        // force refresh view
        invalidate()
      }
    }

    return true
  }
}