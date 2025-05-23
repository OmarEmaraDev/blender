/* SPDX-FileCopyrightText: 2023 Blender Authors
 *
 * SPDX-License-Identifier: GPL-2.0-or-later */

#include "gpu_shader_create_info.hh"

GPU_SHADER_CREATE_INFO(compositor_box_mask_shared)
LOCAL_GROUP_SIZE(16, 16)
PUSH_CONSTANT(int2, domain_size)
PUSH_CONSTANT(float2, location)
PUSH_CONSTANT(float2, size)
PUSH_CONSTANT(float, cos_angle)
PUSH_CONSTANT(float, sin_angle)
SAMPLER(0, FLOAT_2D, base_mask_tx)
SAMPLER(1, FLOAT_2D, mask_value_tx)
IMAGE(0, GPU_R16F, WRITE, FLOAT_2D, output_mask_img)
COMPUTE_SOURCE("compositor_box_mask.glsl")
GPU_SHADER_CREATE_END()

GPU_SHADER_CREATE_INFO(compositor_box_mask_add)
ADDITIONAL_INFO(compositor_box_mask_shared)
DEFINE("CMP_NODE_MASKTYPE_ADD")
DO_STATIC_COMPILATION()
GPU_SHADER_CREATE_END()

GPU_SHADER_CREATE_INFO(compositor_box_mask_subtract)
ADDITIONAL_INFO(compositor_box_mask_shared)
DEFINE("CMP_NODE_MASKTYPE_SUBTRACT")
DO_STATIC_COMPILATION()
GPU_SHADER_CREATE_END()

GPU_SHADER_CREATE_INFO(compositor_box_mask_multiply)
ADDITIONAL_INFO(compositor_box_mask_shared)
DEFINE("CMP_NODE_MASKTYPE_MULTIPLY")
DO_STATIC_COMPILATION()
GPU_SHADER_CREATE_END()

GPU_SHADER_CREATE_INFO(compositor_box_mask_not)
ADDITIONAL_INFO(compositor_box_mask_shared)
DEFINE("CMP_NODE_MASKTYPE_NOT")
DO_STATIC_COMPILATION()
GPU_SHADER_CREATE_END()
