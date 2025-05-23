/* SPDX-FileCopyrightText: 2010-2022 Blender Authors
 *
 * SPDX-License-Identifier: GPL-2.0-or-later */

/** \file
 * \ingroup collada
 */

#include "COLLADAFWMatrix.h"
#include "COLLADAFWRotate.h"
#include "COLLADAFWScale.h"
#include "COLLADAFWTranslate.h"

#include "TransformReader.h"

#include "BLI_math_matrix.h"
#include "BLI_math_rotation.h"

TransformReader::TransformReader(UnitConverter *conv) : unit_converter(conv)
{
  /* pass */
}

void TransformReader::get_node_mat(float mat[4][4],
                                   COLLADAFW::Node *node,
                                   std::map<COLLADAFW::UniqueId, Animation> *animation_map,
                                   Object *ob)
{
  get_node_mat(mat, node, animation_map, ob, nullptr);
}

void TransformReader::get_node_mat(float mat[4][4],
                                   COLLADAFW::Node *node,
                                   std::map<COLLADAFW::UniqueId, Animation> *animation_map,
                                   Object *ob,
                                   float parent_mat[4][4])
{
  float cur[4][4];
  float copy[4][4];

  unit_m4(mat);

  for (uint i = 0; i < node->getTransformations().getCount(); i++) {

    COLLADAFW::Transformation *tm = node->getTransformations()[i];
    COLLADAFW::Transformation::TransformationType type = tm->getTransformationType();

    switch (type) {
      case COLLADAFW::Transformation::MATRIX:
        /* When matrix AND Trans/Rot/Scale are defined for a node,
         * then this is considered as redundant information.
         * So if we find a Matrix we use that and return. */
        dae_matrix_to_mat4(tm, mat);
        if (parent_mat) {
          mul_m4_m4m4(mat, parent_mat, mat);
        }
        return;
      case COLLADAFW::Transformation::TRANSLATE:
        dae_translate_to_mat4(tm, cur);
        break;
      case COLLADAFW::Transformation::ROTATE:
        dae_rotate_to_mat4(tm, cur);
        break;
      case COLLADAFW::Transformation::SCALE:
        dae_scale_to_mat4(tm, cur);
        break;
      case COLLADAFW::Transformation::LOOKAT:
        fprintf(stderr, "|!     LOOKAT transformations are not supported yet.\n");
        break;
      case COLLADAFW::Transformation::SKEW:
        fprintf(stderr, "|!     SKEW transformations are not supported yet.\n");
        break;
    }

    copy_m4_m4(copy, mat);
    mul_m4_m4m4(mat, copy, cur);

    if (animation_map) {
      /* AnimationList that drives this Transformation */
      const COLLADAFW::UniqueId &anim_list_id = tm->getAnimationList();

      /* store this so later we can link animation data with ob */
      Animation anim = {ob, node, tm};
      (*animation_map)[anim_list_id] = anim;
    }
  }

  if (parent_mat) {
    mul_m4_m4m4(mat, parent_mat, mat);
  }
}

void TransformReader::dae_rotate_to_mat4(COLLADAFW::Transformation *tm, float m[4][4])
{
  COLLADAFW::Rotate *ro = (COLLADAFW::Rotate *)tm;
  COLLADABU::Math::Vector3 &axis = ro->getRotationAxis();
  const float angle = float(DEG2RAD(ro->getRotationAngle()));
  const float ax[] = {float(axis[0]), float(axis[1]), float(axis[2])};
#if 0
  float quat[4];
  axis_angle_to_quat(quat, axis, angle);
  quat_to_mat4(m, quat);
#endif
  axis_angle_to_mat4(m, ax, angle);
}

void TransformReader::dae_translate_to_mat4(COLLADAFW::Transformation *tm, float m[4][4])
{
  COLLADAFW::Translate *tra = (COLLADAFW::Translate *)tm;
  COLLADABU::Math::Vector3 &t = tra->getTranslation();

  unit_m4(m);

  m[3][0] = float(t[0]);
  m[3][1] = float(t[1]);
  m[3][2] = float(t[2]);
}

void TransformReader::dae_scale_to_mat4(COLLADAFW::Transformation *tm, float m[4][4])
{
  COLLADABU::Math::Vector3 &s = ((COLLADAFW::Scale *)tm)->getScale();
  float size[3] = {float(s[0]), float(s[1]), float(s[2])};
  size_to_mat4(m, size);
}

void TransformReader::dae_matrix_to_mat4(COLLADAFW::Transformation *tm, float m[4][4])
{
  UnitConverter::dae_matrix_to_mat4_(m, ((COLLADAFW::Matrix *)tm)->getMatrix());
}

void TransformReader::dae_translate_to_v3(COLLADAFW::Transformation *tm, float v[3])
{
  dae_vector3_to_v3(((COLLADAFW::Translate *)tm)->getTranslation(), v);
}

void TransformReader::dae_scale_to_v3(COLLADAFW::Transformation *tm, float v[3])
{
  dae_vector3_to_v3(((COLLADAFW::Scale *)tm)->getScale(), v);
}

void TransformReader::dae_vector3_to_v3(const COLLADABU::Math::Vector3 &v3, float v[3])
{
  v[0] = v3.x;
  v[1] = v3.y;
  v[2] = v3.z;
}
