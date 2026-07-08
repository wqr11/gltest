#include <Mesh.h>

class Cube : public Mesh
{
public:
    Cube()
    {
        vertices = {
            // Front face (z = 0)
            {0, 0, 0}, // 0
            {0, 1, 0}, // 1
            {1, 1, 0}, // 2
            {1, 0, 0}, // 3
            // Back face (z = 1)
            {0, 0, 1}, // 4
            {0, 1, 1}, // 5
            {1, 1, 1}, // 6
            {1, 0, 1}  // 7
        };

        indices = {
            // Front face
            0, 1, 2,
            0, 2, 3,
            // Back face
            4, 6, 5,
            4, 7, 6,
            // Left face
            0, 4, 5,
            0, 5, 1,
            // Right face
            3, 2, 6,
            3, 6, 7,
            // Bottom face
            0, 3, 7,
            0, 7, 4,
            // Top face
            1, 5, 6,
            1, 6, 2};
    }
};