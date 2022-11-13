#include "pch.h"
#include "Scene.h"

namespace Engine
{
	// TODO: Make a scene file
	Scene::Scene(const SceneID id, const StringView sceneName) :
		m_ID{id},
		m_Name{sceneName},
		m_EntityOnSceneList{}
	{
	}
	
	Scene::~Scene()
	{
		// Process deletion of all entities in the EntityOnSceneList;
	}
	
	void Scene::OnBegin()
	{
		
	}
	
	void Scene::OnEnd()
	{
	}
	
	List<Entity&>& Scene::GetEntityOnSceneList()
	{
		return m_EntityOnSceneList;
	}

	void Scene::AddEntity(Entity& entity)
	{
		// TODO: Communicate with the EntityManager
		m_EntityOnSceneList.emplace_back(entity);
	}
}
