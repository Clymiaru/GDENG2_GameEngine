#include "pch.h"
#include "CameraSystem.h"

#include "Engine/ECS/Component/CameraComponent.h"
#include "Engine/ECS/Component/EditorCameraComponent.h"
#include "Engine/ECS/Component/TransformComponent.h"
#include "Engine/ECS/Core/EntityManager.h"

namespace Engine
{
	CameraSystem::CameraSystem() { }

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

	void CameraSystem::GameCameraUpdate() const
	{
		const auto cameraList =
				EntityManager::GetAllComponentsOfType<CameraComponent>();

		for (size_t i = 0; i < cameraList.size(); i++)
		{
			const float yaw   = DegreesToRadians(cameraList[i]->GetTransform().Rotation.y);
			const float pitch = DegreesToRadians(cameraList[i]->GetTransform().Rotation.x);
			const float roll  = DegreesToRadians(cameraList[i]->GetTransform().Rotation.z);

			const Matrix4 cameraRotationMatrix = Matrix4::CreateFromYawPitchRoll(yaw, pitch, roll);

			Vector3Float target = Vector3Float::Transform(cameraList[i]->Front, cameraRotationMatrix);

			target += cameraList[i]->GetTransform().Position;

			Vector3Float up = Vector3Float::Transform(cameraList[i]->Up, cameraRotationMatrix);

			cameraList[i]->UpdateViewMatrix(target, up);
		}
	}

	void CameraSystem::EditorCameraUpdate() const
	{
		const auto cameraList =
			EntityManager::GetAllComponentsOfType<EditorCameraComponent>();

		for (size_t i = 0; i < cameraList.size(); i++)
		{
			const float yaw   = DegreesToRadians(cameraList[i]->GetTransform().Rotation.y);
			const float pitch = DegreesToRadians(cameraList[i]->GetTransform().Rotation.x);
			const float roll  = DegreesToRadians(cameraList[i]->GetTransform().Rotation.z);

			const Matrix4 cameraRotationMatrix = Matrix4::CreateFromYawPitchRoll(yaw, pitch, roll);

			Vector3Float target = Vector3Float::Transform(cameraList[i]->Front, cameraRotationMatrix);

			target += cameraList[i]->GetTransform().Position;

			Vector3Float up = Vector3Float::Transform(cameraList[i]->Up, cameraRotationMatrix);

			cameraList[i]->UpdateViewMatrix(target, up);
		}
	}
}
