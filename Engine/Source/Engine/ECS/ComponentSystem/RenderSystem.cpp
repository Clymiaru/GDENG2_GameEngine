#include "pch.h"
#include "RenderSystem.h"

#include "Engine/ECS/Component/RenderComponent.h"
#include "Engine/ECS/Core/EntityManager.h"

struct RenderObjectData;
namespace Engine
{
	void RenderSystem::Render(CameraComponent& camera) const
	{
		const auto renderList = EntityManager::GetAllComponentsOfType<RenderComponent>();
		
		for (auto render : renderList)
		{
			render->Draw(nullptr, camera);
		}
	}
}
