R"(
#version 330 core

in vec3 barycentric;

uniform float wireframeWidth = 0.01;
uniform vec3 wireframeColor = vec3(0.0,0.0,0.0);
out vec4 FragColor;

void main()
{
    // = minBary
    float edgeDist = min(min(barycentric.x, barycentric.y), barycentric.z);

    float fillWidth = 1.0 - smoothstep(0.0, wireframeWidth, edgeDist);

    FragColor = vec4(mix(vec3(1.0, 0.0, 0.0), wireframeColor, fillWidth), 1.0f);
})"