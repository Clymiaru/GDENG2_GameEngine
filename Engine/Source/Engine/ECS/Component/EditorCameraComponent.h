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

		float FoV;

		Vector3Float Front;

		Vector3Float Up;

		TransformComponent& GetTransform() const;

		void UpdateViewMatrix(const Vector3Float& target,
		                      const Vector3Float& up);

		void SetSize(uint64_t width, uint64_t height);

		void SetPosition(const Vector3Float& position) const;

		void SetRotation(const Vector3Float& rotation) const;

		void SetFocus(bool flag);

		const Vector3Float& GetPosition() const;

		const Vector3Float& GetRotation() const;

		Matrix4 GetViewProjMatrix();

		void Update();

		[[nodiscard]]
		Framebuffer& GetRenderTarget() const;

	private:
		void InitRenderTarget(uint64_t width, uint64_t height);

		SharedPtr<TransformComponent> m_Transform;

		Matrix4 m_ViewMatrix;

		Matrix4 m_ProjMatrix;

		UniquePtr<Framebuffer> m_RenderTarget;

		bool m_IsFocused = false;
	};
}
