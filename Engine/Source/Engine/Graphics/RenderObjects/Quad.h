﻿#pragma once
#include "Engine/Core/Core.h"
#include "Engine/Core/Math.h"

#include "Engine/Graphics/RenderObjects/Primitive.h"

namespace Engine
{
	struct Constant;

	class Quad final : public Primitive
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
		void InitializeBuffers() override;

		void UpdateConstantBuffer(float time);

		std::pair<Vertex*, size_t> CreateVertices() override;

		std::pair<D3D11_INPUT_ELEMENT_DESC*, size_t> CreateVertexLayout() override;

		std::pair<Uint*, size_t> CreateIndices() override;
		
		Vector3 m_Position;

		Vector2 m_Scale;

		Color m_Color;

		DirectX::XMMATRIX m_TransformMatrix;

		Constant* m_Constant;
	};
}
