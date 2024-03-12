shader_type canvas_item;
render_mode unshaded;

uniform vec4 scissor_test;

void vertex() {
//	VERTEX = VERTEX;//(SCREEN_MATRIX * vec4(VERTEX, 0.0, 1.0)).xy;
}

void fragment() {
	if (FRAGCOORD.x < scissor_test.x || FRAGCOORD.x > scissor_test.z ||
		FRAGCOORD.y < scissor_test.y || FRAGCOORD.y > scissor_test.w) {
		discard;
		COLOR = COLOR*texture(TEXTURE, UV);
		COLOR.x = 0.5;
	} else {
		COLOR = COLOR*texture(TEXTURE, UV);
	}
}
