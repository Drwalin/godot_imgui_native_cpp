#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/rendering_server.hpp>
#include <godot_cpp/classes/display_server.hpp>
#include <godot_cpp/classes/text_server.hpp>
#include <godot_cpp/classes/image_texture.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/input.hpp>

#include "../include/godot_imgui_native/ImGui.hpp"

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
	
	ImGui_Impl_Init();
}

void GodotImGui::_bind_methods()
{
	METHOD_NO_ARGS(GodotImGui, EnableInput);
	METHOD_NO_ARGS(GodotImGui, DisableInput);
	METHOD_NO_ARGS(GodotImGui, IsInputEnabled);
	
	ClassDB::bind_method(D_METHOD("ImGui_NewFrame"), &GodotImGui::ImGui_Impl_BeginFrame);
	ClassDB::bind_method(D_METHOD("ImGui_EndFrame"), &GodotImGui::ImGui_Impl_EndFrame);
	
	METHOD_NO_ARGS(GodotImGui, GetFontTexture);
	
	METHOD_ARGS(GodotImGui, GetFont, "path", "sizePixels");
}

Texture2D *GodotImGui::GetFontTexture()
{
	return fontTexture.ptr();
}

void GodotImGui::_enter_tree()
{
	if (Engine::get_singleton()->is_editor_hint()) {
		return;
	}
	
	shader = ResourceLoader::get_singleton()->load("res://imgui/gui_shader.gdshader");
	
	material.instantiate();
	material->set_shader(shader);
	
	this->set_texture_filter(TEXTURE_FILTER_LINEAR);
	this->set_texture_repeat(TEXTURE_REPEAT_ENABLED);
	this->set_light_mask(0);
	
	auto rs = RenderingServer::get_singleton();
 	rs->connect("frame_pre_draw", Callable(this, "ImGui_EndFrame"));
	
	ImGui_Impl_BeginFrame();
}

