#pragma once
#include "Engine/Core/Core.h"
#include "Engine/Core/Debug.h"
#include "Engine/Core/Math.h"

#include "Engine/Graphics/ConstantBuffer.h"
#include "Engine/Graphics/RenderObjects/RenderObject.h"

namespace Engine
{
	struct Constant;

	class Quad final : public RenderObject
	{
	public:
		Quad(const Vector3& position,
		     const Vector2& size,
		     const Color& color,
		     const std::wstring& shaderName);

		~Quad() override;

		void Update(float deltaTime);

		void Render() const;

	private:
		Vector3 m_Position;

		Vector2 m_Size;

		Color m_Color;

		UniquePtr<ConstantBuffer> m_ConstantBuffer{};

		DirectX::XMMATRIX m_TransformMatrix;

		Constant* m_Constant;

		void InitializeBuffers() override;

		void UpdateConstantBuffer(float time);
	};
}
