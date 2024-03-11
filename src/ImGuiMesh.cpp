#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/rendering_server.hpp>
#include <godot_cpp/classes/display_server.hpp>
#include <godot_cpp/classes/text_server.hpp>

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event_screen_touch.hpp>
#include <godot_cpp/classes/input_event_key.hpp>
#include <godot_cpp/classes/input_event_mouse.hpp>
#include <godot_cpp/classes/input_event_from_window.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/input_event_with_modifiers.hpp>
#include <godot_cpp/classes/input_event_screen_drag.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

#include "../include/godot_imgui_native/ImGui.hpp"
#include "../include/godot_imgui_native/ImGuiMesh.hpp"
#include "godot_cpp/classes/base_material3d.hpp"
#include "godot_cpp/classes/immediate_mesh.hpp"

void GodotImGuiMesh::_bind_methods() {}

void GodotImGuiMesh::_enter_tree()
{
	mesh = godot::Ref<godot::ImmediateMesh>(new godot::ImmediateMesh());
	set_mesh(mesh);
	mesh->clear_surfaces();
	shader = godot::ResourceLoader::get_singleton()->load(
		"res://imgui/gui_shader.gdshader", "ShaderMaterial");
}

void GodotImGuiMesh::_exit_tree() {}

void GodotImGuiMesh::_ready() { this->set_process_priority(0x7FFFFFFF); }

void GodotImGuiMesh::_process(double_t delta)
{
	godotImgui->ImGui_Impl_EndFrame();
}

godot::Ref<godot::ShaderMaterial>
GodotImGuiMesh::GetNewMaterial(godot::Texture2D *texturePtr)
{
	if (materials.size() <= freeMaterialId) {
		materials.resize(freeMaterialId + 1);
	}

	godot::Ref<godot::ShaderMaterial> &mat = materials[freeMaterialId];

	if (mat.is_null()) {
		mat.instantiate();
		mat->set_shader(shader);
		mat->set_shader_parameter("TEXTURE", godot::Ref(texturePtr));
	}

	return mat;
}

void GodotImGuiMesh::ImGui_Impl_RenderDrawData(ImDrawData *draw_data)
{
	// Avoid rendering when minimized
	if (draw_data->DisplaySize.x <= 0.0f || draw_data->DisplaySize.y <= 0.0f)
		return;

	mesh->clear_surfaces();
	freeMaterialId = 0;

	// TODO: set ortographic projection matrix here if necssary

	for (int n = 0; n < draw_data->CmdListsCount; n++) {
		const ImDrawList *cmd_list = draw_data->CmdLists[n];

		auto cmdBuf = cmd_list->CmdBuffer;
		auto idxBuf = cmd_list->IdxBuffer;
		auto vtxBuf = cmd_list->VtxBuffer;
		// 		auto flags = cmd_list->Flags;

		ImVec2 clip_off = draw_data->DisplayPos;
		for (int cmd_i = 0; cmd_i < cmdBuf.Size; cmd_i++) {
			const ImDrawCmd *pcmd = &(cmdBuf[cmd_i]);
			if (pcmd->UserCallback) {
				if (pcmd->UserCallback == ImDrawCallback_ResetRenderState) {
					// reset render state here
					// ImGui_ImplAllegro5_SetupRenderState(draw_data);
				} else {
					pcmd->UserCallback(cmd_list, pcmd);
				}
			} else {
				// Project scissor/clipping rectangles into framebuffer space
				ImVec2 clip_min(pcmd->ClipRect.x - clip_off.x,
								pcmd->ClipRect.y - clip_off.y);
				ImVec2 clip_max(pcmd->ClipRect.z - clip_off.x,
								pcmd->ClipRect.w - clip_off.y);
				if (clip_max.x <= clip_min.x || clip_max.y <= clip_min.y)
					continue;

				auto mat =
					GetNewMaterial((godot::Texture2D *)(pcmd->GetTexID()));
				mesh->surface_begin(
					godot::Mesh::PrimitiveType::PRIMITIVE_TRIANGLES, mat);
				godot::Vector4 clip{clip_min.x, clip_min.y, clip_max.x,
									clip_max.y};
				mat->set_shader_parameter("scissor_test", clip);

				for (int i = pcmd->IdxOffset;
					 i < pcmd->IdxOffset + pcmd->ElemCount; ++i) {
					auto &v = vtxBuf[idxBuf[i]];
					mesh->surface_set_color(godot::Color::hex(v.col));
					mesh->surface_set_uv({v.uv.x, v.uv.y});
					mesh->surface_add_vertex_2d({v.pos.x, v.pos.y});
				}
				mesh->surface_end();
			}
		}
	}
}