void GodotImGui::_exit_tree()
{
	if (Engine::get_singleton()->is_editor_hint()) {
		return;
	}
	
	if (imGuiContext) {
		auto rs = RenderingServer::get_singleton();
		rs->disconnect("frame_pre_draw", Callable(this, "ImGui_EndFrame"));
	
		ImGui_Impl_Shutdown();
	}
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

void GodotImGui::ImGui_Impl_NewFrame()
{
    ImGuiIO& io = ImGui::GetIO();

	DisplayServer *ds = DisplayServer::get_singleton();
	
	auto s = ds->window_get_size(0);
	int w = s.width;
	int h = s.height;
    io.DisplaySize = ImVec2((float)w, (float)h);
	
	auto now = std::chrono::steady_clock::now();
	double dt = std::chrono::duration<double>(now-prevFrameStart).count();
	prevFrameStart = now;
    io.DeltaTime = dt;

    ImGui_Impl_UpdateMouseCursor();
}

void GodotImGui::ImGui_Impl_BeginFrame()
{
	if (hasFrameBegun == false && imGuiContext) {
		for (auto &it : fontsToLoad) {
			LoadFont(it);
		}
		fontsToLoad.clear();
		
		if (forceLoadSettings.empty() == false) {
    		ImGui::LoadIniSettingsFromMemory(forceLoadSettings.c_str(), forceLoadSettings.size());
			forceLoadSettings.clear();
		}
		
		if (rebuildFonts) {
			ImGui_Impl_InitFonts();
		}
		
		hasFrameBegun = true;
		ImGui_Impl_NewFrame();
		ImGui::NewFrame();
	}
}
void GodotImGui::ImGui_Impl_EndFrame()
{
	if (hasFrameBegun == true) {
		hasFrameBegun = false;
		
		if (imGuiContext) {
			ImGui::Render();
			ImGui_Impl_RenderDrawData(ImGui::GetDrawData());
		}
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
// 		if (io.MouseDrawCursor == false) {
// 			Input::get_singleton()->set_mouse_mode(Input::MouseMode::MOUSE_MODE_VISIBLE);
// 		} else {
// 			Input::get_singleton()->set_mouse_mode(Input::MouseMode::MOUSE_MODE_HIDDEN);
// 		}
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

void GodotImGui::ImGui_Impl_Init()
{
	IMGUI_CHECKVERSION();
	imGuiContext = ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.BackendPlatformUserData = this;
	ImGui::StyleColorsClassic();
	
	ImGui_Impl_InitFonts();
	
	io.GetClipboardTextFn = +[](void*ptr)->const char *{
		static std::string content;
		content = DisplayServer::get_singleton()->clipboard_get().utf8().ptr();
		return content.c_str();
	};
	io.SetClipboardTextFn = +[](void*ptr, const char*str)->void{
		DisplayServer::get_singleton()->clipboard_set(String::utf8(str));
	};
}

void GodotImGui::ImGui_Impl_InitFonts()
{
	UtilityFunctions::print("Rebuilding fonts");
	rebuildFonts = false;
	
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
    ImGuiIO& io = ImGui::GetIO();
	io.BackendPlatformUserData = nullptr;
	fontsCache.clear();
	ImGui::DestroyContext();
	imGuiContext = nullptr;
}


ImFont *GodotImGui::LoadFont(const struct FontSizePair &info)
{
	auto bytes = FileAccess::get_file_as_bytes(info.filePath);
	if (bytes.size() == 0) {
		return nullptr;
	}
	
    ImGuiIO& io = ImGui::GetIO();
	auto f = io.Fonts;
	
	ImFontGlyphRangesBuilder glyphs;
	glyphs.AddText("ęóąśłżźćńĘÓĄŚŁŻŹĆŃ„”µðđŋħˀĸþ→€←ŧ¶ſ@Ω§®Ŧ¥¢ıÓÞĄŚÐªŊĦ ̛&ŁŻŹĆ‘“Ńº•· ̣´^¨~`×÷ ̇˝ˇ˚¯˘¬¹²³¼½¾{[]}¸˛¿°±™⅞⅝⅜$£⅛¡");
	glyphs.AddRanges(f->GetGlyphRangesDefault());
    glyphs.AddRanges(f->GetGlyphRangesGreek());
    glyphs.AddRanges(f->GetGlyphRangesKorean());
    glyphs.AddRanges(f->GetGlyphRangesJapanese());
    glyphs.AddRanges(f->GetGlyphRangesChineseFull());
    glyphs.AddRanges(f->GetGlyphRangesChineseSimplifiedCommon());
    glyphs.AddRanges(f->GetGlyphRangesCyrillic());
    glyphs.AddRanges(f->GetGlyphRangesThai());
    glyphs.AddRanges(f->GetGlyphRangesVietnamese());
	
	ImVector<ImWchar> r;
	glyphs.BuildRanges(&r);
	
	void *ownedByImGui = ImGui::MemAlloc(bytes.size());
	memcpy(ownedByImGui, bytes.ptr(), bytes.size());
	ImFont *font = io.Fonts->AddFontFromMemoryTTF(ownedByImGui, bytes.size(), info.size, nullptr, r.begin());
	if (font) {
		rebuildFonts = true;
		ImGuiIO& io = ImGui::GetIO();
		unsigned char* pixels;
		int width, height;
		io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
	}
	fontsCache[info.fontName] = font;
	
	return font;
}

ImFont *GodotImGui::LoadFont(const String &path, float sizePixels)
{
	if (path.ends_with(".ttf") == false && path.ends_with(".otf")) {
		return nullptr;
	}
	
	std::string fontName = path.utf8().ptr();
	fontName += ":" + std::to_string((int)(sizePixels*100.0f));
	
	auto it = fontsCache.find(fontName);
	if (it != fontsCache.end()) {
		return it->second;
	}
	
	FontSizePair fontInfo{fontName, path, sizePixels};
	
	if (hasFrameBegun) {
		fontsToLoad.push_back(fontInfo);
		UtilityFunctions::print("Trying to load font inside a frame.");
		return nullptr;
	}
	
	return LoadFont(fontInfo);
}

int64_t GodotImGui::GetFont(const String &path, float sizePixels)
{
	return (int64_t)LoadFont(path, sizePixels);
}
