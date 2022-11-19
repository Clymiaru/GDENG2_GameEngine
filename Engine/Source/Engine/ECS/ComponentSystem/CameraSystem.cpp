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

	CameraComponent* CameraSystem::GetGameCamera() const
	{
		//return (int)m_GameCameraList.size() > 0 ? nullptr : m_GameCameraList[0];
		return nullptr;
	}
	
	CameraComponent* CameraSystem::GetEditorCamera(int index) const
	{
		// return index >= (int)m_EditorCameraList.size() ? nullptr : m_EditorCameraList[index];
		return nullptr;
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
