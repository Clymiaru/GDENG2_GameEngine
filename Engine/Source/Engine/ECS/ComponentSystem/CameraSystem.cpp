#include "pch.h"
#include "CameraSystem.h"

#include "Engine/ECS/Component/CameraComponent.h"
#include "Engine/ECS/Component/EditorCameraComponent.h"
#include "Engine/ECS/Component/TransformComponent.h"
#include "Engine/ECS/Core/EntityManager.h"

namespace Engine
{
	CameraSystem::CameraSystem()
	{
	}
	
	CameraSystem::~CameraSystem() {}

	SharedPtr<CameraComponent> CameraSystem::GetGameCamera() const
	{
		const auto cameraList = EntityManager::GetAllComponentsOfType<CameraComponent>();

		if (0 >= cameraList.size())
		{
			return nullptr;
		}
		
		return cameraList[0];
	}
	
	SharedPtr<EditorCameraComponent> CameraSystem::GetEditorCamera(int index) const
	{
		const auto cameraList = EntityManager::GetAllComponentsOfType<EditorCameraComponent>();

		if (index >= cameraList.size())
		{
			return nullptr;
		}
		
		return cameraList[index];
	}
	
	size_t CameraSystem::GetEditorCameraCount() const
	{
		const auto cameraList = EntityManager::GetAllComponentsOfType<EditorCameraComponent>();
		return cameraList.size();
	}

	void CameraSystem::CameraUpdate() const
	{
		const auto cameraList = EntityManager::GetAllComponentsOfType<CameraComponent>();

		for (size_t i = 0; i < cameraList.size(); i++)
		{
			cameraList[i]->Update();
		}
	}
	
	void CameraSystem::EditorCameraUpdate() const
	{
		const auto cameraList = EntityManager::GetAllComponentsOfType<EditorCameraComponent>();

		for (size_t i = 0; i < cameraList.size(); i++)
		{
			cameraList[i]->Update();
		}
	}
}
