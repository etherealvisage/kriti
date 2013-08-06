#version 130

in vec4 v_normal;
in vec2 v_tex;
out vec4 fragColour;

uniform sampler2D lastStage;

void main() {
    //fragColour = vec4(v_tex.x, v_tex.y, 0.0f, 1.0f);
    //fragColour.b = texture(lastStage, v_tex);
    vec4 result = texture(lastStage, v_tex/2);
    fragColour = result;
    fragColour.a = 1.0f;
}
