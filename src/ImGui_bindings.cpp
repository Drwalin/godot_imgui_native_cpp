#include <tuple>
#include <functional>

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/rendering_server.hpp>
#include <godot_cpp/classes/display_server.hpp>
#include <godot_cpp/classes/text_server.hpp>
#include <godot_cpp/classes/image_texture.hpp>

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

#define BIND_STATIC_METHOD(M_NAME, CODE) \
	ClassDB::bind_static_method("ImGui", M_NAME, CODE)

void CrossCallFrom_ImGui_to_Godot_ImGui_method_bingings();
void CrossCallFrom_ImGui_to_Godot_ImGui_method_bingings()
{
	GodotImGui::Bind_ImGui();
}

void GodotImGui::Bind_ImGui()
{
	Bind_EnumConstants();
	
	BIND_STATIC_METHOD(D_METHOD("Begin", "name", "flags"),
		+[](const String &name, int64_t flags) {
			return ImGui::Begin(name.utf8().ptr(), nullptr, flags);
		});
	BIND_STATIC_METHOD(D_METHOD("End"), ImGui::End);
	
	BIND_STATIC_METHOD(D_METHOD("BeginChild", "str_id", "size", "child_flags", "window_flags"),
		+[](const String &str_id, const Vector2 &size, int64_t child_flags, int64_t window_flags) {
			return ImGui::BeginChild(str_id.utf8().ptr(), {size.x, size.y}, child_flags, window_flags);
		});
	BIND_STATIC_METHOD(D_METHOD("BeginChild_id", "id", "size", "child_flags", "window_flags"),
		+[](int64_t id, const Vector2 &size, int64_t child_flags, int64_t window_flags) {
			return ImGui::BeginChild(id, {size.x, size.y}, child_flags, window_flags);
		});
	BIND_STATIC_METHOD(D_METHOD("EndChild"), ImGui::EndChild);
	
	BIND_STATIC_METHOD(D_METHOD("IsWindowAppearing"), ImGui::IsWindowAppearing);
	BIND_STATIC_METHOD(D_METHOD("IsWindowCollapsed"), ImGui::IsWindowCollapsed);
	BIND_STATIC_METHOD(D_METHOD("IsWindowFocused", "flags"),
		+[](int64_t flags) { return ImGui::IsWindowFocused(flags); });
	BIND_STATIC_METHOD(D_METHOD("IsWindowHovered", "flags"),
		+[](int64_t flags) { return ImGui::IsWindowHovered(flags); });
	BIND_STATIC_METHOD(D_METHOD("GetWindowPos", "flags"),
		+[](int64_t flags) {
			auto v = ImGui::GetWindowPos();
			return Vector2(v.x, v.y);
		});
	BIND_STATIC_METHOD(D_METHOD("GetWindowSize", "flags"),
		+[](int64_t flags) {
			auto v = ImGui::GetWindowSize();
			return Vector2(v.x, v.y);
		});
	BIND_STATIC_METHOD(D_METHOD("GetWindowWidth"), +[]()->double_t{return ImGui::GetWindowWidth();});
	BIND_STATIC_METHOD(D_METHOD("GetWindowHeight"), +[]()->double_t{return ImGui::GetWindowHeight();});
	
	
	BIND_STATIC_METHOD(D_METHOD("SetNextWindowPos", "pos", "cond", "pivot"),
		+[](const Vector2 &pos, int64_t cond, const Vector2 &pivot) {
			ImGui::SetNextWindowPos({pos.x, pos.y}, cond, {pivot.x, pivot.y});
		});
	BIND_STATIC_METHOD(D_METHOD("SetNextWindowSize", "pos", "cond"),
		+[](const Vector2 &pos, int64_t cond) {
			ImGui::SetNextWindowSize({pos.x, pos.y}, cond);
		});
	BIND_STATIC_METHOD(D_METHOD("SetNextWindowSizeConstraints", "size_min", "size_max"),
		+[](const Vector2 &size_min, const Vector2 &size_max) {
			ImGui::SetNextWindowSizeConstraints({size_min.x, size_min.y}, {size_max.x, size_max.y}, nullptr, nullptr);
		});
	BIND_STATIC_METHOD(D_METHOD("SetNextWindowContentSize", "size"),
		+[](const Vector2 &size) {
			ImGui::SetNextWindowContentSize({size.x, size.y});
		});
	BIND_STATIC_METHOD(D_METHOD("SetNextWindowCollapsed", "collapsed", "cond"),
		+[](bool collapsed, int64_t cond) {
			ImGui::SetNextWindowCollapsed(collapsed, cond);
		});
	BIND_STATIC_METHOD(D_METHOD("SetNextWindowFocus"), ImGui::SetNextWindowFocus);
	BIND_STATIC_METHOD(D_METHOD("SetNextWindowScroll", "scroll"),
		+[](const Vector2 &scroll) {
			ImGui::SetNextWindowScroll({scroll.x, scroll.y});
		});
	BIND_STATIC_METHOD(D_METHOD("SetNextWindowBgAlpha", "alpha"),
		+[](double_t alpha) {
			ImGui::SetNextWindowBgAlpha(alpha);
		});
	BIND_STATIC_METHOD(D_METHOD("SetWindowPos", "name", "pos", "cond"),
		+[](const String &name, const Vector2 &pos, int64_t cond) {
			ImGui::SetWindowPos(name.utf8().ptr(), {pos.x, pos.y}, cond);
		});
	BIND_STATIC_METHOD(D_METHOD("SetWindowSize", "name", "size", "cond"),
		+[](const String &name, const Vector2 &size, int64_t cond) {
			ImGui::SetWindowSize(name.utf8().ptr(), {size.x, size.y}, cond);
		});
	BIND_STATIC_METHOD(D_METHOD("SetWindowCollapsed", "name", "collapsed", "cond"),
		+[](const String &name, bool collapsed, int64_t cond) {
			ImGui::SetWindowCollapsed(name.utf8().ptr(), collapsed, cond);
		});
	BIND_STATIC_METHOD(D_METHOD("SetWindowFocus", "name"),
		+[](const String &name) {
			ImGui::SetWindowFocus(name.utf8().ptr());
		});
	
	BIND_STATIC_METHOD(D_METHOD("GetContentRegionAvail"),
		+[]() {
			auto v = ImGui::GetContentRegionAvail();
			return Vector2(v.x, v.y);
		});
	BIND_STATIC_METHOD(D_METHOD("GetContentRegionMax"),
		+[]() {
			auto v = ImGui::GetContentRegionMax();
			return Vector2(v.x, v.y);
		});
	BIND_STATIC_METHOD(D_METHOD("GetWindowContentRegionMin"),
		+[]() {
			auto v = ImGui::GetWindowContentRegionMin();
			return Vector2(v.x, v.y);
		});
	BIND_STATIC_METHOD(D_METHOD("GetWindowContentRegionMax"),
		+[]() {
			auto v = ImGui::GetWindowContentRegionMax();
			return Vector2(v.x, v.y);
		});
	
	BIND_STATIC_METHOD(D_METHOD("IsItemHovered", "flags"),
		+[](int64_t flags) {
			return ImGui::IsItemHovered(flags);
		});
	BIND_STATIC_METHOD(D_METHOD("IsItemClicked", "mouse_button"),
		+[](int64_t flags) {
			return ImGui::IsItemClicked(flags);
		});
	BIND_STATIC_METHOD(D_METHOD("IsItemActive"), ImGui::IsItemActive);
	BIND_STATIC_METHOD(D_METHOD("IsItemFocused"), ImGui::IsItemFocused);
	BIND_STATIC_METHOD(D_METHOD("IsItemVisible"), ImGui::IsItemVisible);
	BIND_STATIC_METHOD(D_METHOD("IsItemEdited"), ImGui::IsItemEdited);
	BIND_STATIC_METHOD(D_METHOD("IsItemActivated"), ImGui::IsItemActivated);
	BIND_STATIC_METHOD(D_METHOD("IsItemDeactivated"), ImGui::IsItemDeactivated);
	BIND_STATIC_METHOD(D_METHOD("IsItemDeactivatedAfterEdit"), ImGui::IsItemDeactivatedAfterEdit);
	BIND_STATIC_METHOD(D_METHOD("IsItemToggledOpen"), ImGui::IsItemToggledOpen);
	BIND_STATIC_METHOD(D_METHOD("IsAnyItemHovered"), ImGui::IsAnyItemHovered);
	BIND_STATIC_METHOD(D_METHOD("IsAnyItemActive"), ImGui::IsAnyItemActive);
	BIND_STATIC_METHOD(D_METHOD("IsAnyItemFocused"), ImGui::IsAnyItemFocused);
	BIND_STATIC_METHOD(D_METHOD("GetItemID"),
		+[]() {
			return (int64_t) ImGui::GetItemID();
		});
	BIND_STATIC_METHOD(D_METHOD("GetItemRectMin"),
		+[]() {
			auto v = ImGui::GetItemRectMin();
			return Vector2(v.x, v.y);
		});
	BIND_STATIC_METHOD(D_METHOD("GetItemRectMax"),
		+[]() {
			auto v = ImGui::GetItemRectMax();
			return Vector2(v.x, v.y);
		});
	BIND_STATIC_METHOD(D_METHOD("GetItemRectSize"),
		+[]() {
			auto v = ImGui::GetItemRectSize();
			return Vector2(v.x, v.y);
		});
	
	
	
	
	
	
	BIND_STATIC_METHOD(D_METHOD("PushStyleColor", "style_color_id", "color"),
		+[](int64_t idx, const Color &c) {
			ImGui::PushStyleColor(idx, {c.r, c.g, c.b, c.a});
		});
	BIND_STATIC_METHOD(D_METHOD("PopStyleColor", "count"),
		+[](int64_t count) {
			ImGui::PopStyleColor(count);
		});
	BIND_STATIC_METHOD(D_METHOD("PushStyleVarFloat", "style_var_idx", "value"),
		+[](int64_t idx, double_t v) {
			ImGui::PushStyleVar(idx, v);
		});
	BIND_STATIC_METHOD(D_METHOD("PushStyleVarVec2", "style_var_idx", "value"),
		+[](int64_t idx, const Vector2 &v) {
			ImGui::PushStyleVar(idx, {v.x, v.y});
		});
	BIND_STATIC_METHOD(D_METHOD("PopStyleVar", "count"),
		+[](int64_t count) {
			ImGui::PopStyleVar(count);
		});
	
	
	BIND_STATIC_METHOD(D_METHOD("PushTabStop", "tab_stop"), ImGui::PushTabStop);
	BIND_STATIC_METHOD(D_METHOD("PopTabStop"), ImGui::PopTabStop);
	BIND_STATIC_METHOD(D_METHOD("PushButtonRepeat", "repeat"), ImGui::PushButtonRepeat);
	BIND_STATIC_METHOD(D_METHOD("PopButtonRepeat"), ImGui::PopButtonRepeat);
	
	
	
	
	
	
	
	
	
// 	void Separator()
// 	void SameLine(float offset_from_start_x=0.0f, float spacing=-1.0f)
// 	void NewLine()
// 	void Spacing()
// 	void Dummy(const ImVec2& size)
// 	void Indent(float indent_w = 0.0f)
// 	void Unindent(float indent_w = 0.0f)
// 	void BeginGroup()
// 	void EndGroup()
// 	void AlignTextToFramePadding()
// 	float GetTextLineHeight()
// 	float GetTextLineHeightWithSpacing()
// 	float GetFrameHeight()
// 	float GetFrameHeightWithSpacing()
	
	
	
	
	
	
	
	
			
	BIND_STATIC_METHOD(D_METHOD("Text", "str"),
		+[](const String &str) {
			auto s = str.utf8();
			ImGui::TextUnformatted(s.ptr(), s.ptr()+s.length());
		});
	
	
	
	
	IMGUI_API void          TextUnformatted(const char* text, const char* text_end = NULL); // raw text without formatting. Roughly equivalent to Text("%s", text) but: A) doesn't require null terminated string if 'text_end' is specified, B) it's faster, no memory copy is done, no buffer size limits, recommended for long chunks of text.
	IMGUI_API void          Text(const char* fmt, ...)                                      IM_FMTARGS(1); // formatted text
	IMGUI_API void          TextV(const char* fmt, va_list args)                            IM_FMTLIST(1);
	IMGUI_API void          TextColored(const ImVec4& col, const char* fmt, ...)            IM_FMTARGS(2); // shortcut for PushStyleColor(ImGuiCol_Text, col); Text(fmt, ...); PopStyleColor();
	IMGUI_API void          TextColoredV(const ImVec4& col, const char* fmt, va_list args)  IM_FMTLIST(2);
	IMGUI_API void          TextDisabled(const char* fmt, ...)                              IM_FMTARGS(1); // shortcut for PushStyleColor(ImGuiCol_Text, style.Colors[ImGuiCol_TextDisabled]); Text(fmt, ...); PopStyleColor();
	IMGUI_API void          TextDisabledV(const char* fmt, va_list args)                    IM_FMTLIST(1);
	IMGUI_API void          TextWrapped(const char* fmt, ...)                               IM_FMTARGS(1); // shortcut for PushTextWrapPos(0.0f); Text(fmt, ...); PopTextWrapPos();. Note that this won't work on an auto-resizing window if there's no other widgets to extend the window width, yoy may need to set a size using SetNextWindowSize().
	IMGUI_API void          TextWrappedV(const char* fmt, va_list args)                     IM_FMTLIST(1);
	IMGUI_API void          LabelText(const char* label, const char* fmt, ...)              IM_FMTARGS(2); // display text+label aligned the same way as value+label widgets
	IMGUI_API void          LabelTextV(const char* label, const char* fmt, va_list args)    IM_FMTLIST(2);
	IMGUI_API void          BulletText(const char* fmt, ...)                                IM_FMTARGS(1); // shortcut for Bullet()+Text()
	IMGUI_API void          BulletTextV(const char* fmt, va_list args)                      IM_FMTLIST(1);
	IMGUI_API void          SeparatorText(const char* label);                               // currently: formatted text with an horizontal line
	
}

