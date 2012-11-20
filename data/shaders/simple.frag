#version 130

#extension GL_ARB_explicit_attrib_location : require

layout(location = 0) out vec4 fragColour;

void main() {
    fragColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
