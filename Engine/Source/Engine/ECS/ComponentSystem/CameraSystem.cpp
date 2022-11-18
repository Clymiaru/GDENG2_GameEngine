#include "pch.h"
#include "CameraSystem.h"

#include "Engine/ECS/Component/CameraComponent.h"
#include "Engine/ECS/Component/TransformComponent.h"
#include "Engine/ECS/Core/EntityManager.h"

namespace Engine
{
	void CameraSystem::CameraUpdate() const
	{
		const List<CameraComponent*> cameraList = EntityManager::GetAllComponentsOfType<CameraComponent>();
		const List<TransformComponent*> transformList = EntityManager::GetAllComponentsOfType<TransformComponent>();

		for (size_t i = 0; i < cameraList.size(); i++)
		{
			for (size_t j = 0; j < transformList.size(); j++)
			{
				if (cameraList[i]->GetOwnerID() == transformList[j]->GetOwnerID())
				{
					cameraList[i]->Update(transformList[j]);
				}
			}
		}
		//Debug::Log("List: {0}", cameraList.size());
	}

}
