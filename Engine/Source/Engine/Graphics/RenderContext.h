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

		void ClearRenderTargetView(ID3D11RenderTargetView& renderTarget,
		                           const Color& color) const;

		void ClearDepthStencilView(ID3D11DepthStencilView& depthStencilView) const;

		void SetRenderTargetTo(ID3D11RenderTargetView* renderTarget,
		                       ID3D11DepthStencilView* depthStencil) const;

		template <typename RenderDataType>
		void Bind(const RenderDataType& data) const;

		template <typename ShaderType>
		void Bind(uint32_t slot, const ConstantBuffer& data) const;

		template <typename ShaderType>
		void Bind(uint32_t startSlot, uint32_t viewCount, ID3D11ShaderResourceView** srvList);

		template <typename ShaderType>
		void Bind(uint32_t startSlot, uint32_t samplerCount, ID3D11SamplerState** samplerList);

		void Bind(D3D11_PRIMITIVE_TOPOLOGY topology) const;

		void UpdateBufferResource(ID3D11Buffer* bufferResource,
		                          const void* updatedBufferData) const;

		void DrawIndexed(uint32_t indexCount,
		                 uint32_t startingIndex) const;

		void SetViewportSize(const Vector2Uint& size) const;

		void SetViewportSize(const Vector2Float& size) const;

		RenderContext(const RenderContext&)                = delete;
		RenderContext& operator=(const RenderContext&)     = delete;
		RenderContext(RenderContext&&) noexcept            = delete;
		RenderContext& operator=(RenderContext&&) noexcept = delete;

	private:
		ID3D11DeviceContext* m_DeviceContext;

		friend class ConstantBuffer;

		friend class SwapChain;

		// Hack: UISystem needs DeviceContext
		friend class UISystem;
	};

	template <typename RenderDataType>
	void RenderContext::Bind(const RenderDataType& data) const
	{
		Debug::Log("RenderContext Bind: Unsupported RenderDataType!");
	}

	template <>
	inline void RenderContext::Bind<VertexShader>(const VertexShader& data) const
	{
		m_DeviceContext->VSSetShader(&data.GetData(), nullptr, 0);
	}

	template <>
	inline void RenderContext::Bind<PixelShader>(const PixelShader& data) const
	{
		m_DeviceContext->PSSetShader(&data.GetData(), nullptr, 0);
	}

	template <>
	inline void RenderContext::Bind<VertexBuffer>(const VertexBuffer& data) const
	{
		const uint32_t stride             = static_cast<uint32_t>(data.DataTypeSize());
		constexpr uint32_t offset         = 0;
		const List<ID3D11Buffer*> buffers = {&data.GetData()};

		m_DeviceContext->IASetVertexBuffers(0,
		                                    buffers.size(),
		                                    buffers.data(),
		                                    &stride,
		                                    &offset);
		m_DeviceContext->IASetInputLayout(&data.GetInputLayout());
	}

	template <>
	inline void RenderContext::Bind<IndexBuffer>(const IndexBuffer& data) const
	{
		constexpr UINT offset = 0;
		m_DeviceContext->IASetIndexBuffer(&data.GetData(), DXGI_FORMAT_R32_UINT, offset);
	}

	template <typename ShaderType>
	void RenderContext::Bind(uint32_t slot, const ConstantBuffer& data) const
	{
		Debug::Log("RenderContext Bind::ConstantBuffer: Unsupported ShaderType!");
	}

	template <>
	inline void RenderContext::Bind<VertexShader>(const uint32_t slot, const ConstantBuffer& data) const
	{
		const List<ID3D11Buffer*> buffers = {&data.GetData()};
		m_DeviceContext->VSSetConstantBuffers(slot,
		                                      1,
		                                      buffers.data());
	}

	template <>
	inline void RenderContext::Bind<PixelShader>(const uint32_t slot, const ConstantBuffer& data) const
	{
		const List<ID3D11Buffer*> buffers = {&data.GetData()};
		m_DeviceContext->PSSetConstantBuffers(slot,
		                                      1,
		                                      buffers.data());
	}

	template <typename ShaderType>
	void RenderContext::Bind(uint32_t startSlot,
	                         uint32_t viewCount,
	                         ID3D11ShaderResourceView** srvList)
	{
		Debug::Log("RenderContext Bind::ShaderResourceView: Unsupported ShaderType!");
	}

	template <>
	inline void RenderContext::Bind<VertexShader>(const uint32_t startSlot,
	                                              const uint32_t viewCount,
	                                              ID3D11ShaderResourceView** srvList)
	{
		m_DeviceContext->VSSetShaderResources(startSlot, viewCount, srvList);
	}

	template <>
	inline void RenderContext::Bind<PixelShader>(const uint32_t startSlot,
	                                             const uint32_t viewCount,
	                                             ID3D11ShaderResourceView** srvList)
	{
		m_DeviceContext->PSSetShaderResources(startSlot, viewCount, srvList);
	}

	template <typename ShaderType>
	void RenderContext::Bind(uint32_t startSlot,
	                         uint32_t samplerCount,
	                         ID3D11SamplerState** samplerList)
	{
		Debug::Log("RenderContext Bind::Sampler: Unsupported ShaderType!");
	}

	template <>
	inline void RenderContext::Bind<VertexShader>(const uint32_t startSlot,
	                                              const uint32_t samplerCount,
	                                              ID3D11SamplerState** samplerList)
	{
		m_DeviceContext->VSSetSamplers(startSlot, samplerCount, samplerList);
	}

	template <>
	inline void RenderContext::Bind<PixelShader>(const uint32_t startSlot,
	                                             const uint32_t samplerCount,
	                                             ID3D11SamplerState** samplerList)
	{
		m_DeviceContext->PSSetSamplers(startSlot, samplerCount, samplerList);
	}

	inline void RenderContext::Bind(const D3D11_PRIMITIVE_TOPOLOGY topology) const
	{
		m_DeviceContext->IASetPrimitiveTopology(topology);
	}
}
