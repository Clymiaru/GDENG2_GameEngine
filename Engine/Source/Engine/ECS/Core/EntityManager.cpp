#include "pch.h"
#include "EntityManager.h"

namespace Engine
{
	EntityManager* EntityManager::s_Instance = nullptr;

	EntityManager::EntityManager()
	{
		Debug::Assert(s_Instance == nullptr,
		              "EntityManager has already been instantiated and initialized!");

		s_Instance = this;
	}

	EntityManager::~EntityManager()
	{
		delete s_Instance; // Wouldn't this loop?
	}
	
	EntityRegistry& EntityManager::GetEntityRegistry()
	{
		return m_EntityRegistry;
	}
}
