#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

void register_gameplay_types(godot::ModuleInitializationLevel p_level);
void unregister_gameplay_types(godot::ModuleInitializationLevel p_level);

void Register_ImGui_class();
