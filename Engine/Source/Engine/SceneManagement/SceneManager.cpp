#include "pch.h"
#include "SceneManager.h"

namespace Engine
{
	SceneManager* SceneManager::s_Instance = nullptr;
	
	SceneManager::SceneManager() = default;

	SceneManager& SceneManager::GetInstance()
	{
		if (s_Instance == nullptr)
		{
			s_Instance = new SceneManager();
		}
		return *s_Instance;
	}
	SceneManager::~SceneManager()
	{
		s_Instance = nullptr;
	}
	
	void SceneManager::CreateNewScene(StringView name)
	{
		GetInstance().m_CurrentScene = new Scene(1, name);
	}
	
	void SceneManager::LoadSceneFromFile(StringView filename)
	{
		
	}
	
	void SceneManager::DestroyCurrentScene()
	{
		delete GetInstance().m_CurrentScene;
	}
	
	Scene* SceneManager::GetCurrentScene()
	{
		return GetInstance().m_CurrentScene;
	}
}

