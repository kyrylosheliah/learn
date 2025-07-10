package org.sdase.submission.documentscanner.utils;

import android.graphics.PointF;
import org.opencv.core.Point;

public class PointUtil {

    /**
     * converts an OpenCV point to Android point
     *
     * @return Android point
     */
    public static PointF toPointF(Point point) {
        return new PointF((float) point.x, (float) point.y);
    }

    /**
     * calculates the distance between 2 OpenCV points
     *
     * @param point2 the 2nd OpenCV point
     * @return the distance between this point and the 2nd point
     */
    public static double distance(Point point1, Point point2) {
        return Math.sqrt(Math.pow(point2.x - point1.x, 2) + Math.pow(point2.y - point1.y, 2));
    }

    /**
     * offset the OpenCV point by (dx, dy)
     *
     * @param dx horizontal offset
     * @param dy vertical offset
     * @return the OpenCV point after moving it (dx, dy)
     */
    public static Point move(Point point, double dx, double dy) {
        return new Point(point.x + dx, point.y + dy);
    }

    /**
     * converts an Android point to OpenCV point
     *
     * @return OpenCV point
     */
    public static Point toOpenCVPoint(PointF pointF) {
        return new Point(pointF.x, pointF.y);
    }

    /**
     * multiply an Android point by magnitude
     *
     * @return Android point after multiplying by magnitude
     */
    public static PointF multiply(PointF pointF, float magnitude) {
        return new PointF(magnitude * pointF.x, magnitude * pointF.y);
    }

    /**
     * offset the Android point by (dx, dy)
     *
     * @param dx horizontal offset
     * @param dy vertical offset
     * @return the Android point after moving it (dx, dy)
     */
    public static PointF move(PointF pointF, float dx, float dy) {
        PointF test = new PointF(pointF.x + dx, pointF.y + dy);
        return new PointF(pointF.x + dx, pointF.y + dy);
    }

    /**
     * calculates the distance between 2 Android points
     *
     * @param pointF2 the 2nd Android point
     * @return the distance between this point and the 2nd point
     */
    public static float distance(PointF pointF1, PointF pointF2) {
        return (float) Math.sqrt(Math.pow(pointF2.x - pointF1.x, 2) + Math.pow(pointF2.y - pointF1.y, 2));
    }

}