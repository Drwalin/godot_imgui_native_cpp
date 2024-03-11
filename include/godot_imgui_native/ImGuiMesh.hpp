#ifndef GODOT_IMGUI_NATIVE_GODOT_IMGUI_MESH_HPP
#define GODOT_IMGUI_NATIVE_GODOT_IMGUI_MESH_HPP

#include <cstdint>

#include <memory>
#include <chrono>
#include <vector>

#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/variant/packed_byte_array.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/immediate_mesh.hpp>
#include <godot_cpp/classes/mesh_instance2d.hpp>
#include <godot_cpp/classes/shader_material.hpp>
#include <godot_cpp/classes/canvas_item_material.hpp>
#include <godot_cpp/variant/typed_array.hpp>

#include "../../imgui/imgui.h"

class GodotImGui;

class GodotImGuiMesh : public godot::MeshInstance2D
{
	GDCLASS(GodotImGuiMesh, MeshInstance2D)
public:
	static void _bind_methods();
	
	void _ready() override;
	void _process(double_t delta) override;
	void _enter_tree() override;
	void _exit_tree() override;
	
	void ImGui_Impl_RenderDrawData(ImDrawData *drawData);
	
	godot::Ref<godot::ShaderMaterial> GetNewMaterial(godot::Texture2D *texturePtr);
	
public:
	
public:
	
	godot::Ref<godot::ShaderMaterial> shader;
	
	GodotImGui *godotImgui = nullptr;
	godot::Ref<godot::ImmediateMesh> mesh;
	
	std::vector<godot::Ref<godot::ShaderMaterial>> materials;
	int freeMaterialId = 0;
};
#endif

