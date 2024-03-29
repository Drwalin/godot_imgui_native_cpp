#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/rendering_server.hpp>
#include <godot_cpp/classes/display_server.hpp>
#include <godot_cpp/classes/text_server.hpp>
#include <godot_cpp/classes/engine.hpp>

#include <godot_cpp/classes/resource_loader.hpp>

#include "../include/godot_imgui_native/ImGui.hpp"
#include "godot_cpp/classes/base_material3d.hpp"
#include "godot_cpp/classes/immediate_mesh.hpp"

Control *GodotImGui::GetNextChild()
{
	while(this->get_child_count() <= nextFreeChild) {
		auto c = memnew(Control());
		c->set_material(material->duplicate());
		add_child(c);
	}
	auto ret = (Control*)(this->get_child(nextFreeChild));
	++nextFreeChild;
	return ret;
}

void GodotImGui::ClearChildren()
{
	auto rs = RenderingServer::get_singleton();
	nextFreeChild = 0;
	for (int i=0; i<get_child_count(); ++i) {
		RID rid = ((Control *)get_child(i))->get_canvas_item();
		rs->canvas_item_clear(rid);
	}
}

void GodotImGui::ImGui_Impl_RenderDrawData(ImDrawData *draw_data)
{
	ClearChildren();
	
	if (imGuiContext == nullptr) {
		return;
	}
	
	// Avoid rendering when minimized
	if (draw_data->DisplaySize.x <= 0.0f || draw_data->DisplaySize.y <= 0.0f)
		return;
	
	auto rs = RenderingServer::get_singleton();

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
			colors[i] = {
				((v.col>> 0)&0xFF)/255.0f,
				((v.col>> 8)&0xFF)/255.0f,
				((v.col>>16)&0xFF)/255.0f,
				((v.col>>24)&0xFF)/255.0f};
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
				Vector2 clip_min(pcmd->ClipRect.x - clip_off.x,
								pcmd->ClipRect.y - clip_off.y);
				Vector2 clip_max(pcmd->ClipRect.z - clip_off.x,
								pcmd->ClipRect.w - clip_off.y);
				if (clip_max.x <= clip_min.x || clip_max.y <= clip_min.y)
					continue;
				
				Control *node = GetNextChild();
				auto mat = ((ShaderMaterial *)(node->get_material().ptr()));
				mat->set_shader_parameter("scissor_test", Vector4(clip_min.x, clip_min.y, clip_max.x, clip_max.y));
				
				RID selfRid = node->get_canvas_item();
				
				auto indicesSlice = indices.slice(pcmd->IdxOffset, pcmd->IdxOffset + pcmd->ElemCount);
				
				RID texRid;
				Texture2D *tex = (Texture2D *)(pcmd->GetTexID());
				if (tex) {
					texRid = tex->get_rid();
					mat->set_shader_parameter("TEXTURE", tex);
				}
				
				rs->canvas_item_add_triangle_array(selfRid, indicesSlice, vertices, colors, uvs, {}, {}, texRid);
				
			}
		}
	}
	
// 	rs->canvas_item_clear(get_canvas_item());
// 	fontTexture->draw(get_canvas_item(), {0,0});
}
