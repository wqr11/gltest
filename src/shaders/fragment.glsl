R"(
#version 330 core

in vec3 barycentric;
in vec2 fTexCoords;

uniform vec3 wireframeColor = vec3(0.0, 0.0, 0.0);
uniform sampler2D fTexture;

out vec4 FragColor;

void main()
{
    float wireframeWidth = 0.01f;

    // [0; 1]
    float edgeDist = min(min(barycentric.x, barycentric.y), barycentric.z);

    // [0; 1]
    float fillWidth = 1.0 - smoothstep(0.0, wireframeWidth, edgeDist);

    vec4 color = mix(vec4(1.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 0.0f), fillWidth);

    FragColor = color;
    // FragColor = mix(texture(fTexture, fTexCoords), color, 0.5f);
})"
