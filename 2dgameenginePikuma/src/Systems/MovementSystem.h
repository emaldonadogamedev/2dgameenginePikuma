#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../ECS/ECS.h"

class MovementSystem : public System
{
    public:
        MovementSystem()
        {
            // TODO: specify what components are required
            // transform component
        }

        void Update()
        {
            // TODO:
            // update entity position based on velocity
        }
};

#endif // !MOVEMENTSYSTEM_H
