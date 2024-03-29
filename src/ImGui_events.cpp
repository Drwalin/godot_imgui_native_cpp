#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/rendering_server.hpp>
#include <godot_cpp/classes/display_server.hpp>
#include <godot_cpp/classes/text_server.hpp>
#include <godot_cpp/classes/image_texture.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/viewport.hpp>

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

ImGuiKey GodotToImGuiKeyCode(int keycode);

void GodotImGui::_process(double_t dt)
{
	if (Engine::get_singleton()->is_editor_hint()) {
		return;
	}
}

void GodotImGui::_input(const Ref<InputEvent> &event)
{
	if (Engine::get_singleton()->is_editor_hint()) {
		return;
	}
	
	ImGui_Impl_ProcessEvent(event.ptr());
}

void GodotImGui::ImGui_Impl_ProcessEvent(InputEvent *event)
{
	if (Engine::get_singleton()->is_editor_hint()) {
		return;
	}
	
	if (imGuiContext == nullptr) {
		return;
	}
	
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
						// TODO: how to handle these other mouse buttons?
				}
			} else if (auto e = Object::cast_to<InputEventKey>(event)) {
				if (e->is_alt_pressed() == false) {
					if (ImGui::IsKeyDown(ImGuiKey_ModAlt)) {
						io.AddKeyEvent(ImGuiKey_ModAlt, false);
					}
				}
				auto imguiKeyCode = GodotToImGuiKeyCode(e->get_keycode());
				io.AddKeyEvent(imguiKeyCode, e->is_pressed());
				if (e->get_unicode() != 0) {
					io.AddInputCharacter((unsigned int)e->get_unicode());
				}
// 				io.SetKeyEventNativeData(imguiKeyCode, e->get_keycode(), e->get_physical_keycode()); // To support legacy indexing (<1.87 user code)
			}
        }
	}
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
		case Key::KEY_CTRL: return ImGuiKey_ModCtrl;
		case Key::KEY_SHIFT: return ImGuiKey_ModShift;
		case Key::KEY_ALT: return ImGuiKey_ModAlt;
// 		case Key::KEY_CTRL: return ImGuiKey_LeftCtrl;
// 		case Key::KEY_SHIFT: return ImGuiKey_LeftShift;
// 		case Key::KEY_ALT: return ImGuiKey_LeftAlt;
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
