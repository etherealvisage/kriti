#version 150

layout (triangles) in;
layout (triangle_strip, max_vertices = 6) out;

in vec4 v_position[3];
in vec4 v_normal[3];
in vec2 v_tex[3];

out vec4 g_position;
out vec4 g_normal;
out vec2 g_tex;

void main() {
    for(int i = 0; i < 3; i ++) {
        gl_PrimitiveID = gl_PrimitiveIDIn;
        gl_Position = gl_in[i].gl_Position + vec4(0.0,2.0,0.0,0.0);
        g_position = v_position[i] + vec4(0.0,2.0,0.0,0.0);
        g_normal = v_normal[i];
        g_tex = v_tex[i];
        EmitVertex();
    }
    EndPrimitive();
    for(int i = 0; i < 3; i ++) {
        gl_PrimitiveID = gl_PrimitiveIDIn;
        gl_Position = gl_in[i].gl_Position + vec4(0.0,-2.0,0.0,0.0);
        g_position = v_position[i] + vec4(0.0,-2.0,0.0,0.0);
        g_normal = v_normal[i];
        g_tex = v_tex[i];
        EmitVertex();
    }
    EndPrimitive();
}
