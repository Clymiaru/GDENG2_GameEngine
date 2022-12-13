#pragma once

#include "Engine/ECS/Core/Entity.h"

#include "Utils/UIIDGenerator.h"

namespace Engine
{
	
	class Scene final
	{
	public:
		
		// void Load(StringView filepath); // File format: .level
		// Load .level file
		// Parse level file
		// Close .level file
		// Instantiate entities based on components

		Scene(UIID id, StringView sceneName);
		~Scene();

		const String& GetName() const; 

		bool IsEntityInScene(UIID entityID) const;
		
	private:

		void AddEntity(const Entity* entity);

		void RemoveEntity(const Entity* entity);
		
		UIID m_ID;
		String m_Name;
		
		List<UIID> m_InSceneEntityIDList;
	};
}
