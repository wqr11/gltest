R"(
#version 330 core

in vec3 barycentric;
in vec2 fTexCoords;

uniform float wireframeWidth = 0.01;
uniform vec3 wireframeColor = vec3(0.0,0.0,0.0);
uniform sampler2D fTexture;

out vec4 FragColor;

void main()
{
    // = minBary
    float edgeDist = min(min(barycentric.x, barycentric.y), barycentric.z);

    // range [0; 1]
    float fillWidth = 1.0 - smoothstep(0.0, wireframeWidth, edgeDist);

    // FragColor = vec4(mix(vec3(1.0, 0.0, 0.0), wireframeColor, fillWidth), 1.0f);

    FragColor = texture(fTexture, fTexCoords);// * vec4(mix(wireframeColor, vec3(1.0,0.0,0.0), fillWidth), 1.0f);
})"
