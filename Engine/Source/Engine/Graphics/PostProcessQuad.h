#pragma once
#include "RenderData.h"

#include "Engine/Core/Core.h"

namespace Engine
{
	class ConstantBuffer;

	class IndexBuffer;

	class VertexBuffer;

	class PixelShader;

	class VertexShader;

	class PostProcessQuad
	{
	public:
		PostProcessQuad();

		~PostProcessQuad();

		void UpdateFrameRef(ID3D11ShaderResourceView* frame);

		void Draw() const;

	private:
		VertexData* m_VertexData;

		VertexLayoutData* m_VertexLayoutData;

		IndexData* m_IndexData;

		SharedPtr<VertexShader> m_VertexShader;

		SharedPtr<PixelShader> m_PixelShader;

		UniquePtr<VertexBuffer> m_VertexBuffer;

		UniquePtr<IndexBuffer> m_IndexBuffer;

		UniquePtr<ConstantBuffer> m_ConstantBuffer;
		
		ID3D11ShaderResourceView* m_FrameReference;

		ID3D11SamplerState* m_TextureSampler;
	};
}
