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

using namespace godot;

class GodotImGui;

class GodotImGuiMesh : public MeshInstance2D
{
	GDCLASS(GodotImGuiMesh, MeshInstance2D)
public:
	GodotImGuiMesh();
	~GodotImGuiMesh();
	static void _bind_methods();
	
	void _ready() override;
	void _process(double_t delta) override;
	void _enter_tree() override;
	void _exit_tree() override;
	
	void ImGui_Impl_RenderDrawData(ImDrawData *drawData);
	
	Ref<ShaderMaterial> GetNewMaterial(Texture2D *texturePtr);
	
public:
	
public:
	
	Ref<ShaderMaterial> shader;
	
	GodotImGui *godotImgui = nullptr;
	Ref<ImmediateMesh> mesh;
	
	std::vector<Ref<ShaderMaterial>> materials;
	int freeMaterialId = 0;
};
#endif

