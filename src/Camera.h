#include <glm/mat4x4.hpp>

using namespace glm;

class Camera
{

public:
    mat4 viewMatrix;
    mat4 perspectiveMatrix;
};