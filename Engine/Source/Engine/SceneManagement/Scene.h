#pragma once

#include "Engine/ECS/Core/Entity.h"

namespace Engine
{
	// The scene's job is to collate information of the entities
	// that will appear at a given time for as long as this scene is active

	// The scene holds their own entity reference for the UI to make use of
	using SceneID = uint64_t;
	class Scene
	{
	public:
		Scene(SceneID id, StringView sceneName);
		
		virtual ~Scene();
		
		// Initialize necessary data when scene begins
		virtual void OnBegin();

		// Deinitialize necessary data when scene ends
		virtual void OnEnd();

		List<Entity&>& GetEntityOnSceneList();
		
		void AddEntity(Entity& entity);
		// void RemoveEntity();
	private:
		SceneID m_ID;
		String m_Name;
		
		List<Entity&> m_EntityOnSceneList;
	};
}
