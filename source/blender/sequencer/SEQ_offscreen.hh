/* SPDX-FileCopyrightText: 2004 Blender Authors
 *
 * SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

/** \file
 * \ingroup bke
 */

#include "DNA_object_enums.h"
#include "DNA_view3d_enums.h"

#include "IMB_imbuf_types.hh"

struct GPUOffScreen;

enum eDrawType;

namespace blender::seq {
typedef struct ImBuf *(*SequencerDrawView)(struct Depsgraph *depsgraph,
                                           struct Scene *scene,
                                           struct View3DShading *shading_override,
                                           eDrawType drawtype,
                                           struct Object *camera,
                                           int width,
                                           int height,
                                           enum eImBufFlags flag,
                                           eV3DOffscreenDrawFlag draw_flags,
                                           int alpha_mode,
                                           const char *viewname,
                                           struct GPUOffScreen *ofs,
                                           struct GPUViewport *viewport,
                                           char err_out[256]);
extern SequencerDrawView sequencer_view3d_fn;
}  // namespace blender::seq
