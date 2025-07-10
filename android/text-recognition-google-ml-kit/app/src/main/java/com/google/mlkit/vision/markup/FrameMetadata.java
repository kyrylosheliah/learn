
package com.google.mlkit.vision.markup;

/** Describing a frame info. */
public class FrameMetadata {

  public final int width;
  public final int height;
  public final int rotation;

  public FrameMetadata(int width, int height, int rotation) {
    this.width = width;
    this.height = height;
    this.rotation = rotation;
  }
}
