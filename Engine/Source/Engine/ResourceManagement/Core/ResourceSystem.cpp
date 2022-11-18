#include "pch.h"
#include "ResourceSystem.h"

namespace Engine
{
	ResourceSystem* ResourceSystem::s_Instance = nullptr;
	
	ResourceSystem::ResourceSystem() :
		m_ShaderLibrary{ShaderLibrary()}
	{
		Debug::Assert(s_Instance == nullptr,
					  "ResourceSystem has already been instantiated and initialized!");

		s_Instance = this;
	}
	
	ResourceSystem::~ResourceSystem()
	{
		// Free all resources
	}
}
