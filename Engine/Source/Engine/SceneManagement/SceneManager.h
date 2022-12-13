#pragma once
#include <sstream>

#include "Scene.h"

namespace Engine
{
	// Work-around for now.
	class SceneManager final
	{
	public:
		static SceneManager& GetInstance();
		~SceneManager();

		// Create the scene and set it as current scene
		static void CreateNewScene(StringView name = "Scene");

		// Save scene as JSON file
		static void SaveScene(StringView filepath);
		
		// Load scene from JSON file
		static void LoadSceneFromFile(StringView filepath);

		// Delete the current scene
		static void DestroyCurrentScene();

		// Get current scene
		static Scene* GetCurrentScene();

		static void UpdateScene();
		
	private:
		SceneManager();

		static SceneManager* s_Instance;

		bool m_IsSceneDeleted = true;

		bool m_IsLoadingFromFile = false;

		std::stringstream m_LoadedFileStringStream;

		Scene* m_CurrentScene = nullptr; 
	};
}
