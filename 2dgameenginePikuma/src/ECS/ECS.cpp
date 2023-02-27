#include "ECS.h"

#include "../Logger/Logger.h"

unsigned BaseComponent::nextComponentId = 0U;

Entity::Entity(int entityId)
    :m_entityId(entityId)
{
}

int Entity::GetEntityId() const
{
    return m_entityId;
}


bool Entity::operator ==(const Entity& other) const
{
    return this->GetEntityId() == other.GetEntityId();
}

bool Entity::operator !=(const Entity& other) const
{
    return this->GetEntityId() != other.GetEntityId();
}

void System::AddEntityToSystem(Entity entity)
{
    m_entities.push_back(entity);
}

void System::RemoveEntityFromSystem(Entity entity)
{
    if (m_entities.empty())
    {
        Logger::Error("No entities to remove!");

        return;
    }

    m_entities.erase(
        std::remove_if(
            m_entities.begin(),
            m_entities.end(),
            [&entity](const Entity& other)
            {
                return entity == other;
            }
        )
    );
}

const std::vector<Entity>& System::GetSystemEntities() const
{
    return m_entities;
}

const ComponentSignature& System::GetComponentSignature() const
{
    return m_componentSignature;
}

Entity Registry::CreateEntity()
{
    int newEntityId;
    newEntityId = m_numberOfEntities++;

    Entity newEntity(newEntityId);
    m_entittiesToBeAdded.push_back(newEntity);

    // make sure the m_entityComponentSignatures can accomodate the new entity
    m_entityComponentSignatures.push_back(std::move(ComponentSignature()));

    Logger::Log("Entity created with id: " + std::to_string(newEntityId));

    return newEntity;
}

void Registry::AddEntityToSystems(Entity entity)
{
    const auto entityId = entity.GetEntityId();

    const auto& entityComponentSignature = m_entityComponentSignatures[entityId];

    for (auto& system : m_systems)
    {
        if (entityComponentSignature == system.second->GetComponentSignature())
        {
            system.second->AddEntityToSystem(entity);
        }
    }
}

void Registry::Update()
{
    // add the entities that are waiting to be created to the active systems
    for (Entity entity : m_entittiesToBeAdded)
    {
        AddEntityToSystems(entity);
    }
    m_entittiesToBeAdded.clear();

    // remove the entities that are waiting to be deleted to the active systems
    for (Entity entity : m_entittiesToBeDestroyed)
    {
    }
}