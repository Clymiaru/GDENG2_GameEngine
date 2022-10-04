#pragma once
#include <d3d11.h>

#include "Engine/Graphics/ConstantBuffer.h"
#include "Engine/Graphics/PixelShader.h"
#include "Engine/Graphics/VertexShader.h"
#include "Engine/Utils/Color32.h"
#include "Engine/Utils/Math.h"
#include "Engine/Utils/Pointers.h"

namespace Engine
{
	struct IndexLayoutInfo
	{
		D3D11_INPUT_ELEMENT_DESC* Data;

		size_t Size;
	};

	class Quad final
	{
	public:
		Quad(const Vector2Float& position,
		     const Vector2Float& size,
		     const Color32& color);

		~Quad();

		auto GetListOfVertices() -> void*;

		auto GetListOfVerticesSize() -> size_t;

		auto GetVertexSize() -> size_t;

		auto GetIndexLayoutAndSize() -> IndexLayoutInfo&;

		auto SetIndexLayoutAndSize(IndexLayoutInfo indexLayoutInfo) -> void;

		auto SetVertexAndPixelShader(SharedPtr<VertexShader> vertexShader,
		                             SharedPtr<PixelShader> pixelShader) -> void;

		auto GetTransform() -> DirectX::XMMATRIX&;

		auto GetConstantBuffer() -> ConstantBuffer*;

		auto SetConstantBuffer(ConstantBuffer* constantBuffer) -> void;

	private:
		Vector2Float m_Position;

		Vector2Float m_Size;

		Color32 m_Color;

		void* m_Vertices;

		size_t m_VerticesSize;

		UniquePtr<IndexLayoutInfo> m_IndexLayout;

		SharedPtr<VertexShader> m_VertexShader;

		SharedPtr<PixelShader> m_PixelShader;

		ConstantBuffer* m_ConstantBuffer;

		DirectX::XMMATRIX m_ModelMat;
	};
}
