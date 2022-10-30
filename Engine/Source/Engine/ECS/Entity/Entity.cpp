#include "pch.h"
#include "Entity.h"

#include "Engine/ECS/Component/RenderComponent.h"
#include "Engine/ECS/Component/TransformComponent.h"

Engine::Entity::Entity(const String& name) :
	m_Name{name},
	m_Transform{new TransformComponent(this)},
	m_RenderComponent{new RenderComponent(this)}
{
	m_RenderComponent->Initialize();
}

Engine::Entity::~Entity()
{
	m_RenderComponent->Terminate();
	delete m_Transform;
}

const Engine::String& Engine::Entity::Name()
{
	return m_Name;
}

Engine::TransformComponent& Engine::Entity::Transform() const
{
	return *m_Transform;
}

Engine::RenderComponent& Engine::Entity::Render() const
{
	return *m_RenderComponent;
}
