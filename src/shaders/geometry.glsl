R"(
#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec2 gTexCoords[];

out vec3 barycentric;
out vec2 fTexCoords;

void main () {
    // Vertex 0
    gl_Position = gl_in[0].gl_Position;
    barycentric = vec3(1.0, 0.0, 0.0);
    fTexCoords = gTexCoords[0];
    EmitVertex();

    // Vertex 1
    gl_Position = gl_in[1].gl_Position;
    barycentric = vec3(0.0, 1.0, 0.0);
    fTexCoords = gTexCoords[1];
    EmitVertex();

    // Vertex 2
    gl_Position = gl_in[2].gl_Position;
    barycentric = vec3(0.0, 0.0, 1.0);
    fTexCoords = gTexCoords[2];
    EmitVertex();

    EndPrimitive();
})"
