#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float time;
uniform vec3 v_color;
uniform int type;

out vec3 frag_color;

float rand(in vec3 co){
    return fract(sin(dot(co.xyz ,vec3(12.34,56.78,910.1112))) * 13141.516);
}

void main()
{
	frag_color = v_color;

	vec3 wiggled = v_position;
	if (type == 1) { // player power Up
		wiggled = v_position + rand(v_position) * v_position;
		frag_color = v_color + vec3(rand(v_color), rand(gl_VertexID * v_color), rand(gl_VertexID * 2 * v_color));
	}

	if (type == 2) { // player death
		wiggled = - (1 / (time * 5)) * rand(v_position) * 3 * v_position;
		frag_color = v_color * rand(gl_VertexID * v_color);
	}

	if (type == 4) { // obstacle death
		float aux = v_position.y - time * 0.35;
		wiggled = vec3(v_position.x, max(-0.4, aux), v_position.z);
	}

	gl_Position = Projection * View * Model * vec4(wiggled, 1.0);

	if (type == 3) { // GUI
		gl_Position = Model * vec4(v_position.x, v_position.y, 0.0, 1.0);
	}
}
