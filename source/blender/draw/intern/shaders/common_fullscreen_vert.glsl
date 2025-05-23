/* SPDX-FileCopyrightText: 2015-2022 Blender Authors
 *
 * SPDX-License-Identifier: GPL-2.0-or-later */

#include "draw_fullscreen_info.hh"

VERTEX_SHADER_CREATE_INFO(draw_fullscreen)

void main()
{
  int v = gl_VertexID % 3;
  float x = -1.0f + float((v & 1) << 2);
  float y = -1.0f + float((v & 2) << 1);
  gl_Position = float4(x, y, 1.0f, 1.0f);
  uvcoordsvar = float4((gl_Position.xy + 1.0f) * 0.5f, 0.0f, 0.0f);
}
