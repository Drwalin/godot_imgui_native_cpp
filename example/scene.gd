extends Node2D


# Called when the node enters the scene tree for the first time.
var font:int = 0;
func _ready():
	font = $"../GodotImGui".GetFont("res://dvu_sans_mono.ttf", 20.0);
	ImGui.SetMouseDrawCursor(true);
	pass;

var img:Texture2D = load("res://icon.svg");

static var checkbox:Vector2i = Vector2i(0,1);

static var time:float = 0;
var textIn1:PackedByteArray;
var textIn2:PackedByteArray;
var vec3i:Vector3i = Vector3i(0,0,0);
# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	time += delta;
	$"../GodotImGui".ImGui_NewFrame();
	
	ImGui.PushStyleColor(ImGui.Col_TextSelectedBg, Color(0, 72.0/255.0, 174.0/255.0, 1));
	ImGui.PushStyleColor(ImGui.Col_Text, Color(1, 1, 1, 1));
	
	ImGui.Begin("Nazwa", 0);
	ImGui.Text("Hello World");
	ImGui.Text("Hello World");
	ImGui.Text("Hello World");
	ImGui.Text("Hello World");
	
	font = $"../GodotImGui".GetFont("res://dvu_sans_mono.ttf", 20.0);
	ImGui.PushFont(font);
	ImGui.Text("Hello World");
	ImGui.PopFont();
	
	vec3i = ImGui.InputInt3("InputInt3", vec3i, 0)[1];
	
	font = $"../GodotImGui".GetFont("res://dvu_sans_mono.ttf", 5.0);
	ImGui.PushFont(font);
	ImGui.Text("Hello World");
	ImGui.PopFont();
	
	font = $"../GodotImGui".GetFont("res://dvu_sans_mono.ttf", 50.0);
	ImGui.PushFont(font);
	ImGui.Text("Hello World");
	ImGui.PopFont();
	
	textIn1 = ImGui.InputText("LabelInputText", textIn1, 1000, ImGui.InputTextFlags_AllowTabInput)[1];
	
	ImGui.ProgressBar(time/10, Vector2(100, 20), "");
	if time > 10:
		time -= 10;
	ImGui.Text("Hello World");
	if (ImGui.ImageButton("imgButt", img, Vector2(50, 50), Rect2(0, 0, 1, 1), Color(1,1,1,1), Color(0,0,0,1))):
		print("Image button pressed");
	ImGui.BeginChild("a", Vector2(100, 50), 0, 0);
	ImGui.Text("Hello World");
	ImGui.Image(img, Vector2(50, 50), Rect2(0, 0, 1, 1), Color(1,1,1,1), Color(0,1,0,1));
	ImGui.EndChild();
	if (ImGui.Button("Przycisk", Vector2(40, 40))):
		print("Pressed");
	checkbox = ImGui.CheckboxFlags("Check", checkbox.y, 4);
	if (checkbox.x !=0):
		print("checkbox: ", checkbox.y);
	ImGui.End();
	
	font = $"../GodotImGui".GetFont("res://dvu_sans_mono.ttf", 20.0);
	ImGui.Begin("fps", ImGui.WindowFlags_AlwaysAutoResize);
	ImGui.PushFont(font);
	ImGui.Text("fps: %s" % Engine.get_frames_per_second());
	ImGui.PopFont();
	ImGui.End();
	
	ImGui.Begin("MultiLineInput", 0);
	textIn2 = ImGui.InputTextMultiline("LabelInputText multi line", textIn2, 10000, Vector2(0,0), ImGui.InputTextFlags_AllowTabInput)[1];
	ImGui.End();
	
	ImGui.PopStyleColor(2);
	
	pass
