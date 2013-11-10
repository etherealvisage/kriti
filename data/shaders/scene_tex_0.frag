#version 140

#extension GL_ARB_explicit_attrib_location : require

in vec4 v_position;
in vec4 v_normal;
out vec4 fragColour;

uniform vec3 u_ambient, u_diffuse, u_specular;
uniform float u_specularPower, u_specularScale;

void main() {
    /*fragColour = max(0, v_normal.y)*vec4(0.9f,0.9f,0.9f,0.0f)
        + vec4(0.1f,0.1f,0.1f,1.0f);*/

    fragColour = u_ambient;
}
