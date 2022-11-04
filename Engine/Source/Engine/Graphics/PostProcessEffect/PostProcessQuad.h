#pragma once
#include "PostProcessEffect.h"

#include <d3d11.h>

#include "Engine/Graphics/RenderData.h"

#include "Engine/Core/Core.h"

namespace Engine
{
	class IndexBuffer;

	class VertexBuffer;

	class PixelShader;

	class VertexShader;

	class PostProcessQuad final
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

		UniquePtr<VertexBuffer> m_VertexBuffer;

		UniquePtr<IndexBuffer> m_IndexBuffer;

		PostProcessEffect* m_PostProcessEffect;
		
		ID3D11ShaderResourceView* m_FrameReference;

		ID3D11SamplerState* m_TextureSampler;
	};
}