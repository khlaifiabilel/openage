#version 330

layout(location=0) in vec2 position;
layout(location=1) in vec2 uv;

out vec2 v_uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform vec4 offset_tile;

float width = offset_tile.y - offset_tile.x;
float height = offset_tile.w - offset_tile.z;

void main() {
	gl_Position = proj * view * model * vec4(position, 0.0, 1.0);
	// gl_Position = vec4(position, 0.0, 1.0);
    v_uv = vec2((uv.x * width) + offset_tile.x, (((1.0 - uv.y) * height) + offset_tile.z));
}
