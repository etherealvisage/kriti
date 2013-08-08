#version 140

#extension GL_ARB_explicit_attrib_location : require

in vec4 v_normal;
out vec4 fragColour;

void main() {
    fragColour = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
