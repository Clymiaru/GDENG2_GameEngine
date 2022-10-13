#pragma once

#include "Engine/Graphics/ConstantBuffer.h"
#include "Engine/Graphics/RenderObjects/RenderObject.h"
#include "Engine/Utils/Color32.h"
#include "Engine/Utils/Math.h"
#include "Engine/Utils/Pointers.h"

namespace Engine
{
	struct Constant;

	class Quad final : public RenderObject
	{
	public:
		Quad(const Vector3Float& position,
		     const Vector2Float& size,
		     const Color32& color,
		     const std::wstring& shaderName);

		~Quad() override;

		void Update(float deltaTime);

		void Render() const;

	private:
		Vector3Float m_Position;

		Vector2Float m_Size;

		Color32 m_Color;

		UniquePtr<ConstantBuffer> m_ConstantBuffer{};

		DirectX::XMMATRIX m_TransformMatrix;

		Constant* m_Constant;

		void InitializeBuffers() override;

		void UpdateConstantBuffer(float time);
	};
}
