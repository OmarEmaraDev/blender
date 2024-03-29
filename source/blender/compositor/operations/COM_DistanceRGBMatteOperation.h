/* SPDX-FileCopyrightText: 2011 Blender Authors
 *
 * SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#include "COM_MultiThreadedOperation.h"

namespace blender::compositor {

/**
 * this program converts an input color to an output value.
 * it assumes we are in sRGB color space.
 */
class DistanceRGBMatteOperation : public MultiThreadedOperation {
 protected:
  const NodeChroma *settings_;

  virtual float calculate_distance(const float key[4], const float image[4]);

 public:
  DistanceRGBMatteOperation();

  void set_settings(const NodeChroma *node_chroma)
  {
    settings_ = node_chroma;
  }

  void update_memory_buffer_partial(MemoryBuffer *output,
                                    const rcti &area,
                                    Span<MemoryBuffer *> inputs) override;
};

}  // namespace blender::compositor
