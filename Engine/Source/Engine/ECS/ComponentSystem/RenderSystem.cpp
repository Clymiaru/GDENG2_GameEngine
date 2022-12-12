#include "pch.h"
#include "RenderSystem.h"

#include "Engine/ECS/Component/RenderComponent.h"
#include "Engine/ECS/Component/CameraRenderComponent.h"
#include "Engine/ECS/Component/Render/StaticMeshComponent.h"
#include "Engine/ECS/Core/EntityManager.h"

struct RenderObjectData;
namespace Engine
{
	void RenderSystem::Render(CameraComponent& camera) const
	{
		const auto renderList = EntityManager::GetAllComponentsOfType<StaticMeshComponent>();
		const auto CameraRenderList = EntityManager::GetAllComponentsOfType<CameraRenderComponent>();
		
		for (auto render : renderList)
		{
			render->Draw(camera);
		}

		for(auto CameraRender: CameraRenderList)
		{
			
			CameraRender->Draw(camera);
		}
	}
	
	void RenderSystem::Render(EditorCameraComponent& camera) const
	{
		const auto renderList = EntityManager::GetAllComponentsOfType<StaticMeshComponent>();
		const auto CameraRenderList = EntityManager::GetAllComponentsOfType<CameraRenderComponent>();
		
		for (auto render : renderList)
		{
			render->Draw(camera);
		}

		for (auto CameraRender : CameraRenderList)
		{

			CameraRender->Draw(camera);
		}
	}
}
