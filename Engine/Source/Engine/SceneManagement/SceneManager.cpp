#include "pch.h"
#include "SceneManager.h"

#include "../../../Dependencies/rapidjson/istreamwrapper.h"
#include "../../../Dependencies/rapidjson/ostreamwrapper.h"
#include "../../../Dependencies/rapidjson/prettywriter.h"
#include "../../../Dependencies/rapidjson/writer.h"
#include <fstream>

#include "../../../Dependencies/rapidjson/document.h"

#include "Engine/ECS/Component/TransformComponent.h"
#include "Engine/ECS/Component/Render/StaticMeshComponent.h"
#include "Engine/ECS/Core/EntityManager.h"

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
		GetInstance().m_IsSceneDeleted = false;
	}

	void SceneManager::SaveScene(StringView filepath)
	{
		rapidjson::StringBuffer stringBuffer;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(stringBuffer);

		writer.StartObject();

		writer.Key("SceneInfo");
		writer.StartObject();
		{
			writer.Key("SceneName");
			writer.String(s_Instance->GetCurrentScene()->GetName().c_str());
		}
		writer.EndObject();

		writer.Key("Entities");
		writer.StartArray();
		
		//For each game object
		// For each component
		const List<UIID> entityUIIDList = s_Instance->GetCurrentScene()->GetSceneEntityIDList();

		for (size_t i = 0; i < entityUIIDList.size(); ++i)
		{
			auto entity = EntityManager::GetEntity(entityUIIDList[i]);

			// Save entity
			writer.StartObject();
			{
				writer.Key("Id");
				writer.String(std::to_string(entity->GetID()).c_str());

				writer.Key("Name");
				writer.String(entity->GetName().c_str());

				writer.Key("Components");
				writer.StartArray();

				auto componentList = EntityManager::GetAllComponentsOfEntity(entityUIIDList[i]);

				for (size_t j = 0; j < componentList.size(); ++j)
				{
					// Save component
					auto& component = componentList[j];

					writer.StartObject();
					{
						writer.Key("Name");
						writer.String(component->GetName().c_str());

						if (component->GetName() == "Transform")
						{
							const auto transform = std::dynamic_pointer_cast<TransformComponent>(component);

							writer.Key("Position");
							writer.StartObject();
							{
								writer.Key("X");
								writer.String(std::to_string(transform->Position.x).c_str());

								writer.Key("Y");
								writer.String(std::to_string(transform->Position.y).c_str());

								writer.Key("Z");
								writer.String(std::to_string(transform->Position.z).c_str());
							}
							writer.EndObject();

							writer.Key("Rotation");
							writer.StartObject();
							{
								writer.Key("X");
								writer.String(std::to_string(transform->Rotation.x).c_str());

								writer.Key("Y");
								writer.String(std::to_string(transform->Rotation.y).c_str());

								writer.Key("Z");
								writer.String(std::to_string(transform->Rotation.z).c_str());
							}
							writer.EndObject();

							writer.Key("Scale");
							writer.StartObject();
							{
								writer.Key("X");
								writer.String(std::to_string(transform->Scale.x).c_str());

								writer.Key("Y");
								writer.String(std::to_string(transform->Scale.y).c_str());

								writer.Key("Z");
								writer.String(std::to_string(transform->Scale.z).c_str());
							}
							writer.EndObject();
						}

						if (component->GetName() == "StaticMesh")
						{
							const auto staticMesh = std::dynamic_pointer_cast<StaticMeshComponent>(component);

							writer.Key("AlbedoColor");
							writer.StartObject();
							{
								writer.Key("R");
								writer.String(std::to_string(staticMesh->AlbedoColor.Red()).c_str());

								writer.Key("G");
								writer.String(std::to_string(staticMesh->AlbedoColor.Green()).c_str());

								writer.Key("B");
								writer.String(std::to_string(staticMesh->AlbedoColor.Blue()).c_str());

								writer.Key("A");
								writer.String(std::to_string(staticMesh->AlbedoColor.Alpha()).c_str());
							}
							writer.EndObject();

							writer.Key("PrimitiveType");
							switch (staticMesh->GetRenderData().PrimitiveType)
							{
								case PrimitiveType::Cube:
									writer.String("Cube");
								break;
								case PrimitiveType::Plane:
									writer.String("Plane");
								break;
								case PrimitiveType::Sphere:
									writer.String("Sphere");
								break;
								default:
									writer.String("NotSupported");
							}
						}

					}
					writer.EndObject();
				}
				writer.EndArray();
			}
			writer.EndObject();

		}
		writer.EndArray();
		writer.EndObject();

		std::ofstream fileStream;
		fileStream.open(filepath.data());

		fileStream << stringBuffer.GetString();

		fileStream.close();
	}

	void SceneManager::LoadSceneFromFile(const StringView filepath)
	{
		std::ifstream fileStream(filepath.data());

		if (!fileStream)
		{
			fileStream.close();
			Debug::Log("Failed to load scene {0).", filepath.data());
			return;
		}

		s_Instance->m_LoadedFileStringStream << fileStream.rdbuf();
		fileStream.close();

		s_Instance->m_IsLoadingFromFile = true;
		DestroyCurrentScene();
	}

	void SceneManager::DestroyCurrentScene()
	{
		s_Instance->m_IsSceneDeleted = true;
	}

	Scene* SceneManager::GetCurrentScene()
	{
		return GetInstance().m_CurrentScene;
	}
	
	void SceneManager::UpdateScene()
	{
		if (s_Instance->m_CurrentScene == nullptr)
		{
			return;
		}
		
		if (!s_Instance->m_IsSceneDeleted)
		{
			return;
		}

		delete GetInstance().m_CurrentScene;
		GetInstance().m_CurrentScene = nullptr;
		
		s_Instance->m_IsSceneDeleted = false;

		if (!s_Instance->m_IsLoadingFromFile)
		{
			return;
		}

		rapidjson::Document document;
		document.Parse(s_Instance->m_LoadedFileStringStream.str().c_str());

		Debug::Log("{0} json", document["SceneInfo"]["SceneName"].GetString());
		// std::string loadedSceneName = doc["meta"]["sceneName"].GetString();
		// CreateNewScene(loadedSceneName);
		
		

		// s_Instance->m_LoadedSceneDocument.Parse(fileStringStream.str().c_str());

		// Process Loading


		s_Instance->m_LoadedFileStringStream.clear();
		s_Instance->m_IsLoadingFromFile = false;
	}
}
