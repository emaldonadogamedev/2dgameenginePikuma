#ifndef ECS_H
#define ECS_H

#include <bitset>

#include <vector>

const unsigned MAX_COMPONENTS = 64U;

///////////////////////////////////////////////////////////////////////////////////////////////////
/// ComponentSignature
///////////////////////////////////////////////////////////////////////////////////////////////////
/// We use a bitset (1s and 0s) to keep track of which components an entity has, and also keeps
/// track of which entities a system is interested in
///////////////////////////////////////////////////////////////////////////////////////////////////
typedef std::bitset<MAX_COMPONENTS> ComponentSignature;

struct BaseComponent
{
    protected:
        static unsigned nextComponentId;
};

// used to assign a unique id to a component type
template <typename ComponentType>
class Component : public BaseComponent
{
        // Returns the unique id of Component<T>
        static int GetComponentId()
        {
            static unsigned componentId = nextComponentId++;

            return componentId;
        }
};

class Entity
{
    public:
        Entity(int entityId);
        Entity(const Entity& entity) = default;  //<-- will use Enity's own '=' operator
        int GetEntityId() const;

        Entity& operator =(const Entity& other) = default; // <-- modern C++ thing!

        bool operator ==(const Entity& other) const;
        bool operator !=(const Entity& other) const;

    private:
        int m_entityId;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
/// System
///////////////////////////////////////////////////////////////////////////////////////////////////
/// The system processes entities that contain specific signatures
///////////////////////////////////////////////////////////////////////////////////////////////////
class System
{
    public:
        System() = default;
        ~System() = default;

        void AddEntityToSystem(Entity entity);
        void RemoveEntityFromSystem(Entity entity);
        const std::vector<Entity>& GetSystemEntities() const;

        const ComponentSignature& GetComponentSignature() const;

        // Define a component type that entities must have to be considered by the system
        template <typename ComponentType>
        void RequireComponent()
        {
            const auto componentId = Component<ComponentType>::GetComponentId();
            m_componentSignature.set(componentId);
        }
    private:
        ComponentSignature m_componentSignature;
        std::vector<Entity> m_entities;
};

class Registry
{

};

#endif // !ECS_H