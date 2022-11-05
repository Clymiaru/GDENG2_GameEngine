#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "PixelShader.h"
#include "VertexShader.h"

#include "Engine/Graphics/RenderData.h"
#include "Engine/Core/Core.h"

namespace Engine
{
	class RenderQuad
	{
	public:
		explicit RenderQuad();

		~RenderQuad();

		void Draw(ID3D11ShaderResourceView& renderTargetFrame);

		RenderQuad(const RenderQuad&) = delete;

		RenderQuad& operator=(const RenderQuad&) = delete;

		RenderQuad(RenderQuad&&) noexcept = delete;

		RenderQuad& operator=(RenderQuad&&) noexcept = delete;
	private:
		SharedPtr<VertexShader> m_VertexShader;
		
		SharedPtr<PixelShader> m_PixelShader;

		UniquePtr<VertexBuffer> m_VertexBuffer;

		UniquePtr<IndexBuffer> m_IndexBuffer;

		ID3D11SamplerState* m_TextureSampler;
	};
}
