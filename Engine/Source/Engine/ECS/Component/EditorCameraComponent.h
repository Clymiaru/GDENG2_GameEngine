#pragma once
#include "TransformComponent.h"

#include "Engine/ECS/Core/AComponent.h"
#include "Engine/Graphics/Buffer/Framebuffer.h"

namespace Engine
{
	// This component is simply for editor
	// Difference is that this is controllable for the editor
	class EditorCameraComponent final : public AComponent
	{
	public:
		explicit EditorCameraComponent(const EntityID& ownerID,
		                               SharedPtr<TransformComponent> transform,
		                               uint64_t width,
		                               uint64_t height);

		~EditorCameraComponent() override;

		MAKE_COMPONENT(EditorCamera)

		void SetSize(uint64_t width, uint64_t height);

		Matrix4 GetViewProjMatrix();

		void Update();

		[[nodiscard]]
		Framebuffer& GetRenderTarget() const;

	private:
		float FoV = 45.0f;

		void InitRenderTarget(uint64_t width, uint64_t height);

		void UpdateViewMatrix();

		void UpdateCameraVectors();

		SharedPtr<TransformComponent> m_Transform;

		Matrix4 m_ViewMatrix;

		Matrix4 m_ProjMatrix;

		Vector3Float m_Front;

		Vector3Float m_Up;

		Vector3Float m_Right;

		Vector3Float m_WorldUp;

		UniquePtr<Framebuffer> m_RenderTarget;
	};
}
