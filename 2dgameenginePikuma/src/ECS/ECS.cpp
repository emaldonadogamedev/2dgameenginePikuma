#include "ECS.h"

#include "../Logger/Logger.h"

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