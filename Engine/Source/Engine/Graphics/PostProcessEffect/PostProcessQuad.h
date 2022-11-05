#pragma once
#include <d3d11.h>

#include "Engine/Graphics/RenderData.h"

#include "Engine/Core/Core.h"

namespace Engine
{
	class PostProcessEffect;

	class IndexBuffer;

	class VertexBuffer;

	class VertexShader;

	class PostProcessQuad final
	{
	public:
		explicit PostProcessQuad();

		~PostProcessQuad();

		void Draw(ID3D11ShaderResourceView& renderTargetFrame,
		          const PostProcessEffect& postProcessEffect) const;

		PostProcessQuad(const PostProcessQuad&) = delete;

		PostProcessQuad& operator=(const PostProcessQuad&) = delete;

		PostProcessQuad(PostProcessQuad&&) noexcept = delete;

		PostProcessQuad& operator=(PostProcessQuad&&) noexcept = delete;

	private:
		RenderData* m_RenderData;
		
		SharedPtr<VertexShader> m_VertexShader;

		UniquePtr<VertexBuffer> m_VertexBuffer;

		UniquePtr<IndexBuffer> m_IndexBuffer;

		ID3D11SamplerState* m_TextureSampler;
	};
}
