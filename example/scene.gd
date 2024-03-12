extends Node2D


# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

var img:Texture2D = load("res://icon.svg");

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
	ImGui.Image(img, Vector2(50, 50), Rect2(0, 0, 1, 1), Color(1,1,1,1), Color(0,0,0,1));
	ImGui.BeginChild("a", Vector2(100, 50), 0, 0);
	ImGui.Text("Hello World");
	ImGui.Image(img, Vector2(50, 50), Rect2(0, 0, 1, 1), Color(1,1,1,1), Color(0,1,0,1));
	ImGui.EndChild();
	ImGui.End();
	
	pass
