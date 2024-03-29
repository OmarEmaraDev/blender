/* SPDX-FileCopyrightText: 2011 Blender Authors
 *
 * SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#include "COM_MultiThreadedOperation.h"

namespace blender::compositor {

class DespeckleOperation : public MultiThreadedOperation {
 private:
  constexpr static int IMAGE_INPUT_INDEX = 0;
  constexpr static int FACTOR_INPUT_INDEX = 1;

  float threshold_;
  float threshold_neighbor_;

  // int filter_width_;
  // int filter_height_;

 public:
  DespeckleOperation();

  void set_threshold(float threshold)
  {
    threshold_ = threshold;
  }
  void set_threshold_neighbor(float threshold)
  {
    threshold_neighbor_ = threshold;
  }

  void get_area_of_interest(int input_idx, const rcti &output_area, rcti &r_input_area) override;
  void update_memory_buffer_partial(MemoryBuffer *output,
                                    const rcti &area,
                                    Span<MemoryBuffer *> inputs) override;
};

}  // namespace blender::compositor
