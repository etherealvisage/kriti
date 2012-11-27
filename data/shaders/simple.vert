#version 130

#extension GL_ARB_explicit_attrib_location : require

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 camera;
uniform mat4 model;

void main() {
    gl_Position = camera * model * vec4(position, 1.0);
}
