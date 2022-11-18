#include "WorldOutlinerScreen.h"

#include <Engine/Core/Core.h>

#include "../Dependencies/ImGui/imgui.h"

#include <Engine/ECS/Core/Entity.h>
#include <Engine/ECS/Core/EntityManager.h>
#include <Engine/UI/UISystem.h>

namespace Editor
{
	WorldOutlinerScreen::WorldOutlinerScreen(const Engine::ScreenID id)
		: AUIScreen{id, "World Outliner"}
	{
		using namespace Engine;
		EntityManager::ListenToCreateEvent([this](const EntityID entityID, const StringView entityName) -> void
		{
			OnEntityCreate(entityID, entityName);
		});

		EntityManager::ListenToDestroyEvent([this](const EntityID entityID, const StringView entityName) -> void
		{
			OnEntityDestroy(entityID, entityName);
		});

		const List<Entity*>& entityListRef = EntityManager::GetAllEntities();
		for (auto* entity : entityListRef)
		{
			OnEntityCreate(entity->GetID(), entity->GetName());
		}
	}

	WorldOutlinerScreen::~WorldOutlinerScreen()
	{
	}
	
	Engine::EntityID WorldOutlinerScreen::GetSelectedEntityID() const
	{
		return m_SelectedEntity;
	}

	void WorldOutlinerScreen::DrawImpl()
	{
		using namespace Engine;
		UISystem::ShowDemoWindow(true);

		// This window is always open for the whole duration of the program
		ImGui::Begin(GetNameAndIDLabel());

		if (ImGui::TreeNode("Scene"))
		{
			for (size_t i = 0ULL; i < m_EntityEntryList.size(); i++)
			{
				if (ImGui::Selectable(m_EntityEntryList[i].EntityName.c_str(),
					m_SelectedEntity == m_EntityEntryList[i].EntityID))
				{
					m_SelectedEntity = m_EntityEntryList[i].EntityID;
				}
			}
			ImGui::TreePop();
		}

		ImGui::End();
		
	}
	
	void WorldOutlinerScreen::OnEntityCreate(const Engine::EntityID entityID, const Engine::StringView entityName)
	{
		Entry entityEntry;
		entityEntry.EntityID = entityID;
		entityEntry.EntityName = entityName.data();
		entityEntry.IsSelected = false;
		m_EntityEntryList.push_back(entityEntry);
	}
	
	void WorldOutlinerScreen::OnEntityDestroy(Engine::EntityID entityID, Engine::StringView entityName)
	{
		if (m_SelectedEntity == entityID)
		{
			m_SelectedEntity = 0;
		}

		auto foundEntry = std::ranges::remove_if(m_EntityEntryList, [entityID](const Entry& entry) -> bool
		{
			return entry.EntityID == entityID;
		});
		m_EntityEntryList.erase(foundEntry.begin(), foundEntry.end());
		m_EntityEntryList.shrink_to_fit();
	}
}