#define ___NAME_TO_STR(__NAM) #__NAM

#define BIND_ENUM_CONSTANT_FIELD(ENUM, VAL) \
	ClassDB::bind_integer_constant("ImGui", #ENUM, ___NAME_TO_STR(ENUM##_&&VAL), ImGui##ENUM##_##VAL, true)

void GodotImGui::Bind_EnumConstants()
{
	BIND_ENUM_CONSTANT_FIELD(WindowFlags, None);
	BIND_ENUM_CONSTANT_FIELD(WindowFlags, NoTitleBar);
	BIND_ENUM_CONSTANT_FIELD(WindowFlags, NoResize);
	BIND_ENUM_CONSTANT_FIELD(WindowFlags, NoMove);
	BIND_ENUM_CONSTANT_FIELD(WindowFlags, NoScrollbar);
	BIND_ENUM_CONSTANT_FIELD(WindowFlags, NoScrollWithMouse);
	BIND_ENUM_CONSTANT_FIELD(WindowFlags, NoCollapse);
	BIND_ENUM_CONSTANT_FIELD(WindowFlags, AlwaysAutoResize);
	BIND_ENUM_CONSTANT_FIELD(WindowFlags, NoBackground);
	BIND_ENUM_CONSTANT_FIELD(WindowFlags, NoSavedSettings);
	BIND_ENUM_CONSTANT_FIELD(WindowFlags, NoMouseInputs);
	BIND_ENUM_CONSTANT_FIELD(WindowFlags, MenuBar);
	BIND_ENUM_CONSTANT_FIELD(WindowFlags, HorizontalScrollbar);
	BIND_ENUM_CONSTANT_FIELD(WindowFlags, NoFocusOnAppearing);
	BIND_ENUM_CONSTANT_FIELD(WindowFlags, NoBringToFrontOnFocus);
	BIND_ENUM_CONSTANT_FIELD(WindowFlags, AlwaysVerticalScrollbar);
	BIND_ENUM_CONSTANT_FIELD(WindowFlags, AlwaysHorizontalScrollbar);
	BIND_ENUM_CONSTANT_FIELD(WindowFlags, NoNavInputs);
	BIND_ENUM_CONSTANT_FIELD(WindowFlags, NoNavFocus);
	BIND_ENUM_CONSTANT_FIELD(WindowFlags, UnsavedDocument);
	BIND_ENUM_CONSTANT_FIELD(WindowFlags, NoNav);
	BIND_ENUM_CONSTANT_FIELD(WindowFlags, NoDecoration);
	BIND_ENUM_CONSTANT_FIELD(WindowFlags, NoInputs);
	BIND_ENUM_CONSTANT_FIELD(WindowFlags, NavFlattened);
	BIND_ENUM_CONSTANT_FIELD(WindowFlags, ChildWindow);
	BIND_ENUM_CONSTANT_FIELD(WindowFlags, Tooltip);
	BIND_ENUM_CONSTANT_FIELD(WindowFlags, Popup);
	BIND_ENUM_CONSTANT_FIELD(WindowFlags, Modal);
	BIND_ENUM_CONSTANT_FIELD(WindowFlags, ChildMenu);

	BIND_ENUM_CONSTANT_FIELD(ChildFlags, None);
	BIND_ENUM_CONSTANT_FIELD(ChildFlags, Border);
	BIND_ENUM_CONSTANT_FIELD(ChildFlags, AlwaysUseWindowPadding);
	BIND_ENUM_CONSTANT_FIELD(ChildFlags, ResizeX);
	BIND_ENUM_CONSTANT_FIELD(ChildFlags, ResizeY);
	BIND_ENUM_CONSTANT_FIELD(ChildFlags, AutoResizeX);
	BIND_ENUM_CONSTANT_FIELD(ChildFlags, AutoResizeY);
	BIND_ENUM_CONSTANT_FIELD(ChildFlags, AlwaysAutoResize);
	BIND_ENUM_CONSTANT_FIELD(ChildFlags, FrameStyle);

	BIND_ENUM_CONSTANT_FIELD(InputTextFlags, None);
	BIND_ENUM_CONSTANT_FIELD(InputTextFlags, CharsDecimal);
	BIND_ENUM_CONSTANT_FIELD(InputTextFlags, CharsHexadecimal);
	BIND_ENUM_CONSTANT_FIELD(InputTextFlags, CharsUppercase);
	BIND_ENUM_CONSTANT_FIELD(InputTextFlags, CharsNoBlank);
	BIND_ENUM_CONSTANT_FIELD(InputTextFlags, AutoSelectAll);
	BIND_ENUM_CONSTANT_FIELD(InputTextFlags, EnterReturnsTrue);
	BIND_ENUM_CONSTANT_FIELD(InputTextFlags, CallbackCompletion);
	BIND_ENUM_CONSTANT_FIELD(InputTextFlags, CallbackHistory);
	BIND_ENUM_CONSTANT_FIELD(InputTextFlags, CallbackAlways);
	BIND_ENUM_CONSTANT_FIELD(InputTextFlags, CallbackCharFilter);
	BIND_ENUM_CONSTANT_FIELD(InputTextFlags, AllowTabInput);
	BIND_ENUM_CONSTANT_FIELD(InputTextFlags, CtrlEnterForNewLine);
	BIND_ENUM_CONSTANT_FIELD(InputTextFlags, NoHorizontalScroll);
	BIND_ENUM_CONSTANT_FIELD(InputTextFlags, AlwaysOverwrite);
	BIND_ENUM_CONSTANT_FIELD(InputTextFlags, ReadOnly);
	BIND_ENUM_CONSTANT_FIELD(InputTextFlags, Password);
	BIND_ENUM_CONSTANT_FIELD(InputTextFlags, NoUndoRedo);
	BIND_ENUM_CONSTANT_FIELD(InputTextFlags, CharsScientific);
	BIND_ENUM_CONSTANT_FIELD(InputTextFlags, CallbackResize);
	BIND_ENUM_CONSTANT_FIELD(InputTextFlags, CallbackEdit);
	BIND_ENUM_CONSTANT_FIELD(InputTextFlags, EscapeClearsAll);

	BIND_ENUM_CONSTANT_FIELD(TreeNodeFlags, None);
	BIND_ENUM_CONSTANT_FIELD(TreeNodeFlags, Selected);
	BIND_ENUM_CONSTANT_FIELD(TreeNodeFlags, Framed);
	BIND_ENUM_CONSTANT_FIELD(TreeNodeFlags, AllowOverlap);
	BIND_ENUM_CONSTANT_FIELD(TreeNodeFlags, NoTreePushOnOpen);
	BIND_ENUM_CONSTANT_FIELD(TreeNodeFlags, NoAutoOpenOnLog);
	BIND_ENUM_CONSTANT_FIELD(TreeNodeFlags, DefaultOpen);
	BIND_ENUM_CONSTANT_FIELD(TreeNodeFlags, OpenOnDoubleClick);
	BIND_ENUM_CONSTANT_FIELD(TreeNodeFlags, OpenOnArrow);
	BIND_ENUM_CONSTANT_FIELD(TreeNodeFlags, Leaf);
	BIND_ENUM_CONSTANT_FIELD(TreeNodeFlags, Bullet);
	BIND_ENUM_CONSTANT_FIELD(TreeNodeFlags, FramePadding);
	BIND_ENUM_CONSTANT_FIELD(TreeNodeFlags, SpanAvailWidth);
	BIND_ENUM_CONSTANT_FIELD(TreeNodeFlags, SpanFullWidth);
	BIND_ENUM_CONSTANT_FIELD(TreeNodeFlags, SpanAllColumns);
	BIND_ENUM_CONSTANT_FIELD(TreeNodeFlags, NavLeftJumpsBackHere);
	BIND_ENUM_CONSTANT_FIELD(TreeNodeFlags, CollapsingHeader);

	BIND_ENUM_CONSTANT_FIELD(PopupFlags, None);
	BIND_ENUM_CONSTANT_FIELD(PopupFlags, MouseButtonLeft);
	BIND_ENUM_CONSTANT_FIELD(PopupFlags, MouseButtonRight);
	BIND_ENUM_CONSTANT_FIELD(PopupFlags, MouseButtonMiddle);
	BIND_ENUM_CONSTANT_FIELD(PopupFlags, MouseButtonMask_);
	BIND_ENUM_CONSTANT_FIELD(PopupFlags, MouseButtonDefault_);
	BIND_ENUM_CONSTANT_FIELD(PopupFlags, NoReopen);
	BIND_ENUM_CONSTANT_FIELD(PopupFlags, NoOpenOverExistingPopup);
	BIND_ENUM_CONSTANT_FIELD(PopupFlags, NoOpenOverItems);
	BIND_ENUM_CONSTANT_FIELD(PopupFlags, AnyPopupId);
	BIND_ENUM_CONSTANT_FIELD(PopupFlags, AnyPopupLevel);
	BIND_ENUM_CONSTANT_FIELD(PopupFlags, AnyPopup);

	BIND_ENUM_CONSTANT_FIELD(SelectableFlags, None);
	BIND_ENUM_CONSTANT_FIELD(SelectableFlags, DontClosePopups);
	BIND_ENUM_CONSTANT_FIELD(SelectableFlags, SpanAllColumns);
	BIND_ENUM_CONSTANT_FIELD(SelectableFlags, AllowDoubleClick);
	BIND_ENUM_CONSTANT_FIELD(SelectableFlags, Disabled);
	BIND_ENUM_CONSTANT_FIELD(SelectableFlags, AllowOverlap);

	BIND_ENUM_CONSTANT_FIELD(ComboFlags, None);
	BIND_ENUM_CONSTANT_FIELD(ComboFlags, PopupAlignLeft);
	BIND_ENUM_CONSTANT_FIELD(ComboFlags, HeightSmall);
	BIND_ENUM_CONSTANT_FIELD(ComboFlags, HeightRegular);
	BIND_ENUM_CONSTANT_FIELD(ComboFlags, HeightLarge);
	BIND_ENUM_CONSTANT_FIELD(ComboFlags, HeightLargest);
	BIND_ENUM_CONSTANT_FIELD(ComboFlags, NoArrowButton);
	BIND_ENUM_CONSTANT_FIELD(ComboFlags, NoPreview);
	BIND_ENUM_CONSTANT_FIELD(ComboFlags, WidthFitPreview);
	BIND_ENUM_CONSTANT_FIELD(ComboFlags, HeightMask_);

	BIND_ENUM_CONSTANT_FIELD(TabBarFlags, None);
	BIND_ENUM_CONSTANT_FIELD(TabBarFlags, Reorderable);
	BIND_ENUM_CONSTANT_FIELD(TabBarFlags, AutoSelectNewTabs);
	BIND_ENUM_CONSTANT_FIELD(TabBarFlags, TabListPopupButton);
	BIND_ENUM_CONSTANT_FIELD(TabBarFlags, NoCloseWithMiddleMouseButton);
	BIND_ENUM_CONSTANT_FIELD(TabBarFlags, NoTabListScrollingButtons);
	BIND_ENUM_CONSTANT_FIELD(TabBarFlags, NoTooltip);
	BIND_ENUM_CONSTANT_FIELD(TabBarFlags, FittingPolicyResizeDown);
	BIND_ENUM_CONSTANT_FIELD(TabBarFlags, FittingPolicyScroll);
	BIND_ENUM_CONSTANT_FIELD(TabBarFlags, FittingPolicyMask_);
	BIND_ENUM_CONSTANT_FIELD(TabBarFlags, FittingPolicyDefault_);

	BIND_ENUM_CONSTANT_FIELD(TabItemFlags, None);
	BIND_ENUM_CONSTANT_FIELD(TabItemFlags, UnsavedDocument);
	BIND_ENUM_CONSTANT_FIELD(TabItemFlags, SetSelected);
	BIND_ENUM_CONSTANT_FIELD(TabItemFlags, NoCloseWithMiddleMouseButton);
	BIND_ENUM_CONSTANT_FIELD(TabItemFlags, NoPushId);
	BIND_ENUM_CONSTANT_FIELD(TabItemFlags, NoTooltip);
	BIND_ENUM_CONSTANT_FIELD(TabItemFlags, NoReorder);
	BIND_ENUM_CONSTANT_FIELD(TabItemFlags, Leading);
	BIND_ENUM_CONSTANT_FIELD(TabItemFlags, Trailing);
	BIND_ENUM_CONSTANT_FIELD(TabItemFlags, NoAssumedClosure);

	BIND_ENUM_CONSTANT_FIELD(FocusedFlags, None);
	BIND_ENUM_CONSTANT_FIELD(FocusedFlags, ChildWindows);
	BIND_ENUM_CONSTANT_FIELD(FocusedFlags, RootWindow);
	BIND_ENUM_CONSTANT_FIELD(FocusedFlags, AnyWindow);
	BIND_ENUM_CONSTANT_FIELD(FocusedFlags, NoPopupHierarchy);
	BIND_ENUM_CONSTANT_FIELD(FocusedFlags, RootAndChildWindows);

	BIND_ENUM_CONSTANT_FIELD(HoveredFlags, None);
	BIND_ENUM_CONSTANT_FIELD(HoveredFlags, ChildWindows);
	BIND_ENUM_CONSTANT_FIELD(HoveredFlags, RootWindow);
	BIND_ENUM_CONSTANT_FIELD(HoveredFlags, AnyWindow);
	BIND_ENUM_CONSTANT_FIELD(HoveredFlags, NoPopupHierarchy);
	BIND_ENUM_CONSTANT_FIELD(HoveredFlags, AllowWhenBlockedByPopup);
	BIND_ENUM_CONSTANT_FIELD(HoveredFlags, AllowWhenBlockedByActiveItem);
	BIND_ENUM_CONSTANT_FIELD(HoveredFlags, AllowWhenOverlappedByItem);
	BIND_ENUM_CONSTANT_FIELD(HoveredFlags, AllowWhenOverlappedByWindow);
	BIND_ENUM_CONSTANT_FIELD(HoveredFlags, AllowWhenDisabled);
	BIND_ENUM_CONSTANT_FIELD(HoveredFlags, NoNavOverride);
	BIND_ENUM_CONSTANT_FIELD(HoveredFlags, AllowWhenOverlapped);
	BIND_ENUM_CONSTANT_FIELD(HoveredFlags, RectOnly);
	BIND_ENUM_CONSTANT_FIELD(HoveredFlags, RootAndChildWindows);
	BIND_ENUM_CONSTANT_FIELD(HoveredFlags, ForTooltip);
	BIND_ENUM_CONSTANT_FIELD(HoveredFlags, Stationary);
	BIND_ENUM_CONSTANT_FIELD(HoveredFlags, DelayNone);
	BIND_ENUM_CONSTANT_FIELD(HoveredFlags, DelayShort);
	BIND_ENUM_CONSTANT_FIELD(HoveredFlags, DelayNormal);
	BIND_ENUM_CONSTANT_FIELD(HoveredFlags, NoSharedDelay);

	BIND_ENUM_CONSTANT_FIELD(DragDropFlags, None);
	BIND_ENUM_CONSTANT_FIELD(DragDropFlags, SourceNoPreviewTooltip);
	BIND_ENUM_CONSTANT_FIELD(DragDropFlags, SourceNoDisableHover);
	BIND_ENUM_CONSTANT_FIELD(DragDropFlags, SourceNoHoldToOpenOthers);
	BIND_ENUM_CONSTANT_FIELD(DragDropFlags, SourceAllowNullID);
	BIND_ENUM_CONSTANT_FIELD(DragDropFlags, SourceExtern);
	BIND_ENUM_CONSTANT_FIELD(DragDropFlags, SourceAutoExpirePayload);
	BIND_ENUM_CONSTANT_FIELD(DragDropFlags, AcceptBeforeDelivery);
	BIND_ENUM_CONSTANT_FIELD(DragDropFlags, AcceptNoDrawDefaultRect);
	BIND_ENUM_CONSTANT_FIELD(DragDropFlags, AcceptNoPreviewTooltip);
	BIND_ENUM_CONSTANT_FIELD(DragDropFlags, AcceptPeekOnly);

	BIND_ENUM_CONSTANT_FIELD(DataType, S8);
	BIND_ENUM_CONSTANT_FIELD(DataType, U8);
	BIND_ENUM_CONSTANT_FIELD(DataType, S16);
	BIND_ENUM_CONSTANT_FIELD(DataType, U16);
	BIND_ENUM_CONSTANT_FIELD(DataType, S32);
	BIND_ENUM_CONSTANT_FIELD(DataType, U32);
	BIND_ENUM_CONSTANT_FIELD(DataType, S64);
	BIND_ENUM_CONSTANT_FIELD(DataType, U64);
	BIND_ENUM_CONSTANT_FIELD(DataType, Float);
	BIND_ENUM_CONSTANT_FIELD(DataType, Double);
	BIND_ENUM_CONSTANT_FIELD(DataType, COUNT);

	BIND_ENUM_CONSTANT_FIELD(Dir, None);
	BIND_ENUM_CONSTANT_FIELD(Dir, Left);
	BIND_ENUM_CONSTANT_FIELD(Dir, Right);
	BIND_ENUM_CONSTANT_FIELD(Dir, Up);
	BIND_ENUM_CONSTANT_FIELD(Dir, Down);
	BIND_ENUM_CONSTANT_FIELD(Dir, COUNT);

	BIND_ENUM_CONSTANT_FIELD(SortDirection, None);
	BIND_ENUM_CONSTANT_FIELD(SortDirection, Ascending);
	BIND_ENUM_CONSTANT_FIELD(SortDirection, Descending);

	BIND_ENUM_CONSTANT_FIELD(NavInput, Activate);
	BIND_ENUM_CONSTANT_FIELD(NavInput, LStickLeft);
	BIND_ENUM_CONSTANT_FIELD(NavInput, COUNT);

	BIND_ENUM_CONSTANT_FIELD(ConfigFlags, None);
	BIND_ENUM_CONSTANT_FIELD(ConfigFlags, NavEnableKeyboard);
	BIND_ENUM_CONSTANT_FIELD(ConfigFlags, NavEnableGamepad);
	BIND_ENUM_CONSTANT_FIELD(ConfigFlags, NavEnableSetMousePos);
	BIND_ENUM_CONSTANT_FIELD(ConfigFlags, NavNoCaptureKeyboard);
	BIND_ENUM_CONSTANT_FIELD(ConfigFlags, NoMouse);
	BIND_ENUM_CONSTANT_FIELD(ConfigFlags, NoMouseCursorChange);
	BIND_ENUM_CONSTANT_FIELD(ConfigFlags, IsSRGB);
	BIND_ENUM_CONSTANT_FIELD(ConfigFlags, IsTouchScreen);

	BIND_ENUM_CONSTANT_FIELD(BackendFlags, None);
	BIND_ENUM_CONSTANT_FIELD(BackendFlags, HasGamepad);
	BIND_ENUM_CONSTANT_FIELD(BackendFlags, HasMouseCursors);
	BIND_ENUM_CONSTANT_FIELD(BackendFlags, HasSetMousePos);
	BIND_ENUM_CONSTANT_FIELD(BackendFlags, RendererHasVtxOffset);

	BIND_ENUM_CONSTANT_FIELD(Col, Text);
	BIND_ENUM_CONSTANT_FIELD(Col, TextDisabled);
	BIND_ENUM_CONSTANT_FIELD(Col, WindowBg);
	BIND_ENUM_CONSTANT_FIELD(Col, ChildBg);
	BIND_ENUM_CONSTANT_FIELD(Col, PopupBg);
	BIND_ENUM_CONSTANT_FIELD(Col, Border);
	BIND_ENUM_CONSTANT_FIELD(Col, BorderShadow);
	BIND_ENUM_CONSTANT_FIELD(Col, FrameBg);
	BIND_ENUM_CONSTANT_FIELD(Col, FrameBgHovered);
	BIND_ENUM_CONSTANT_FIELD(Col, FrameBgActive);
	BIND_ENUM_CONSTANT_FIELD(Col, TitleBg);
	BIND_ENUM_CONSTANT_FIELD(Col, TitleBgActive);
	BIND_ENUM_CONSTANT_FIELD(Col, TitleBgCollapsed);
	BIND_ENUM_CONSTANT_FIELD(Col, MenuBarBg);
	BIND_ENUM_CONSTANT_FIELD(Col, ScrollbarBg);
	BIND_ENUM_CONSTANT_FIELD(Col, ScrollbarGrab);
	BIND_ENUM_CONSTANT_FIELD(Col, ScrollbarGrabHovered);
	BIND_ENUM_CONSTANT_FIELD(Col, ScrollbarGrabActive);
	BIND_ENUM_CONSTANT_FIELD(Col, CheckMark);
	BIND_ENUM_CONSTANT_FIELD(Col, SliderGrab);
	BIND_ENUM_CONSTANT_FIELD(Col, SliderGrabActive);
	BIND_ENUM_CONSTANT_FIELD(Col, Button);
	BIND_ENUM_CONSTANT_FIELD(Col, ButtonHovered);
	BIND_ENUM_CONSTANT_FIELD(Col, ButtonActive);
	BIND_ENUM_CONSTANT_FIELD(Col, Header);
	BIND_ENUM_CONSTANT_FIELD(Col, HeaderHovered);
	BIND_ENUM_CONSTANT_FIELD(Col, HeaderActive);
	BIND_ENUM_CONSTANT_FIELD(Col, Separator);
	BIND_ENUM_CONSTANT_FIELD(Col, SeparatorHovered);
	BIND_ENUM_CONSTANT_FIELD(Col, SeparatorActive);
	BIND_ENUM_CONSTANT_FIELD(Col, ResizeGrip);
	BIND_ENUM_CONSTANT_FIELD(Col, ResizeGripHovered);
	BIND_ENUM_CONSTANT_FIELD(Col, ResizeGripActive);
	BIND_ENUM_CONSTANT_FIELD(Col, Tab);
	BIND_ENUM_CONSTANT_FIELD(Col, TabHovered);
	BIND_ENUM_CONSTANT_FIELD(Col, TabActive);
	BIND_ENUM_CONSTANT_FIELD(Col, TabUnfocused);
	BIND_ENUM_CONSTANT_FIELD(Col, TabUnfocusedActive);
	BIND_ENUM_CONSTANT_FIELD(Col, PlotLines);
	BIND_ENUM_CONSTANT_FIELD(Col, PlotLinesHovered);
	BIND_ENUM_CONSTANT_FIELD(Col, PlotHistogram);
	BIND_ENUM_CONSTANT_FIELD(Col, PlotHistogramHovered);
	BIND_ENUM_CONSTANT_FIELD(Col, TableHeaderBg);
	BIND_ENUM_CONSTANT_FIELD(Col, TableBorderStrong);
	BIND_ENUM_CONSTANT_FIELD(Col, TableBorderLight);
	BIND_ENUM_CONSTANT_FIELD(Col, TableRowBg);
	BIND_ENUM_CONSTANT_FIELD(Col, TableRowBgAlt);
	BIND_ENUM_CONSTANT_FIELD(Col, TextSelectedBg);
	BIND_ENUM_CONSTANT_FIELD(Col, DragDropTarget);
	BIND_ENUM_CONSTANT_FIELD(Col, NavHighlight);
	BIND_ENUM_CONSTANT_FIELD(Col, NavWindowingHighlight);
	BIND_ENUM_CONSTANT_FIELD(Col, NavWindowingDimBg);
	BIND_ENUM_CONSTANT_FIELD(Col, ModalWindowDimBg);
	BIND_ENUM_CONSTANT_FIELD(Col, COUNT);

	BIND_ENUM_CONSTANT_FIELD(StyleVar, Alpha);
	BIND_ENUM_CONSTANT_FIELD(StyleVar, DisabledAlpha);
	BIND_ENUM_CONSTANT_FIELD(StyleVar, WindowPadding);
	BIND_ENUM_CONSTANT_FIELD(StyleVar, WindowRounding);
	BIND_ENUM_CONSTANT_FIELD(StyleVar, WindowBorderSize);
	BIND_ENUM_CONSTANT_FIELD(StyleVar, WindowMinSize);
	BIND_ENUM_CONSTANT_FIELD(StyleVar, WindowTitleAlign);
	BIND_ENUM_CONSTANT_FIELD(StyleVar, ChildRounding);
	BIND_ENUM_CONSTANT_FIELD(StyleVar, ChildBorderSize);
	BIND_ENUM_CONSTANT_FIELD(StyleVar, PopupRounding);
	BIND_ENUM_CONSTANT_FIELD(StyleVar, PopupBorderSize);
	BIND_ENUM_CONSTANT_FIELD(StyleVar, FramePadding);
	BIND_ENUM_CONSTANT_FIELD(StyleVar, FrameRounding);
	BIND_ENUM_CONSTANT_FIELD(StyleVar, FrameBorderSize);
	BIND_ENUM_CONSTANT_FIELD(StyleVar, ItemSpacing);
	BIND_ENUM_CONSTANT_FIELD(StyleVar, ItemInnerSpacing);
	BIND_ENUM_CONSTANT_FIELD(StyleVar, IndentSpacing);
	BIND_ENUM_CONSTANT_FIELD(StyleVar, CellPadding);
	BIND_ENUM_CONSTANT_FIELD(StyleVar, ScrollbarSize);
	BIND_ENUM_CONSTANT_FIELD(StyleVar, ScrollbarRounding);
	BIND_ENUM_CONSTANT_FIELD(StyleVar, GrabMinSize);
	BIND_ENUM_CONSTANT_FIELD(StyleVar, GrabRounding);
	BIND_ENUM_CONSTANT_FIELD(StyleVar, TabRounding);
	BIND_ENUM_CONSTANT_FIELD(StyleVar, TabBarBorderSize);
	BIND_ENUM_CONSTANT_FIELD(StyleVar, ButtonTextAlign);
	BIND_ENUM_CONSTANT_FIELD(StyleVar, SelectableTextAlign);
	BIND_ENUM_CONSTANT_FIELD(StyleVar, SeparatorTextBorderSize);
	BIND_ENUM_CONSTANT_FIELD(StyleVar, SeparatorTextAlign);
	BIND_ENUM_CONSTANT_FIELD(StyleVar, SeparatorTextPadding);
	BIND_ENUM_CONSTANT_FIELD(StyleVar, COUNT);

	BIND_ENUM_CONSTANT_FIELD(ButtonFlags, None);
	BIND_ENUM_CONSTANT_FIELD(ButtonFlags, MouseButtonLeft);
	BIND_ENUM_CONSTANT_FIELD(ButtonFlags, MouseButtonRight);
	BIND_ENUM_CONSTANT_FIELD(ButtonFlags, MouseButtonMiddle);
	BIND_ENUM_CONSTANT_FIELD(ButtonFlags, MouseButtonMask_);
	BIND_ENUM_CONSTANT_FIELD(ButtonFlags, MouseButtonDefault_);

	BIND_ENUM_CONSTANT_FIELD(ColorEditFlags, None);
	BIND_ENUM_CONSTANT_FIELD(ColorEditFlags, NoAlpha);
	BIND_ENUM_CONSTANT_FIELD(ColorEditFlags, NoPicker);
	BIND_ENUM_CONSTANT_FIELD(ColorEditFlags, NoOptions);
	BIND_ENUM_CONSTANT_FIELD(ColorEditFlags, NoSmallPreview);
	BIND_ENUM_CONSTANT_FIELD(ColorEditFlags, NoInputs);
	BIND_ENUM_CONSTANT_FIELD(ColorEditFlags, NoTooltip);
	BIND_ENUM_CONSTANT_FIELD(ColorEditFlags, NoLabel);
	BIND_ENUM_CONSTANT_FIELD(ColorEditFlags, NoSidePreview);
	BIND_ENUM_CONSTANT_FIELD(ColorEditFlags, NoDragDrop);
	BIND_ENUM_CONSTANT_FIELD(ColorEditFlags, NoBorder);
	BIND_ENUM_CONSTANT_FIELD(ColorEditFlags, AlphaBar);
	BIND_ENUM_CONSTANT_FIELD(ColorEditFlags, AlphaPreview);
	BIND_ENUM_CONSTANT_FIELD(ColorEditFlags, AlphaPreviewHalf);
	BIND_ENUM_CONSTANT_FIELD(ColorEditFlags, HDR);
	BIND_ENUM_CONSTANT_FIELD(ColorEditFlags, DisplayRGB);
	BIND_ENUM_CONSTANT_FIELD(ColorEditFlags, DisplayHSV);
	BIND_ENUM_CONSTANT_FIELD(ColorEditFlags, DisplayHex);
	BIND_ENUM_CONSTANT_FIELD(ColorEditFlags, Uint8);
	BIND_ENUM_CONSTANT_FIELD(ColorEditFlags, Float);
	BIND_ENUM_CONSTANT_FIELD(ColorEditFlags, PickerHueBar);
	BIND_ENUM_CONSTANT_FIELD(ColorEditFlags, PickerHueWheel);
	BIND_ENUM_CONSTANT_FIELD(ColorEditFlags, InputRGB);
	BIND_ENUM_CONSTANT_FIELD(ColorEditFlags, InputHSV);
	BIND_ENUM_CONSTANT_FIELD(ColorEditFlags, DefaultOptions_);

	BIND_ENUM_CONSTANT_FIELD(SliderFlags, None);
	BIND_ENUM_CONSTANT_FIELD(SliderFlags, AlwaysClamp);
	BIND_ENUM_CONSTANT_FIELD(SliderFlags, Logarithmic);
	BIND_ENUM_CONSTANT_FIELD(SliderFlags, NoRoundToFormat);
	BIND_ENUM_CONSTANT_FIELD(SliderFlags, NoInput);
	BIND_ENUM_CONSTANT_FIELD(SliderFlags, InvalidMask_);

	BIND_ENUM_CONSTANT_FIELD(MouseButton, Left);
	BIND_ENUM_CONSTANT_FIELD(MouseButton, Right);
	BIND_ENUM_CONSTANT_FIELD(MouseButton, Middle);
	BIND_ENUM_CONSTANT_FIELD(MouseButton, COUNT);

	BIND_ENUM_CONSTANT_FIELD(MouseCursor, None);
	BIND_ENUM_CONSTANT_FIELD(MouseCursor, Arrow);
	BIND_ENUM_CONSTANT_FIELD(MouseCursor, TextInput);
	BIND_ENUM_CONSTANT_FIELD(MouseCursor, ResizeAll);
	BIND_ENUM_CONSTANT_FIELD(MouseCursor, ResizeNS);
	BIND_ENUM_CONSTANT_FIELD(MouseCursor, ResizeEW);
	BIND_ENUM_CONSTANT_FIELD(MouseCursor, ResizeNESW);
	BIND_ENUM_CONSTANT_FIELD(MouseCursor, ResizeNWSE);
	BIND_ENUM_CONSTANT_FIELD(MouseCursor, Hand);
	BIND_ENUM_CONSTANT_FIELD(MouseCursor, NotAllowed);
	BIND_ENUM_CONSTANT_FIELD(MouseCursor, COUNT);

	BIND_ENUM_CONSTANT_FIELD(MouseSource, Mouse);
	BIND_ENUM_CONSTANT_FIELD(MouseSource, TouchScreen);
	BIND_ENUM_CONSTANT_FIELD(MouseSource, Pen);
	BIND_ENUM_CONSTANT_FIELD(MouseSource, COUNT);

	BIND_ENUM_CONSTANT_FIELD(Cond, None);
	BIND_ENUM_CONSTANT_FIELD(Cond, Always);
	BIND_ENUM_CONSTANT_FIELD(Cond, Once);
	BIND_ENUM_CONSTANT_FIELD(Cond, FirstUseEver);
	BIND_ENUM_CONSTANT_FIELD(Cond, Appearing);

	BIND_ENUM_CONSTANT_FIELD(TableFlags, None);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, Resizable);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, Reorderable);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, Hideable);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, Sortable);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, NoSavedSettings);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, ContextMenuInBody);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, RowBg);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, BordersInnerH);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, BordersOuterH);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, BordersInnerV);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, BordersOuterV);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, BordersH);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, BordersV);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, BordersInner);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, BordersOuter);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, Borders);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, NoBordersInBody);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, NoBordersInBodyUntilResize);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, SizingFixedFit);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, SizingFixedSame);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, SizingStretchProp);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, SizingStretchSame);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, NoHostExtendX);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, NoHostExtendY);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, NoKeepColumnsVisible);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, PreciseWidths);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, NoClip);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, PadOuterX);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, NoPadOuterX);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, NoPadInnerX);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, ScrollX);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, ScrollY);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, SortMulti);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, SortTristate);
	BIND_ENUM_CONSTANT_FIELD(TableFlags, HighlightHoveredColumn);

	BIND_ENUM_CONSTANT_FIELD(TableColumnFlags, None);
	BIND_ENUM_CONSTANT_FIELD(TableColumnFlags, Disabled);
	BIND_ENUM_CONSTANT_FIELD(TableColumnFlags, DefaultHide);
	BIND_ENUM_CONSTANT_FIELD(TableColumnFlags, DefaultSort);
	BIND_ENUM_CONSTANT_FIELD(TableColumnFlags, WidthStretch);
	BIND_ENUM_CONSTANT_FIELD(TableColumnFlags, WidthFixed);
	BIND_ENUM_CONSTANT_FIELD(TableColumnFlags, NoResize);
	BIND_ENUM_CONSTANT_FIELD(TableColumnFlags, NoReorder);
	BIND_ENUM_CONSTANT_FIELD(TableColumnFlags, NoHide);
	BIND_ENUM_CONSTANT_FIELD(TableColumnFlags, NoClip);
	BIND_ENUM_CONSTANT_FIELD(TableColumnFlags, NoSort);
	BIND_ENUM_CONSTANT_FIELD(TableColumnFlags, NoSortAscending);
	BIND_ENUM_CONSTANT_FIELD(TableColumnFlags, NoSortDescending);
	BIND_ENUM_CONSTANT_FIELD(TableColumnFlags, NoHeaderLabel);
	BIND_ENUM_CONSTANT_FIELD(TableColumnFlags, NoHeaderWidth);
	BIND_ENUM_CONSTANT_FIELD(TableColumnFlags, PreferSortAscending);
	BIND_ENUM_CONSTANT_FIELD(TableColumnFlags, PreferSortDescending);
	BIND_ENUM_CONSTANT_FIELD(TableColumnFlags, IndentEnable);
	BIND_ENUM_CONSTANT_FIELD(TableColumnFlags, IndentDisable);
	BIND_ENUM_CONSTANT_FIELD(TableColumnFlags, AngledHeader);
	BIND_ENUM_CONSTANT_FIELD(TableColumnFlags, IsEnabled);
	BIND_ENUM_CONSTANT_FIELD(TableColumnFlags, IsVisible);
	BIND_ENUM_CONSTANT_FIELD(TableColumnFlags, IsSorted);
	BIND_ENUM_CONSTANT_FIELD(TableColumnFlags, IsHovered);

	BIND_ENUM_CONSTANT_FIELD(TableRowFlags, None);
	BIND_ENUM_CONSTANT_FIELD(TableRowFlags, Headers);

	BIND_ENUM_CONSTANT_FIELD(TableBgTarget, None);
	BIND_ENUM_CONSTANT_FIELD(TableBgTarget, RowBg0);
	BIND_ENUM_CONSTANT_FIELD(TableBgTarget, RowBg1);
	BIND_ENUM_CONSTANT_FIELD(TableBgTarget, CellBg);
	
	
	
	
	
	
	BIND_ENUM_CONSTANT_FIELD(Key, None);
	BIND_ENUM_CONSTANT_FIELD(Key, Tab);
	BIND_ENUM_CONSTANT_FIELD(Key, LeftArrow);
	BIND_ENUM_CONSTANT_FIELD(Key, RightArrow);
	BIND_ENUM_CONSTANT_FIELD(Key, UpArrow);
	BIND_ENUM_CONSTANT_FIELD(Key, DownArrow);
	BIND_ENUM_CONSTANT_FIELD(Key, PageUp);
	BIND_ENUM_CONSTANT_FIELD(Key, PageDown);
	BIND_ENUM_CONSTANT_FIELD(Key, Home);
	BIND_ENUM_CONSTANT_FIELD(Key, End);
	BIND_ENUM_CONSTANT_FIELD(Key, Insert);
	BIND_ENUM_CONSTANT_FIELD(Key, Delete);
	BIND_ENUM_CONSTANT_FIELD(Key, Backspace);
	BIND_ENUM_CONSTANT_FIELD(Key, Space);
	BIND_ENUM_CONSTANT_FIELD(Key, Enter);
	BIND_ENUM_CONSTANT_FIELD(Key, Escape);
	BIND_ENUM_CONSTANT_FIELD(Key, LeftCtrl);
	BIND_ENUM_CONSTANT_FIELD(Key, LeftShift);
	BIND_ENUM_CONSTANT_FIELD(Key, LeftAlt);
	BIND_ENUM_CONSTANT_FIELD(Key, LeftSuper);
	BIND_ENUM_CONSTANT_FIELD(Key, RightCtrl);
	BIND_ENUM_CONSTANT_FIELD(Key, RightShift);
	BIND_ENUM_CONSTANT_FIELD(Key, RightAlt);
	BIND_ENUM_CONSTANT_FIELD(Key, RightSuper);
	BIND_ENUM_CONSTANT_FIELD(Key, Menu);
	BIND_ENUM_CONSTANT_FIELD(Key, 0);
	BIND_ENUM_CONSTANT_FIELD(Key, 1);
	BIND_ENUM_CONSTANT_FIELD(Key, 2);
	BIND_ENUM_CONSTANT_FIELD(Key, 3);
	BIND_ENUM_CONSTANT_FIELD(Key, 4);
	BIND_ENUM_CONSTANT_FIELD(Key, 5);
	BIND_ENUM_CONSTANT_FIELD(Key, 6);
	BIND_ENUM_CONSTANT_FIELD(Key, 7);
	BIND_ENUM_CONSTANT_FIELD(Key, 8);
	BIND_ENUM_CONSTANT_FIELD(Key, 9);
	BIND_ENUM_CONSTANT_FIELD(Key, A);
	BIND_ENUM_CONSTANT_FIELD(Key, B);
	BIND_ENUM_CONSTANT_FIELD(Key, C);
	BIND_ENUM_CONSTANT_FIELD(Key, D);
	BIND_ENUM_CONSTANT_FIELD(Key, E);
	BIND_ENUM_CONSTANT_FIELD(Key, F);
	BIND_ENUM_CONSTANT_FIELD(Key, G);
	BIND_ENUM_CONSTANT_FIELD(Key, H);
	BIND_ENUM_CONSTANT_FIELD(Key, I);
	BIND_ENUM_CONSTANT_FIELD(Key, J);
	BIND_ENUM_CONSTANT_FIELD(Key, K);
	BIND_ENUM_CONSTANT_FIELD(Key, L);
	BIND_ENUM_CONSTANT_FIELD(Key, M);
	BIND_ENUM_CONSTANT_FIELD(Key, N);
	BIND_ENUM_CONSTANT_FIELD(Key, O);
	BIND_ENUM_CONSTANT_FIELD(Key, P);
	BIND_ENUM_CONSTANT_FIELD(Key, Q);
	BIND_ENUM_CONSTANT_FIELD(Key, R);
	BIND_ENUM_CONSTANT_FIELD(Key, S);
	BIND_ENUM_CONSTANT_FIELD(Key, T);
	BIND_ENUM_CONSTANT_FIELD(Key, U);
	BIND_ENUM_CONSTANT_FIELD(Key, V);
	BIND_ENUM_CONSTANT_FIELD(Key, W);
	BIND_ENUM_CONSTANT_FIELD(Key, X);
	BIND_ENUM_CONSTANT_FIELD(Key, Y);
	BIND_ENUM_CONSTANT_FIELD(Key, Z);
	BIND_ENUM_CONSTANT_FIELD(Key, F1);
	BIND_ENUM_CONSTANT_FIELD(Key, F2);
	BIND_ENUM_CONSTANT_FIELD(Key, F3);
	BIND_ENUM_CONSTANT_FIELD(Key, F4);
	BIND_ENUM_CONSTANT_FIELD(Key, F5);
	BIND_ENUM_CONSTANT_FIELD(Key, F6);
	BIND_ENUM_CONSTANT_FIELD(Key, F7);
	BIND_ENUM_CONSTANT_FIELD(Key, F8);
	BIND_ENUM_CONSTANT_FIELD(Key, F9);
	BIND_ENUM_CONSTANT_FIELD(Key, F10);
	BIND_ENUM_CONSTANT_FIELD(Key, F11);
	BIND_ENUM_CONSTANT_FIELD(Key, F12);
	BIND_ENUM_CONSTANT_FIELD(Key, F13);
	BIND_ENUM_CONSTANT_FIELD(Key, F14);
	BIND_ENUM_CONSTANT_FIELD(Key, F15);
	BIND_ENUM_CONSTANT_FIELD(Key, F16);
	BIND_ENUM_CONSTANT_FIELD(Key, F17);
	BIND_ENUM_CONSTANT_FIELD(Key, F18);
	BIND_ENUM_CONSTANT_FIELD(Key, F19);
	BIND_ENUM_CONSTANT_FIELD(Key, F20);
	BIND_ENUM_CONSTANT_FIELD(Key, F21);
	BIND_ENUM_CONSTANT_FIELD(Key, F22);
	BIND_ENUM_CONSTANT_FIELD(Key, F23);
	BIND_ENUM_CONSTANT_FIELD(Key, F24);
	BIND_ENUM_CONSTANT_FIELD(Key, Apostrophe);
	BIND_ENUM_CONSTANT_FIELD(Key, Comma);
	BIND_ENUM_CONSTANT_FIELD(Key, Minus);
	BIND_ENUM_CONSTANT_FIELD(Key, Period);
	BIND_ENUM_CONSTANT_FIELD(Key, Slash);
	BIND_ENUM_CONSTANT_FIELD(Key, Semicolon);
	BIND_ENUM_CONSTANT_FIELD(Key, Equal);
	BIND_ENUM_CONSTANT_FIELD(Key, LeftBracket);
	BIND_ENUM_CONSTANT_FIELD(Key, Backslash);
	BIND_ENUM_CONSTANT_FIELD(Key, RightBracket);
	BIND_ENUM_CONSTANT_FIELD(Key, GraveAccent);
	BIND_ENUM_CONSTANT_FIELD(Key, CapsLock);
	BIND_ENUM_CONSTANT_FIELD(Key, ScrollLock);
	BIND_ENUM_CONSTANT_FIELD(Key, NumLock);
	BIND_ENUM_CONSTANT_FIELD(Key, PrintScreen);
	BIND_ENUM_CONSTANT_FIELD(Key, Pause);
	BIND_ENUM_CONSTANT_FIELD(Key, Keypad0);
	BIND_ENUM_CONSTANT_FIELD(Key, Keypad1);
	BIND_ENUM_CONSTANT_FIELD(Key, Keypad2);
	BIND_ENUM_CONSTANT_FIELD(Key, Keypad3);
	BIND_ENUM_CONSTANT_FIELD(Key, Keypad4);
	BIND_ENUM_CONSTANT_FIELD(Key, Keypad5);
	BIND_ENUM_CONSTANT_FIELD(Key, Keypad6);
	BIND_ENUM_CONSTANT_FIELD(Key, Keypad7);
	BIND_ENUM_CONSTANT_FIELD(Key, Keypad8);
	BIND_ENUM_CONSTANT_FIELD(Key, Keypad9);
	BIND_ENUM_CONSTANT_FIELD(Key, KeypadDecimal);
	BIND_ENUM_CONSTANT_FIELD(Key, KeypadDivide);
	BIND_ENUM_CONSTANT_FIELD(Key, KeypadMultiply);
	BIND_ENUM_CONSTANT_FIELD(Key, KeypadSubtract);
	BIND_ENUM_CONSTANT_FIELD(Key, KeypadAdd);
	BIND_ENUM_CONSTANT_FIELD(Key, KeypadEnter);
	BIND_ENUM_CONSTANT_FIELD(Key, KeypadEqual);
	BIND_ENUM_CONSTANT_FIELD(Key, AppBack);
	BIND_ENUM_CONSTANT_FIELD(Key, AppForward);

	BIND_ENUM_CONSTANT_FIELD(Key, GamepadStart);
	BIND_ENUM_CONSTANT_FIELD(Key, GamepadBack);
	BIND_ENUM_CONSTANT_FIELD(Key, GamepadFaceLeft);
	BIND_ENUM_CONSTANT_FIELD(Key, GamepadFaceRight);
	BIND_ENUM_CONSTANT_FIELD(Key, GamepadFaceUp);
	BIND_ENUM_CONSTANT_FIELD(Key, GamepadFaceDown);
	BIND_ENUM_CONSTANT_FIELD(Key, GamepadDpadLeft);
	BIND_ENUM_CONSTANT_FIELD(Key, GamepadDpadRight);
	BIND_ENUM_CONSTANT_FIELD(Key, GamepadDpadUp);
	BIND_ENUM_CONSTANT_FIELD(Key, GamepadDpadDown);
	BIND_ENUM_CONSTANT_FIELD(Key, GamepadL1);
	BIND_ENUM_CONSTANT_FIELD(Key, GamepadR1);
	BIND_ENUM_CONSTANT_FIELD(Key, GamepadL2);
	BIND_ENUM_CONSTANT_FIELD(Key, GamepadR2);
	BIND_ENUM_CONSTANT_FIELD(Key, GamepadL3);
	BIND_ENUM_CONSTANT_FIELD(Key, GamepadR3);
	BIND_ENUM_CONSTANT_FIELD(Key, GamepadLStickLeft);
	BIND_ENUM_CONSTANT_FIELD(Key, GamepadLStickRight);
	BIND_ENUM_CONSTANT_FIELD(Key, GamepadLStickUp);
	BIND_ENUM_CONSTANT_FIELD(Key, GamepadLStickDown);
	BIND_ENUM_CONSTANT_FIELD(Key, GamepadRStickLeft);
	BIND_ENUM_CONSTANT_FIELD(Key, GamepadRStickRight);
	BIND_ENUM_CONSTANT_FIELD(Key, GamepadRStickUp);
	BIND_ENUM_CONSTANT_FIELD(Key, GamepadRStickDown);

	BIND_ENUM_CONSTANT_FIELD(Key, MouseLeft);
	BIND_ENUM_CONSTANT_FIELD(Key, MouseRight);
	BIND_ENUM_CONSTANT_FIELD(Key, MouseMiddle);
	BIND_ENUM_CONSTANT_FIELD(Key, MouseX1);
	BIND_ENUM_CONSTANT_FIELD(Key, MouseX2);
	BIND_ENUM_CONSTANT_FIELD(Key, MouseWheelX);
	BIND_ENUM_CONSTANT_FIELD(Key, MouseWheelY);

	BIND_ENUM_CONSTANT_FIELD(Mod, None);
	BIND_ENUM_CONSTANT_FIELD(Mod, Ctrl);
	BIND_ENUM_CONSTANT_FIELD(Mod, Shift);
	BIND_ENUM_CONSTANT_FIELD(Mod, Alt);
	BIND_ENUM_CONSTANT_FIELD(Mod, Super);
	BIND_ENUM_CONSTANT_FIELD(Mod, Shortcut);
	BIND_ENUM_CONSTANT_FIELD(Mod, Mask_);
}
