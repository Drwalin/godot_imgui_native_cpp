#ifndef GODOT_IMGUI_NATIVE_GODOT_IMGUI_HPP
#define GODOT_IMGUI_NATIVE_GODOT_IMGUI_HPP

#include <cstdint>

#include <memory>
#include <chrono>

#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/variant/packed_byte_array.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/ref.hpp>

#include "../../imgui/imgui.h"

#include "ImGuiMesh.hpp"

class GodotImGui : public godot::Node
{
	GDCLASS(GodotImGui, Node)
public:
	GodotImGui();
	static void _bind_methods();
	
	void _enter_tree() override;
	void _exit_tree() override;
	void _ready() override;
	void _process(double_t delta) override;
	void _notification(int what);
	virtual void _input(const godot::Ref<godot::InputEvent> &event) override;
	virtual void _shortcut_input(const godot::Ref<godot::InputEvent> &event) override;
	virtual void _unhandled_input(const godot::Ref<godot::InputEvent> &event) override;
	virtual void _unhandled_key_input(const godot::Ref<godot::InputEvent> &event) override;
	
	void DisableInput();
	void EnableInput();
	bool IsInputEnabled();
	
public: // Dear ImGui
	void ImGui_Impl_Init();
	void ImGui_Impl_Shutdown();
	void ImGui_Impl_NewFrame();
	void ImGui_Impl_RenderDrawData(ImDrawData* draw_data);
	void ImGui_Impl_ProcessEvent(godot::InputEvent *event);

	// Use if you want to reset your rendering device without losing Dear ImGui state.
	bool ImGui_Impl_CreateDeviceObjects();
	void ImGui_Impl_InvalidateDeviceObjects();
	
	void ImGui_Impl_BeginFrame();
	void ImGui_Impl_EndFrame();
	
	void ImGui_Impl_UpdateMouseCursor();
	
private:
	
	bool hasFrameBegun = false;
	
	std::chrono::steady_clock::time_point prevFrameStart = std::chrono::steady_clock::now();
	
	bool useInput = true;
	
	GodotImGuiMesh *mesh = nullptr;
};
#endif
