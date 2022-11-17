#pragma once
#include <d3d11.h>

#include "Engine/Math/Math.h"

#include "Buffer/VertexBuffer.h"
#include "Buffer/IndexBuffer.h"
#include "Buffer/ConstantBuffer.h"

#include "Shader/VertexShader.h"
#include "Shader/PixelShader.h"

namespace Engine
{
	class SwapChain;
	class UISystem;

	// Responsible of utilizing resources for DirectX
	class RenderContext final
	{
	public:
		explicit RenderContext(ID3D11DeviceContext* deviceContext);

		~RenderContext();

		void Release() const;

		ID3D11DeviceContext& GetContext()
		{
			return *m_DeviceContext;
		}

		void ClearRenderTargetView(ID3D11RenderTargetView& renderTarget,
		                           const Color& color) const;

		void ClearDepthStencilView(ID3D11DepthStencilView& depthStencilView) const;

		void SetRenderTargetTo(ID3D11RenderTargetView* renderTarget,
		                       ID3D11DepthStencilView* depthStencil) const;

		template <typename T>
		void SetRenderData(const T& renderData) const;

		template <typename T>
		void UploadShaderData(const ConstantBuffer& constantBuffer) const;

		void UpdateBufferResource(ID3D11Buffer* bufferResource,
		                          const void* updatedBufferData) const;

		void SetTopology(const D3D11_PRIMITIVE_TOPOLOGY& topology) const;

		void DrawIndexed(uint32_t indexCount,
		                 uint32_t startingIndex) const;

		void SetViewportSize(const Vector2Uint& size) const;
		
		void SetViewportSize(const Vector2Float& size) const;

		RenderContext(const RenderContext&) = delete;

		RenderContext& operator=(const RenderContext&) = delete;

		RenderContext(RenderContext&&) noexcept = delete;

		RenderContext& operator=(RenderContext&&) noexcept = delete;

	private:
		ID3D11DeviceContext* m_DeviceContext;

		friend class ConstantBuffer;

		friend class SwapChain;

		// Hack: UISystem needs DeviceContext
		friend class UISystem;
	};

	template <typename T>
	void RenderContext::SetRenderData(const T& renderData) const
	{
	}

	// Shader Binds
	template <>
	inline void RenderContext::SetRenderData<VertexShader>(const VertexShader& toBind) const
	{
		m_DeviceContext->VSSetShader(toBind.m_Data,
		                             nullptr,
		                             0);
	}

	template <>
	inline void RenderContext::SetRenderData<PixelShader>(const PixelShader& toBind) const
	{
		m_DeviceContext->PSSetShader(toBind.m_Data,
		                             nullptr,
		                             0);
	}

	template <>
	inline void RenderContext::SetRenderData<VertexBuffer>(const VertexBuffer& toBind) const
	{
		const uint32_t stride     = static_cast<uint32_t>(toBind.DataTypeSize());
		constexpr uint32_t offset = 0;
		m_DeviceContext->IASetVertexBuffers(0,
		                                    1,
		                                    &toBind.m_Data,
		                                    &stride,
		                                    &offset);
		m_DeviceContext->IASetInputLayout(toBind.m_DataLayout);
	}

	template <>
	inline void RenderContext::SetRenderData<IndexBuffer>(const IndexBuffer& toBind) const
	{
		constexpr UINT offset = 0;
		m_DeviceContext->IASetIndexBuffer(toBind.m_Data, DXGI_FORMAT_R32_UINT, offset);
	}

	template <typename T>
	void RenderContext::UploadShaderData(const ConstantBuffer& constantBuffer) const
	{
	}

	template <>
	inline void RenderContext::UploadShaderData<VertexShader>(const ConstantBuffer& constantBuffer) const
	{
		m_DeviceContext->VSSetConstantBuffers(0,
		                                      1,
		                                      &constantBuffer.m_Data);
	}

	template <>
	inline void RenderContext::UploadShaderData<PixelShader>(const ConstantBuffer& constantBuffer) const
	{
		m_DeviceContext->PSSetConstantBuffers(0,
		                                      1,
		                                      &constantBuffer.m_Data);
	}
}
