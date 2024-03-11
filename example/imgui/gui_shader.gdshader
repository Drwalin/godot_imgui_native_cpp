shader_type canvas_item;
render_mode unshaded;

uniform vec4 scissor_test;

void vertex() {
	VERTEX = (CANVAS_MATRIX * vec4(VERTEX, 0.0, 1.0)).xy;
}

void fragment() {
	if (POINT_COORD.x < scissor_test.x || POINT_COORD.x > scissor_test.z ||
		POINT_COORD.y < scissor_test.y || POINT_COORD.y > scissor_test.w) {
		discard;
	} else {
		//if (has_texture) {
		//	COLOR *= texture(TEXTURE, UV);
		//} else {
			// COLOR = COLOR;
		//}
	}
}
