#ifndef ECS_H
#define ECS_H

#include <bitset>

#include <typeindex>

#include <vector>
#include <unordered_map>

typedef unsigned int EntityId;

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

///////////////////////////////////////////////////////////////////////////////////////////////////
/// Registry
///////////////////////////////////////////////////////////////////////////////////////////////////
/// The registry manages the creation and destruction of entities, as well as adding systems and
/// adding components to entities
///////////////////////////////////////////////////////////////////////////////////////////////////
class Registry
{
    private:
        class IMemoryPool
        {
            public:
                virtual ~IMemoryPool() = 0;
        };

        // Pool: a data structure of objects of type
        template <typename ComponentType>
        class BaseComponentMemoryPool : public IMemoryPool
        {
            public:
                virtual bool IsEmpty() const = 0;
                virtual size_t GetSize() const = 0;
                virtual void Resize(size_t newSize) = 0;
                virtual void Clear() = 0;
                virtual void Set(EntityId entityId, ComponentType entity) = 0;
                virtual ComponentType& Get(EntityId entityId) = 0;
                virtual ComponentType& operator[](EntityId entityId) = 0;
        };

        template<typename ComponentType>
        class UmapComponentMemoryPool : public BaseComponentMemoryPool<ComponentType>
        {
            public:
                bool IsEmpty() const
                {
                    return m_data.empty();
                }
                size_t GetSize() const
                {
                    return m_data.size();
                }
                void Clear()
                {
                    m_data.clear();
                }
                void Add(EntityId entityId, ComponentType component)
                {
                    m_data.insert(entityId, component);
                }
                void Set(EntityId entityId, ComponentType entity)
                {
                    m_data[entityId] = entity;
                }
                ComponentType& Get(EntityId entityId)
                {
                    return m_data[entityId];
                }
                ComponentType& operator[](EntityId entityId)
                {
                    return m_data[entityId];
                }
            private:
                std::unordered_map<EntityId, ComponentType> m_data;
        };

        template<typename ComponentType>
        class ArrayComponentMemoryPool : public BaseComponentMemoryPool<ComponentType>
        {
            public:
                ArrayComponentMemoryPool(size_t size = 100)
                {
                    m_data.resize(size);
                }

                ~ArrayComponentMemoryPool() = default;

                bool IsEmpty() const override
                {
                    return m_data.empty();
                }

                size_t GetSize() const
                {
                    return m_data.size();
                }

                void Resize(size_t newSize)
                {
                    m_data.resize(newSize);
                }

                void Clear()
                {
                    m_data.clear();
                }

                void Add(ComponentType component)
                {
                    m_data.push_back(component);
                }

                void Set(EntityId entityId, ComponentType entity)
                {
                    m_data[entityId] = entity;
                }
                ComponentType& Get(EntityId entityId)
                {
                    return m_data[entityId];
                }
                ComponentType& operator[](EntityId entityId)
                {
                    return m_data[entityId];
                }

            private:
                std::vector<ComponentType> m_data;
        };

    public:
        Registry() = default;
        ~Registry() = default;

        Entity& CreateEntity();


    private:

        int m_numberOfEntities;

        // vector of pools. Each pool contains all of the data for a certain component type
        // vector index = component type id
        // pool index = entity id
        std::vector<IMemoryPool> m_componentPools;

        // Vector of component signatures
        // The signature lets us know which componnents are turned "on" for an entity
        // vector index = the entity Id
        std::vector<ComponentSignature> m_entityComponentSignatures;

        // umap of active systems [index = system type id]
        std::unordered_map<std::type_index, System*> m_systems;
};

#endif // !ECS_H