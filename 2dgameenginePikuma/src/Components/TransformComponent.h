#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <glm/glm.hpp>

struct TransformComponent
{
    TransformComponent(
        glm::vec2 position = glm::vec2(0.f,0.f),
        glm::vec2 scale = glm::vec2(1.f, 1.f),
        float rotation = 0.f):
        position(position),
        scale(scale),
        rotation(rotation)
    {
    }

    glm::vec2 position;
    glm::vec2 scale;
    float rotation;
};

#endif // !TRANSFORMCOMPONENT_H
