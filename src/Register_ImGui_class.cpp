#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

void CrossCallFrom_ImGui_to_Godot_ImGui_method_bingings();

class ImGui : public godot::Object
{
	GDCLASS(ImGui, Object)
public:
	static void _bind_methods()
	{
		CrossCallFrom_ImGui_to_Godot_ImGui_method_bingings();
	}
};

void Register_ImGui_class()
{
	godot::ClassDB::register_abstract_class<ImGui>();
}
