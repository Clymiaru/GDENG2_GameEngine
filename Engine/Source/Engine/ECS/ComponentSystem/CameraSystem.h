#pragma once
#include "Engine/ECS/Component/CameraComponent.h"
#include "Engine/ECS/Component/EditorCameraComponent.h"

namespace Engine
{
	// Having each system listens to events would
	// render ComponentRegistry's get all components useless
	// (maybe not as it can still be used for deregistering)
	class CameraSystem final
	{
	public:
		CameraSystem();
		~CameraSystem();
		
		SharedPtr<CameraComponent> GetGameCamera() const;
		
		SharedPtr<EditorCameraComponent> GetEditorCamera(int index) const;

		size_t GetEditorCameraCount() const;
		
		void CameraUpdate() const;

		void EditorCameraUpdate() const;
		
	private:
		
	};
}
