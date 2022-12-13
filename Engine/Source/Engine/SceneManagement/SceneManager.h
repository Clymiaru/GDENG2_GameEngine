#pragma once
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

		// Load scene from JSON file
		static void LoadSceneFromFile(StringView filename);

		// Delete the current scene
		static void DestroyCurrentScene();

		// Get current scene
		static Scene* GetCurrentScene();
		
	private:
		SceneManager();

		static SceneManager* s_Instance;

		Scene* m_CurrentScene; 
	};
}
