#version 130

#extension GL_ARB_explicit_attrib_location : require

in vec4 v_position;
in vec4 v_normal;
out vec4 fragColour;

void main() {
    //fragColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    /*fragColour = max(0, dot(v_normal, vec4(0.0f, 0.0f, 1.0f, 0.0f)))
        * vec4(0.9f, 0.9f, 0.9f, 0.0f)
        + vec4(0.1f, 0.1f, 0.1f, 1.0f);*/
    //fragColour = sqrt(abs(v_normal.z))*vec4(1,1,1,0) + vec4(0,0,0,1);
    //fragColour = vec4(sqrt(sin(mod(v_position.x*2, 3.1415926))),0,0,0) + vec4(0,0,0,1);
    //fragColour = vec4(.1f,.1f,.1f,1f);
    fragColour = max(0, v_normal.y)*vec4(0.9f,0.9f,0.9f,0.0f)
        + vec4(0.1f,0.1f,0.1f,1.0f);
}
