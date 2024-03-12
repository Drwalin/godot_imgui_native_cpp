extends Node2D


# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	$"../GodotImGui".ImGui_NewFrame();
	ImGui.Begin("Nazwa", 0);
	ImGui.Text("Hello World");
	ImGui.Text("Hello World");
	ImGui.Text("Hello World");
	ImGui.Text("Hello World");
	ImGui.Text("Hello World");
	ImGui.Text("Hello World");
	ImGui.Text("Hello World");
	ImGui.End();
	
	pass
