#version 150

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

void main() {
    /* identity geometry shader */
    for(int i = 0; i < 3; i ++) {
        gl_PrimitiveID = gl_PrimitiveIDIn;
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    EndPrimitive();
}
