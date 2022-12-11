#pragma once
#include "Engine/Math/Math.h"
#include "Engine/ECS/Core/AComponent.h"
#include "Engine/Graphics/Buffer/Framebuffer.h"

namespace Engine
{
	// Issue, what if the transform is deleted before camera component?
	class TransformComponent;
	class CameraComponent final : public AComponent
	{
	public:
		explicit CameraComponent(const EntityID& ownerID,
		                         SharedPtr<TransformComponent> transform,
		                         uint32_t width,
		                         uint32_t height);

		~CameraComponent() override;

		MAKE_COMPONENT(Camera)

		enum class Projection
		{
			Perspective,
			Orthographic
		};

		Color ClearColor;

		float FoV;

		float OrthographicSize;

		float NearClipPlane;

		float FarClipPlane;

		Vector3Float Front;

		Vector3Float Up;

		Projection Projection;

		TransformComponent& GetTransform() const;

		void UpdateViewMatrix(const Vector3Float& target,
							  const Vector3Float& up);

		void SetSize(uint32_t width, uint32_t height);

		void SetPosition(const Vector3Float& position) const;

		void SetRotation(const Vector3Float& rotation) const;

		const Vector3Float& GetPosition() const;

		const Vector3Float& GetRotation() const;
		
		Matrix4 GetViewProjMatrix();

		// void Update();

		[[nodiscard]]
		Framebuffer& GetRenderTarget() const;

		std::vector<DirectX::XMFLOAT4> GetFrustumPlanes();

	private:
		void InitRenderTarget(uint32_t width, uint32_t height);

		SharedPtr<TransformComponent> m_Transform{};

		Matrix4 m_ViewMatrix;

		Matrix4 m_ProjMatrix;

		UniquePtr<Framebuffer> m_RenderTarget{};
	};
}
