package org.sdase.submission.documentscanner.models;

import android.graphics.PointF;
import android.graphics.RectF;
import org.opencv.core.Point;
import org.sdase.submission.documentscanner.enums.QuadCorner;
import org.sdase.submission.documentscanner.utils.PointUtil;

import java.util.HashMap;
import java.util.Map;

public class Quad {
  public final PointF topLeftCorner;
  public final PointF topRightCorner;
  public final PointF bottomRightCorner;
  public final PointF bottomLeftCorner;
  public final Map<QuadCorner, PointF> corners;
  public final Line[] edges;

  public Quad(PointF topLeftCorner, PointF topRightCorner, PointF bottomRightCorner, PointF bottomLeftCorner) {
    this.topLeftCorner = topLeftCorner;
    this.topRightCorner = topRightCorner;
    this.bottomRightCorner = bottomRightCorner;
    this.bottomLeftCorner = bottomLeftCorner;
    this.corners = new HashMap<>();
    this.corners.put(QuadCorner.TOP_LEFT, topLeftCorner);
    this.corners.put(QuadCorner.TOP_RIGHT, topRightCorner);
    this.corners.put(QuadCorner.BOTTOM_RIGHT, bottomRightCorner);
    this.corners.put(QuadCorner.BOTTOM_LEFT, bottomLeftCorner);
    this.edges = new Line[]{
            new Line(topLeftCorner, topRightCorner),
            new Line(topRightCorner, bottomRightCorner),
            new Line(bottomRightCorner, bottomLeftCorner),
            new Line(bottomLeftCorner, topLeftCorner)
    };
  }

  public Quad(Point topLeftCorner, Point topRightCorner, Point bottomRightCorner, Point bottomLeftCorner) {
    this(PointUtil.toPointF(topLeftCorner), PointUtil.toPointF(topRightCorner), PointUtil.toPointF(bottomRightCorner), PointUtil.toPointF(bottomLeftCorner));
  }

  public QuadCorner getCornerClosestToPoint(PointF point) {
    QuadCorner smallestKey = QuadCorner.TOP_LEFT;
    PointF smallestValue = corners.get(smallestKey);
    for (HashMap.Entry<QuadCorner, PointF> entry : corners.entrySet()) {
      if (PointUtil.distance(entry.getValue(), point) < PointUtil.distance(smallestValue, point)) {
        smallestKey = entry.getKey();
        smallestValue = entry.getValue();
      }
    }
    return smallestKey;
  }

  public void moveCorner(QuadCorner corner, float dx, float dy) {
    PointF target = corners.get(corner);
    if (target != null) {
      target.offset(dx, dy);
    }
  }

  public Quad mapOriginalToPreviewImageCoordinates(RectF imagePreviewBounds, float ratio) {
    return new Quad(
            PointUtil.move(PointUtil.multiply(topLeftCorner, ratio), imagePreviewBounds.left, imagePreviewBounds.top),
            PointUtil.move(PointUtil.multiply(topRightCorner, ratio), imagePreviewBounds.left, imagePreviewBounds.top),
            PointUtil.move(PointUtil.multiply(bottomRightCorner, ratio), imagePreviewBounds.left, imagePreviewBounds.top),
            PointUtil.move(PointUtil.multiply(bottomLeftCorner, ratio), imagePreviewBounds.left, imagePreviewBounds.top)
    );
  }

  public Quad mapPreviewToOriginalImageCoordinates(RectF imagePreviewBounds, float ratio) {
    return new Quad(
            PointUtil.multiply(PointUtil.move(topLeftCorner, -imagePreviewBounds.left, -imagePreviewBounds.top), 1/ratio),
            PointUtil.multiply(PointUtil.move(topRightCorner, -imagePreviewBounds.left, -imagePreviewBounds.top), 1/ratio),
            PointUtil.multiply(PointUtil.move(bottomRightCorner, -imagePreviewBounds.left, -imagePreviewBounds.top), 1/ratio),
            PointUtil.multiply(PointUtil.move(bottomLeftCorner, -imagePreviewBounds.left, -imagePreviewBounds.top), 1/ratio)
    );
  }
}

