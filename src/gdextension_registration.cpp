// #include <godot_cpp/godot.hpp>
// #include <godot_cpp/core/class_db.hpp>
//
// #include <gdextension_interface.h>
// #include <godot_cpp/core/defs.hpp>
// #include <godot_cpp/godot.hpp>

#include "../include/godot_imgui_native/gdextension_registration.h"

#include "../include/godot_imgui_native/ImGui.hpp"

void register_gameplay_types(godot::ModuleInitializationLevel p_level)
{
	if (p_level !=
		godot::ModuleInitializationLevel::MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

// 	godot::ClassDB::register_class<GodotImGuiMesh>();
// 	godot::ClassDB::register_class<GodotImGui>();
	// REGISTER CLASSES HERE LATER
}

void unregister_gameplay_types(godot::ModuleInitializationLevel p_level)
{
	// DO NOTHING
}

extern "C" {

GDExtensionBool GDE_EXPORT
imgui_library_init(GDExtensionInterfaceGetProcAddress p_interface,
				   GDExtensionClassLibraryPtr p_library,
				   GDExtensionInitialization *r_initialization)
{
	godot::GDExtensionBinding::InitObject init_object(p_interface, p_library,
													  r_initialization);

	init_object.register_initializer(register_gameplay_types);
	init_object.register_terminator(unregister_gameplay_types);
	init_object.set_minimum_library_initialization_level(
		godot::ModuleInitializationLevel::MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_object.init();
}
}
