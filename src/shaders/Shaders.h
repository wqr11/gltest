#include <cstring>

constexpr int32_t strlen_c(const char *str)
{
    int32_t size = 0;

    while (*str++)
    {
        ++size;
    }

    return size;
}

constexpr char VERTEX_SHADER_SOURCE[] = {
#include "vertex.glsl"
};
constexpr char FRAGMENT_SHADER_SOURCE[] = {
#include "fragment.glsl"
};

constexpr int32_t VERTEX_SHADER_SIZE = strlen_c(VERTEX_SHADER_SOURCE);
constexpr int32_t FRAGMENT_SHADER_SIZE = strlen_c(FRAGMENT_SHADER_SOURCE);