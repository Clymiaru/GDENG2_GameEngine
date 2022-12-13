#include "pch.h"
#include "Scene.h"

#include "SceneManager.h"

#include "Engine/ECS/Core/EntityManager.h"

namespace Engine
{
	Scene::Scene(const UIID id, const StringView sceneName) :
		m_ID{id},
		m_Name{sceneName.data()}
	{
		auto createEntityCallback = [this](const Entity* entity) { AddEntity(entity); };
		EntityManager::ListenToEntityCreateEvent(createEntityCallback);

		auto destroyEntityCallback = [this](const Entity* entity) { RemoveEntity(entity); };
		EntityManager::ListenToEntityDestroyEvent(destroyEntityCallback);
	}
	
	Scene::~Scene()
	{
		for (size_t i = 0; i < m_InSceneEntityIDList.size(); ++i)
		{
			const auto entity = EntityManager::GetEntity(m_InSceneEntityIDList[i]);
			m_InSceneEntityIDList.erase(m_InSceneEntityIDList.begin());
			
			EntityManager::Destroy(entity);
		}
	}
	const String& Scene::GetName() const
	{
		return m_Name;
	}

	bool Scene::IsEntityInScene(const UIID entityID) const
	{
		for (size_t i = 0; i < m_InSceneEntityIDList.size(); ++i)
		{
			if (entityID == m_InSceneEntityIDList[i])
			{
				return true;
			}
		}
		return false;
	}

	void Scene::AddEntity(const Entity* entity)
	{
		m_InSceneEntityIDList.push_back(entity->GetID());
	}

	void Scene::RemoveEntity(const Entity* entity)
	{
		for (size_t i = 0; i < m_InSceneEntityIDList.size(); ++i)
		{
			if (entity->GetID() == m_InSceneEntityIDList[i])
			{
				m_InSceneEntityIDList.erase(m_InSceneEntityIDList.begin() + i);
			}
		}
	}
}
