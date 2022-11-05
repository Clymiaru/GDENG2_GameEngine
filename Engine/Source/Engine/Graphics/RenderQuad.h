#pragma once
#include "Engine/Core/Core.h"

#include "RenderData.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "PixelShader.h"
#include "VertexShader.h"

namespace Engine
{
	class RenderQuad
	{
	public:
		explicit RenderQuad();

		~RenderQuad();

		void Draw(ID3D11ShaderResourceView& renderTargetFrame) const;

		RenderQuad(const RenderQuad&) = delete;

		RenderQuad& operator=(const RenderQuad&) = delete;

		RenderQuad(RenderQuad&&) noexcept = delete;

		RenderQuad& operator=(RenderQuad&&) noexcept = delete;
		
	private:
		RenderData* m_RenderData;
		
		SharedPtr<VertexShader> m_VertexShader{};
		
		SharedPtr<PixelShader> m_PixelShader{};

		UniquePtr<VertexBuffer> m_VertexBuffer{};

		UniquePtr<IndexBuffer> m_IndexBuffer{};

		ID3D11SamplerState* m_TextureSampler;
	};
}
