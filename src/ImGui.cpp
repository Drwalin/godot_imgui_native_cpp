#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/rendering_server.hpp>
#include <godot_cpp/classes/display_server.hpp>
#include <godot_cpp/classes/text_server.hpp>
#include <godot_cpp/classes/image_texture.hpp>
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

#include "../include/godot_imgui_native/ImGui.hpp"
#include "../include/godot_imgui_native/ImGuiMesh.hpp"

#define METHOD_NO_ARGS(CLASS, NAME)                                            \
	ClassDB::bind_method(D_METHOD(#NAME), &CLASS::NAME);

#define METHOD_ARGS(CLASS, NAME, ...)                                          \
	ClassDB::bind_method(D_METHOD(#NAME, __VA_ARGS__),           \
								&CLASS::NAME);

GodotImGui::GodotImGui()
{
	if (Engine::get_singleton()->is_editor_hint()) {
		return;
	}
	UtilityFunctions::print("GodotImGui::GodotImGui()");
	
	mesh = memnew(GodotImGuiMesh());
	mesh->godotImgui = this;
	this->add_child(mesh);
}

void GodotImGui::_bind_methods()
{
	METHOD_NO_ARGS(GodotImGui, EnableInput);
	METHOD_NO_ARGS(GodotImGui, DisableInput);
	METHOD_NO_ARGS(GodotImGui, IsInputEnabled);
	
	ClassDB::bind_method(D_METHOD("ImGui_NewFrame"), &GodotImGui::ImGui_Impl_BeginFrame);
}

void GodotImGui::_enter_tree()
{
	if (Engine::get_singleton()->is_editor_hint()) {
		return;
	}
	ImGui_Impl_Init();
	
	ImGui_Impl_BeginFrame();
}

void GodotImGui::_exit_tree()
{
	if (Engine::get_singleton()->is_editor_hint()) {
		return;
	}
// 	ImGui_Impl_EndFrame();
	
	ImGui_Impl_Shutdown();
	ImGui::DestroyContext();
	
	remove_child(mesh);
	delete mesh;
}

void GodotImGui::_ready()
{
	if (Engine::get_singleton()->is_editor_hint()) {
		return;
	}
	this->set_process_priority(0x80);
}

void GodotImGui::_process(double_t delta)
{
	if (Engine::get_singleton()->is_editor_hint()) {
		return;
	}
	ImGui_Impl_NewFrame();
}

void GodotImGui::_notification(int what)
{
}

void GodotImGui::DisableInput()
{
	useInput = false;
}

void GodotImGui::EnableInput()
{
	useInput = true;
}

bool GodotImGui::IsInputEnabled()
{
	return useInput;
}





void GodotImGui::_input(const Ref<InputEvent> &event)
{
	ImGui_Impl_ProcessEvent(event.ptr());
}

void GodotImGui::_shortcut_input(const Ref<InputEvent> &event)
{
	ImGui_Impl_ProcessEvent(event.ptr());
}

void GodotImGui::_unhandled_input(const Ref<InputEvent> &event)
{
	ImGui_Impl_ProcessEvent(event.ptr());
}

void GodotImGui::_unhandled_key_input(const Ref<InputEvent> &event)
{
	ImGui_Impl_ProcessEvent(event.ptr());
}





void GodotImGui::ImGui_Impl_Init()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	
	// TODO: init godot imgui here
	ImGui_Impl_InitFonts();
}

void GodotImGui::ImGui_Impl_InitFonts()
{
    ImGuiIO& io = ImGui::GetIO();
    unsigned char* pixels;
    int width, height;
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
	
	PackedByteArray _pixels;
	_pixels.resize(width*height*4);
	memcpy((void *)_pixels.ptr(), pixels, width*height*4);
	
	Ref<Image> image;
	image.instantiate();
	image->set_data(width, height, false, Image::Format::FORMAT_RGBA8, _pixels);
	
	fontTexture = ImageTexture::create_from_image(image);
	
    io.Fonts->SetTexID((ImTextureID)(intptr_t)fontTexture.ptr());
}

void GodotImGui::ImGui_Impl_Shutdown()
{
	// TODO: destroy godot imgui here
}

void GodotImGui::ImGui_Impl_NewFrame()
{
    ImGuiIO& io = ImGui::GetIO();

    // Setup display size (every frame to accommodate for window resizing)
	DisplayServer *ds = DisplayServer::get_singleton();
	
	auto s = ds->window_get_size(0);
	int w = s.width;
	int h = s.height;
    io.DisplaySize = ImVec2((float)w, (float)h);
	
	
	auto now = std::chrono::steady_clock::now();
	double dt = std::chrono::duration<double>(now-prevFrameStart).count();
	prevFrameStart = now;

    // Setup time step
    io.DeltaTime = dt;

    // Setup mouse cursor shape
    ImGui_Impl_UpdateMouseCursor();
}

ImGuiKey GodotToImGuiKeyCode(int keycode)
{
    switch (keycode)
    {
		case Key::KEY_TAB: return ImGuiKey_Tab;
		case Key::KEY_LEFT: return ImGuiKey_LeftArrow;
		case Key::KEY_RIGHT: return ImGuiKey_RightArrow;
		case Key::KEY_UP: return ImGuiKey_UpArrow;
		case Key::KEY_DOWN: return ImGuiKey_DownArrow;
		case Key::KEY_PAGEUP: return ImGuiKey_PageUp;
		case Key::KEY_PAGEDOWN: return ImGuiKey_PageDown;
		case Key::KEY_HOME: return ImGuiKey_Home;
		case Key::KEY_END: return ImGuiKey_End;
		case Key::KEY_INSERT: return ImGuiKey_Insert;
		case Key::KEY_DELETE: return ImGuiKey_Delete;
		case Key::KEY_BACKSPACE: return ImGuiKey_Backspace;
		case Key::KEY_SPACE: return ImGuiKey_Space;
		case Key::KEY_ENTER: return ImGuiKey_Enter;
		case Key::KEY_ESCAPE: return ImGuiKey_Escape;
		case Key::KEY_APOSTROPHE: return ImGuiKey_Apostrophe;
		case Key::KEY_COMMA: return ImGuiKey_Comma;
		case Key::KEY_MINUS: return ImGuiKey_Minus;
		case Key::KEY_PERIOD: return ImGuiKey_Period;
		case Key::KEY_SLASH: return ImGuiKey_Slash;
		case Key::KEY_SEMICOLON: return ImGuiKey_Semicolon;
		case Key::KEY_EQUAL: return ImGuiKey_Equal;
		case Key::KEY_BRACKETLEFT: return ImGuiKey_LeftBracket;
		case Key::KEY_BACKSLASH: return ImGuiKey_Backslash;
		case Key::KEY_BRACKETRIGHT: return ImGuiKey_RightBracket;
		case Key::KEY_ASCIITILDE: return ImGuiKey_GraveAccent;
		case Key::KEY_CAPSLOCK: return ImGuiKey_CapsLock;
		case Key::KEY_SCROLLLOCK: return ImGuiKey_ScrollLock;
		case Key::KEY_NUMLOCK: return ImGuiKey_NumLock;
		case Key::KEY_PRINT: return ImGuiKey_PrintScreen;
		case Key::KEY_PAUSE: return ImGuiKey_Pause;
		case Key::KEY_KP_0: return ImGuiKey_Keypad0;
		case Key::KEY_KP_1: return ImGuiKey_Keypad1;
		case Key::KEY_KP_2: return ImGuiKey_Keypad2;
		case Key::KEY_KP_3: return ImGuiKey_Keypad3;
		case Key::KEY_KP_4: return ImGuiKey_Keypad4;
		case Key::KEY_KP_5: return ImGuiKey_Keypad5;
		case Key::KEY_KP_6: return ImGuiKey_Keypad6;
		case Key::KEY_KP_7: return ImGuiKey_Keypad7;
		case Key::KEY_KP_8: return ImGuiKey_Keypad8;
		case Key::KEY_KP_9: return ImGuiKey_Keypad9;
		case Key::KEY_KP_PERIOD: return ImGuiKey_KeypadDecimal;
		case Key::KEY_KP_DIVIDE: return ImGuiKey_KeypadDivide;
		case Key::KEY_KP_MULTIPLY: return ImGuiKey_KeypadMultiply;
		case Key::KEY_KP_SUBTRACT: return ImGuiKey_KeypadSubtract;
		case Key::KEY_KP_ADD: return ImGuiKey_KeypadAdd;
		case Key::KEY_KP_ENTER: return ImGuiKey_KeypadEnter;
		case Key::KEY_CTRL: return ImGuiKey_LeftCtrl;
		case Key::KEY_SHIFT: return ImGuiKey_LeftShift;
		case Key::KEY_ALT: return ImGuiKey_LeftAlt;
// 		case Key::KEY_LWIN: return ImGuiKey_LeftSuper;
// 		case Key::KEY_RCTRL: return ImGuiKey_RightCtrl;
// 		case Key::KEY_RSHIFT: return ImGuiKey_RightShift;
// 		case Key::KEY_ALT: return ImGuiKey_RightAlt;
// 		case Key::KEY_RWIN: return ImGuiKey_RightSuper;
		case Key::KEY_MENU: return ImGuiKey_Menu;
		case Key::KEY_0: return ImGuiKey_0;
		case Key::KEY_1: return ImGuiKey_1;
		case Key::KEY_2: return ImGuiKey_2;
		case Key::KEY_3: return ImGuiKey_3;
		case Key::KEY_4: return ImGuiKey_4;
		case Key::KEY_5: return ImGuiKey_5;
		case Key::KEY_6: return ImGuiKey_6;
		case Key::KEY_7: return ImGuiKey_7;
		case Key::KEY_8: return ImGuiKey_8;
		case Key::KEY_9: return ImGuiKey_9;
		case Key::KEY_A: return ImGuiKey_A;
		case Key::KEY_B: return ImGuiKey_B;
		case Key::KEY_C: return ImGuiKey_C;
		case Key::KEY_D: return ImGuiKey_D;
		case Key::KEY_E: return ImGuiKey_E;
		case Key::KEY_F: return ImGuiKey_F;
		case Key::KEY_G: return ImGuiKey_G;
		case Key::KEY_H: return ImGuiKey_H;
		case Key::KEY_I: return ImGuiKey_I;
		case Key::KEY_J: return ImGuiKey_J;
		case Key::KEY_K: return ImGuiKey_K;
		case Key::KEY_L: return ImGuiKey_L;
		case Key::KEY_M: return ImGuiKey_M;
		case Key::KEY_N: return ImGuiKey_N;
		case Key::KEY_O: return ImGuiKey_O;
		case Key::KEY_P: return ImGuiKey_P;
		case Key::KEY_Q: return ImGuiKey_Q;
		case Key::KEY_R: return ImGuiKey_R;
		case Key::KEY_S: return ImGuiKey_S;
		case Key::KEY_T: return ImGuiKey_T;
		case Key::KEY_U: return ImGuiKey_U;
		case Key::KEY_V: return ImGuiKey_V;
		case Key::KEY_W: return ImGuiKey_W;
		case Key::KEY_X: return ImGuiKey_X;
		case Key::KEY_Y: return ImGuiKey_Y;
		case Key::KEY_Z: return ImGuiKey_Z;
		case Key::KEY_F1: return ImGuiKey_F1;
		case Key::KEY_F2: return ImGuiKey_F2;
		case Key::KEY_F3: return ImGuiKey_F3;
		case Key::KEY_F4: return ImGuiKey_F4;
		case Key::KEY_F5: return ImGuiKey_F5;
		case Key::KEY_F6: return ImGuiKey_F6;
		case Key::KEY_F7: return ImGuiKey_F7;
		case Key::KEY_F8: return ImGuiKey_F8;
		case Key::KEY_F9: return ImGuiKey_F9;
		case Key::KEY_F10: return ImGuiKey_F10;
		case Key::KEY_F11: return ImGuiKey_F11;
		case Key::KEY_F12: return ImGuiKey_F12;
		// TODO: When to return this ???
        // return ImGuiKey_KeypadEqual;
        default: return ImGuiKey_None;
	}
}


void GodotImGui::ImGui_Impl_RenderDrawData(ImDrawData* draw_data)
{
	mesh->ImGui_Impl_RenderDrawData(draw_data);
}

void GodotImGui::ImGui_Impl_ProcessEvent(InputEvent *event)
{
    ImGuiIO& io = ImGui::GetIO();
	
	if (Object::cast_to<InputEventFromWindow>(event)) {
		if (auto e = Object::cast_to<InputEventScreenDrag>(event)) {
			if (e->get_index() == 0) {
				io.AddMousePosEvent(e->get_position().x, e->get_position().y);
			}
        } else if (auto e = Object::cast_to<InputEventScreenTouch>(event)) {
			if (e->get_index() == 0) {
				io.AddMousePosEvent(e->get_position().x, e->get_position().y);
			}
        } else if (Object::cast_to<InputEventWithModifiers>(event)) {
			if (auto e = Object::cast_to<InputEventMouseMotion>(event)) {
				auto p = e->get_position();
				io.AddMousePosEvent(p.x, p.y);
			} else if (auto e = Object::cast_to<InputEventMouseButton>(event)) {
				switch(e->get_button_index()) {
					case MouseButton::MOUSE_BUTTON_LEFT:
						io.AddMouseButtonEvent(ImGuiMouseButton_Left, e->is_pressed());
						break;
					case MouseButton::MOUSE_BUTTON_RIGHT:
						io.AddMouseButtonEvent(ImGuiMouseButton_Right, e->is_pressed());
						break;
					case MouseButton::MOUSE_BUTTON_MIDDLE:
						io.AddMouseButtonEvent(ImGuiMouseButton_Middle, e->is_pressed());
						break;
					case MouseButton::MOUSE_BUTTON_WHEEL_DOWN:
						io.AddMouseWheelEvent(0, e->get_factor() > 0.01 ? e->get_factor() : 1);
						break;
					case MouseButton::MOUSE_BUTTON_WHEEL_UP:
						io.AddMouseWheelEvent(0, e->get_factor() > 0.01 ? -e->get_factor() : -1);
						break;
					case MouseButton::MOUSE_BUTTON_WHEEL_LEFT:
						io.AddMouseWheelEvent(e->get_factor() > 0.01 ? e->get_factor() : 1, 0);
						break;
					case MouseButton::MOUSE_BUTTON_WHEEL_RIGHT:
						io.AddMouseWheelEvent(e->get_factor() > 0.01 ? -e->get_factor() : -1, 0);
						break;
					default:
						;
						// TODO: how to handle these other keys?
				}
			} else if (auto e = Object::cast_to<InputEventKey>(event)) {
				auto imguiKeyCode = GodotToImGuiKeyCode(e->get_keycode());
				io.AddKeyEvent(imguiKeyCode, e->is_pressed());
                io.AddInputCharacter((unsigned int)e->get_unicode());
// 				io.SetKeyEventNativeData(imguiKeyCode, e->get_keycode(), e->get_physical_keycode()); // To support legacy indexing (<1.87 user code)
			}
        }
	}
//     case ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY:
//         if (ev->mouse.display == bd->Display)
//             io.AddMousePosEvent(-FLT_MAX, -FLT_MAX);
//         return true;
}


void GodotImGui::ImGui_Impl_BeginFrame()
{
	if (hasFrameBegun == false) {
		hasFrameBegun = true;
		
		ImGui_Impl_NewFrame();
		ImGui::NewFrame();
	}
}
void GodotImGui::ImGui_Impl_EndFrame()
{
	if (hasFrameBegun == true) {
		hasFrameBegun = false;
		
		ImGui::Render();
		ImGui_Impl_RenderDrawData(ImGui::GetDrawData());
	}
}

void GodotImGui::ImGui_Impl_UpdateMouseCursor()
{
    ImGuiIO& io = ImGui::GetIO();
	Input &gio = *Input::get_singleton();
    if (io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange)
        return;

    ImGuiMouseCursor imgui_cursor = ImGui::GetMouseCursor();
    if (io.MouseDrawCursor || imgui_cursor == ImGuiMouseCursor_None)
    {
        // Hide OS mouse cursor if imgui is drawing it or if it wants no cursor
//         al_set_mouse_cursor(bd->Display, bd->MouseCursorInvisible);
    }
    else
    {
		Input::CursorShape cursor_id = Input::CursorShape::CURSOR_ARROW;
        switch (imgui_cursor)
        {
        case ImGuiMouseCursor_TextInput:    cursor_id = Input::CursorShape::CURSOR_IBEAM; break;
        case ImGuiMouseCursor_ResizeAll:    cursor_id = Input::CursorShape::CURSOR_MOVE; break;
        case ImGuiMouseCursor_ResizeNS:     cursor_id = Input::CursorShape::CURSOR_VSIZE; break;
        case ImGuiMouseCursor_ResizeEW:     cursor_id = Input::CursorShape::CURSOR_HSIZE; break;
        case ImGuiMouseCursor_ResizeNESW:   cursor_id = Input::CursorShape::CURSOR_FDIAGSIZE; break;
        case ImGuiMouseCursor_ResizeNWSE:   cursor_id = Input::CursorShape::CURSOR_BDIAGSIZE; break;
		case ImGuiMouseCursor_NotAllowed:   cursor_id = Input::CursorShape::CURSOR_FORBIDDEN; break;
        }
		gio.set_custom_mouse_cursor(nullptr, cursor_id);
    }
}
