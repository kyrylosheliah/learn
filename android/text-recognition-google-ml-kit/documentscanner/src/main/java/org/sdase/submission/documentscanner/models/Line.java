package org.sdase.submission.documentscanner.models;

import android.graphics.PointF;


public class Line {
  private final PointF from;
  private final PointF to;

  /**
   * represents a line connecting 2 Android points
   *
   * @param fromPoint the 1st point
   * @param toPoint the 2nd point
   * @constructor creates a line connecting 2 points
   */
  public Line(PointF fromPoint, PointF toPoint) {
    this.from = fromPoint;
    this.to = toPoint;
  }

  public PointF getFrom() {
    return from;
  }

  public PointF getTo() {
    return to;
  }
}

