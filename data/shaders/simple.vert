#version 130

#extension GL_ARB_explicit_attrib_location : require

layout(location = 0) in vec4 position;

uniform mat4 projection;

void main() {
    gl_Position = projection * position;
}
