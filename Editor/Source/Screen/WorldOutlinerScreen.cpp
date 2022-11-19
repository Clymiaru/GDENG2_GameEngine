#include "WorldOutlinerScreen.h"

#include <Engine/Core/Core.h>
#include <Engine/Core/Debug.h>

#include "../Dependencies/ImGui/imgui.h"

#include <Engine/ECS/Core/Entity.h>
#include <Engine/ECS/Core/EntityManager.h>
#include <Engine/UI/UISystem.h>

namespace Editor
{
	WorldOutlinerScreen::WorldOutlinerScreen(const Engine::ScreenID id) :
		AUIScreen{id, "World Outliner"}
	{
		using namespace Engine;

        auto createEntityCallback = [this](const Entity* entity) { AddEntityEntry(entity); };
		EntityManager::ListenToEntityCreateEvent(createEntityCallback);

        auto destroyEntityCallback = [this](const Entity* entity) { RemoveEntityEntry(entity); };
		EntityManager::ListenToEntityDestroyEvent(destroyEntityCallback);

		// const List<Entity*>& entityListRef = EntityManager::GetAllEntities();
		// for (auto* entity : entityListRef)
		// {
		// 	AddEntityEntry(entity->GetID(), entity->GetName());
		// }
	}

	WorldOutlinerScreen::~WorldOutlinerScreen() { }

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

	void WorldOutlinerScreen::AddEntityEntry(const Engine::Entity* entity)
	{
		if (entity == nullptr)
		{
			Engine::Debug::Log("Attempting to add a null entity (WorldOutlinerScreen)!");
			return;
		}

		Entry entityEntry;
		entityEntry.EntityID   = entity->GetID();
		entityEntry.EntityName = entity->GetName();
		entityEntry.IsSelected = false;
		m_EntityEntryList.push_back(entityEntry);
	}

	void WorldOutlinerScreen::RemoveEntityEntry(const Engine::Entity* entity)
	{
		if (entity == nullptr)
		{
			Engine::Debug::Log("Attempting to remove a null entity (WorldOutlinerScreen)!");
			return;
		}

		Engine::EntityID entityID = entity->GetID();

		if (m_SelectedEntity == entityID)
		{
			m_SelectedEntity = 0;
		}

		auto foundEntry = std::ranges::remove_if(m_EntityEntryList,
		                                         [entityID](const Entry& entry) -> bool
		                                         {
			                                         return entry.EntityID == entityID;
		                                         });
		m_EntityEntryList.erase(foundEntry.begin(), foundEntry.end());
		m_EntityEntryList.shrink_to_fit();
	}
}
