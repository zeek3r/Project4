#version 400 core
in vec2 pos;
in vec2 UV;

out vec2 uv;

uniform mat4 ortho;
uniform vec2 position;
uniform float zoom;
void main(){
	vec2 v = UV;
	v.y *= -1;
	uv = v;
	gl_Position = ortho * vec4((pos + position) * zoom,0,1);
}