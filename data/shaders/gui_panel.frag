#version 140

#extension GL_ARB_explicit_attrib_location : require

const float pi = 3.14159265;

in vec4 v_normal;
in vec2 v_tex;
out vec4 fragColour;

uniform int time;
uniform float gui_xscale, gui_yscale;
uniform float panel_xscale, panel_yscale;
uniform float gui_trans;

void main() {
    float xdist = (min(v_tex.x, 1.0f-v_tex.x) / gui_xscale) * panel_xscale;
    float ydist = (min(v_tex.y, 1.0f-v_tex.y) / gui_yscale) * panel_yscale;

    if(xdist <= 3.0f || ydist <= 3.0f) {
        float value = (distance(3.0f, min(xdist,ydist))+1.0) / 3.0;
        fragColour = vec4(value, value, 0.0f, gui_trans);
    }
    else {
        fragColour = vec4(0.3f, 0.3f, 0.0f, gui_trans);
    }
}
