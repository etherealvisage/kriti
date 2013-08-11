#version 140

#extension GL_ARB_explicit_attrib_location : require

const float pi = 3.14159265;

in vec4 v_position;
in vec4 v_normal;
in vec2 v_tex;
out vec4 fragColour;

uniform int time;
uniform float gui_xscale, gui_yscale;
uniform float button_xscale, button_yscale;
uniform float gui_trans;
uniform float button_activation, button_click;

void main() {
    float xdist = (min(v_tex.x, 1.0f-v_tex.x) / gui_xscale) * button_xscale;
    float ydist = (min(v_tex.y, 1.0f-v_tex.y) / gui_yscale) * button_yscale;

    vec4 highlight = vec4(0.3f, 0.3f, 0.5f, 1.0f);
    float tensec_progress = (time % 5000) / 5000.0f;
    float highlight_mix = pow(0.1f, distance(v_position.x+1.3f, tensec_progress*2.6f)*8)/8.0f;

    if(xdist <= 5.0f || ydist <= 5.0f) {
        vec4 activated = vec4(1.0f, 1.0f, 0.0f, 1.0f);
        vec4 deactivated = vec4(0.1f, 0.1f, 0.0f, 1.0f);
        vec4 border = mix(deactivated, activated, button_activation);
        fragColour = mix(vec4(0.4f, 0.4f, 0.0f, 1.0f), border,
            distance(5.0f, min(xdist,ydist)) / 5.0f);
    }
    else {
        vec4 activated = vec4(0.1f, 0.1f, 0.0f, 1.0f);
        vec4 deactivated = vec4(0.4f, 0.4f, 0.0f, 1.0f);
        fragColour = mix(deactivated, activated, button_activation);
        vec4 clicked = vec4(0.4f, 0.4f, 0.4f, 1.0f);
        fragColour = mix(fragColour, clicked, button_click/2.0f);
    }
    fragColour = mix(fragColour, highlight, highlight_mix);
}