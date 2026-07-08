#include <glm/vec3.hpp>

using namespace glm;

class Vertex
{
public:
    Vertex(float x, float y, float z) : position(x, y, z) {};

    vec3 position;
};