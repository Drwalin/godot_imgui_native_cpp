#ifndef GODOT_IMGUI_NATIVE_GODOT_IMGUI_HPP
#define GODOT_IMGUI_NATIVE_GODOT_IMGUI_HPP

#include <cstdint>

#include <memory>
#include <chrono>
#include <unordered_map>

#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/variant/packed_byte_array.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/shader.hpp>
#include <godot_cpp/classes/shader_material.hpp>

#include "../../imgui/imgui.h"

using namespace godot;

class GodotImGui : public Node2D
{
	GDCLASS(GodotImGui, Node2D)
public:
	GodotImGui();
	static void _bind_methods();
	
	void _enter_tree() override;
	void _exit_tree() override;
	void _process(double_t dt) override;
	void _notification(int what);
	virtual void _input(const Ref<InputEvent> &event) override;
	
	void DisableInput();
	void EnableInput();
	bool IsInputEnabled();
	
	Texture2D *GetFontTexture();
	
	struct FontSizePair {
		std::string fontName = "";
		String filePath = "";
		float size;
	};
	ImFont *LoadFont(const FontSizePair &info);
	ImFont *LoadFont(const String &path, float sizePixels);
	int64_t GetFont(const String &path, float sizePixels);
	
	
public: // Dear ImGui
	void ImGui_Impl_Init();
	void ImGui_Impl_Shutdown();
	void ImGui_Impl_NewFrame();
	void ImGui_Impl_RenderDrawData(ImDrawData* draw_data);
	void ImGui_Impl_ProcessEvent(InputEvent *event);

	// Use if you want to reset your rendering device without losing Dear ImGui state.
	void ImGui_Impl_InitFonts();
	
	void ImGui_Impl_BeginFrame();
	void ImGui_Impl_EndFrame();
	
	void ImGui_Impl_UpdateMouseCursor();
	
public: // ImGui bindings
	static void Bind_ImGui();
	static void Bind_EnumConstants();
	
private:
	Ref<Texture2D> fontTexture;
	
	ImGuiContext *imGuiContext = nullptr;
	
	bool hasFrameBegun = false;
	
	std::chrono::steady_clock::time_point prevFrameStart = std::chrono::steady_clock::now();
	
	bool useInput = true;
	
	std::unordered_map<std::string, ImFont *> fontsCache;
	std::vector<FontSizePair> fontsToLoad;
	bool rebuildFonts = true;
	
	std::string forceLoadSettings;
	
private:
	
	Control *GetNextChild();
	void ClearChildren();
	
private:
	Ref<Shader> shader;
	Ref<ShaderMaterial> material;
	
	PackedInt32Array indices;
	PackedVector2Array vertices;
	PackedColorArray colors;
	PackedVector2Array uvs;
	
	GodotImGui *godotImgui = nullptr;
	
	int nextFreeChild = 0;
};
#endif
