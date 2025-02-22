/* SPDX-FileCopyrightText: 2006 Blender Authors
 *
 * SPDX-License-Identifier: GPL-2.0-or-later */

/** \file
 * \ingroup cmpnodes
 */

#include "GPU_material.hh"

#include "COM_shader_node.hh"

#include "node_composite_util.hh"

/* **************** SEPARATE HSVA ******************** */

namespace blender::nodes::node_composite_separate_hsva_cc {

static void cmp_node_sephsva_declare(NodeDeclarationBuilder &b)
{
  b.add_input<decl::Color>("Image")
      .default_value({1.0f, 1.0f, 1.0f, 1.0f})
      .compositor_domain_priority(0);
  b.add_output<decl::Float>("H").translation_context(BLT_I18NCONTEXT_COLOR);
  b.add_output<decl::Float>("S").translation_context(BLT_I18NCONTEXT_COLOR);
  b.add_output<decl::Float>("V").translation_context(BLT_I18NCONTEXT_COLOR);
  b.add_output<decl::Float>("A").translation_context(BLT_I18NCONTEXT_COLOR);
}

using namespace blender::compositor;

class SeparateHSVAShaderNode : public ShaderNode {
 public:
  using ShaderNode::ShaderNode;

  void compile(GPUMaterial *material) override
  {
    GPUNodeStack *inputs = get_inputs_array();
    GPUNodeStack *outputs = get_outputs_array();

    GPU_stack_link(material, &bnode(), "node_composite_separate_hsva", inputs, outputs);
  }
};

static ShaderNode *get_compositor_shader_node(DNode node)
{
  return new SeparateHSVAShaderNode(node);
}

}  // namespace blender::nodes::node_composite_separate_hsva_cc

void register_node_type_cmp_sephsva()
{
  namespace file_ns = blender::nodes::node_composite_separate_hsva_cc;

  static blender::bke::bNodeType ntype;

  cmp_node_type_base(&ntype, "CompositorNodeSepHSVA", CMP_NODE_SEPHSVA_LEGACY);
  ntype.ui_name = "Separate HSVA (Legacy)";
  ntype.ui_description = "Deprecated";
  ntype.enum_name_legacy = "SEPHSVA";
  ntype.nclass = NODE_CLASS_CONVERTER;
  ntype.declare = file_ns::cmp_node_sephsva_declare;
  ntype.gather_link_search_ops = nullptr;
  ntype.get_compositor_shader_node = file_ns::get_compositor_shader_node;

  blender::bke::node_register_type(&ntype);
}

/* **************** COMBINE HSVA ******************** */

namespace blender::nodes::node_composite_combine_hsva_cc {

static void cmp_node_combhsva_declare(NodeDeclarationBuilder &b)
{
  b.add_input<decl::Float>("H")
      .min(0.0f)
      .max(1.0f)
      .compositor_domain_priority(0)
      .translation_context(BLT_I18NCONTEXT_COLOR);
  b.add_input<decl::Float>("S")
      .min(0.0f)
      .max(1.0f)
      .compositor_domain_priority(1)
      .translation_context(BLT_I18NCONTEXT_COLOR);
  b.add_input<decl::Float>("V")
      .min(0.0f)
      .max(1.0f)
      .compositor_domain_priority(2)
      .translation_context(BLT_I18NCONTEXT_COLOR);
  b.add_input<decl::Float>("A")
      .default_value(1.0f)
      .min(0.0f)
      .max(1.0f)
      .compositor_domain_priority(3)
      .translation_context(BLT_I18NCONTEXT_COLOR);
  b.add_output<decl::Color>("Image");
}

using namespace blender::compositor;

class CombineHSVAShaderNode : public ShaderNode {
 public:
  using ShaderNode::ShaderNode;

  void compile(GPUMaterial *material) override
  {
    GPUNodeStack *inputs = get_inputs_array();
    GPUNodeStack *outputs = get_outputs_array();

    GPU_stack_link(material, &bnode(), "node_composite_combine_hsva", inputs, outputs);
  }
};

static ShaderNode *get_compositor_shader_node(DNode node)
{
  return new CombineHSVAShaderNode(node);
}

}  // namespace blender::nodes::node_composite_combine_hsva_cc

void register_node_type_cmp_combhsva()
{
  namespace file_ns = blender::nodes::node_composite_combine_hsva_cc;

  static blender::bke::bNodeType ntype;

  cmp_node_type_base(&ntype, "CompositorNodeCombHSVA", CMP_NODE_COMBHSVA_LEGACY);
  ntype.ui_name = "Combine HSVA (Legacy)";
  ntype.ui_description = "Deprecated";
  ntype.enum_name_legacy = "COMBHSVA";
  ntype.nclass = NODE_CLASS_CONVERTER;
  ntype.declare = file_ns::cmp_node_combhsva_declare;
  ntype.gather_link_search_ops = nullptr;
  ntype.get_compositor_shader_node = file_ns::get_compositor_shader_node;

  blender::bke::node_register_type(&ntype);
}
