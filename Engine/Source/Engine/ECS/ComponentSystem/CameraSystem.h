#pragma once
#include "Engine/ECS/Component/CameraComponent.h"

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
		
		CameraComponent* GetGameCamera() const;
		
		CameraComponent* GetEditorCamera(int index) const;
		
		void CameraUpdate() const;

		void EditorCameraUpdate() const;
		
	private:
		
	};
}
