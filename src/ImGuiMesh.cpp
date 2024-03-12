#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/rendering_server.hpp>
#include <godot_cpp/classes/display_server.hpp>
#include <godot_cpp/classes/text_server.hpp>
#include <godot_cpp/classes/engine.hpp>

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

GodotImGuiMesh::GodotImGuiMesh()
{
}

GodotImGuiMesh::~GodotImGuiMesh()
{
}

void GodotImGuiMesh::_bind_methods() {}

void GodotImGuiMesh::_enter_tree()
{
	if (Engine::get_singleton()->is_editor_hint()) {
		return;
	}
// 	shader = ResourceLoader::get_singleton()->load("res://imgui/gui_shader.gdshader");
	
// 	mat.instantiate();
	this->set_texture_filter(TEXTURE_FILTER_LINEAR);
	this->set_texture_repeat(TEXTURE_REPEAT_ENABLED);
	this->set_light_mask(0);
}

void GodotImGuiMesh::_exit_tree() {
	if (Engine::get_singleton()->is_editor_hint()) {
		return;
	}
}

void GodotImGuiMesh::_ready()
{
	if (Engine::get_singleton()->is_editor_hint()) {
		return;
	}
}

void GodotImGuiMesh::_process(double_t delta)
{
	if (Engine::get_singleton()->is_editor_hint()) {
		return;
	}
// 	godotImgui->ImGui_Impl_EndFrame();
}

void GodotImGuiMesh::ImGui_Impl_RenderDrawData(ImDrawData *draw_data)
{
	// Avoid rendering when minimized
	if (draw_data->DisplaySize.x <= 0.0f || draw_data->DisplaySize.y <= 0.0f)
		return;
	
	auto rs = RenderingServer::get_singleton();

	freeMaterialId = 0;

	// TODO: set ortographic projection matrix here if necssary

	RID selfRid = this->get_canvas_item();
	
	rs->canvas_item_clear(selfRid);
	
	for (int n = 0; n < draw_data->CmdListsCount; n++) {
		const ImDrawList *cmd_list = draw_data->CmdLists[n];

		auto cmdBuf = cmd_list->CmdBuffer;
		auto idxBuf = cmd_list->IdxBuffer;
		auto vtxBuf = cmd_list->VtxBuffer;
		
		indices.resize(idxBuf.size());
		vertices.resize(vtxBuf.size());
		colors.resize(vtxBuf.size());
		uvs.resize(vtxBuf.size());
		
		for (int i=0; i<idxBuf.size(); ++i) {
			indices[i] = idxBuf[i];
		}
		
		for (int i=0; i<vtxBuf.size(); ++i) {
			auto &v = vtxBuf[i];
			vertices[i] = {v.pos.x, v.pos.y};
			colors[i] = Color::hex(v.col);
			uvs[i] = {v.uv.x, v.uv.y};
		}

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
				
// 				mat->set_shader_parameter("scissor_test", clip);
				
				auto indicesSlice = indices.slice(pcmd->IdxOffset, pcmd->IdxOffset + pcmd->ElemCount);
				
				RID texRid;
				Texture2D *tex = (Texture2D *)(pcmd->GetTexID());
				if (tex) {
					texRid = tex->get_rid();
					rs->canvas_item_add_texture_rect(selfRid, {0,0,tex->get_size().x/3,tex->get_size().y/3}, texRid, false, {1,1,1,1});
					tex->draw(selfRid, {100, 100}, {1,0.2,0.2,1});
				}
				
				rs->canvas_item_add_triangle_array(selfRid, indicesSlice, vertices, colors, uvs, {}, {}, texRid);
				
			}
		}
	}
	
}
