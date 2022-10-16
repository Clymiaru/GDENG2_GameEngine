#pragma once
#include <d3d11.h>

#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "PixelShader.h"
#include "SwapChain.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "Engine/Core/Core.h"
#include "Engine/Core/Math.h"

namespace Engine
{
	class DeviceContext final
	{
	public:
		explicit DeviceContext(ID3D11DeviceContext* deviceContext);

		~DeviceContext();

		void Release() const;

		// Buffers
		template <typename T>
		void SetBuffer(const T& buffer) const;

		template <typename T>
		void SetConstantBuffer(const ConstantBuffer& constantBuffer) const;

		void UpdateConstantBuffer(const ConstantBuffer& constantBuffer,
		                          const void* updatedBufferData);

		// Shaders
		template <typename T>
		void SetShader(T& shader) const;

		// Draw
		void SetTopology(const D3D11_PRIMITIVE_TOPOLOGY& topology);

		void DrawIndexed(Uint indexCount,
		          Uint startingIndex) const;

		void Clear(const SwapChain& swapChain,
		   Color color) const;

		void SetViewportSize(Vector2 size) const;

	private:
		ID3D11DeviceContext* m_DeviceContext;

		D3D11_PRIMITIVE_TOPOLOGY m_Topology;

		friend class ConstantBuffer;
	};

	//---------- SET BUFFER
	template <typename T>
	void DeviceContext::SetBuffer(const T& buffer) const
	{
	}

	template <>
	inline void DeviceContext::SetBuffer<VertexBuffer>(const VertexBuffer& buffer) const
	{
		const Uint stride     = buffer.DataTypeSize();
		constexpr Uint offset = 0;
		m_DeviceContext->IASetVertexBuffers(0,
		                                    1,
		                                    &buffer.m_Data,
		                                    &stride,
		                                    &offset);
		m_DeviceContext->IASetInputLayout(buffer.m_DataLayout);
	}

	template <>
	inline void DeviceContext::SetBuffer<IndexBuffer>(const IndexBuffer& buffer) const
	{
		constexpr UINT offset = 0;
		m_DeviceContext->IASetIndexBuffer(buffer.m_Data, DXGI_FORMAT_R32_UINT, offset);
	}

	//---------- SET CONSTANT BUFFER
	template <typename T>
	void DeviceContext::SetConstantBuffer(const ConstantBuffer& constantBuffer) const
	{
	}

	template <>
	inline void DeviceContext::SetConstantBuffer<VertexShader>(const ConstantBuffer& constantBuffer) const
	{
		m_DeviceContext->VSSetConstantBuffers(0,
		                                      1,
		                                      &constantBuffer.m_Data);
	}

	template <>
	inline void DeviceContext::SetConstantBuffer<PixelShader>(const ConstantBuffer& constantBuffer) const
	{
		m_DeviceContext->PSSetConstantBuffers(0,
		                                      1,
		                                      &constantBuffer.m_Data);
	}

	//---------- SET SHADER
	template <typename T>
	void DeviceContext::SetShader(T& shader) const
	{
	}

	template <>
	inline void DeviceContext::SetShader<VertexShader>(VertexShader& shader) const
	{
		m_DeviceContext->VSSetShader(&shader.GetData(),
		                             nullptr,
		                             0);
	}

	template <>
	inline void DeviceContext::SetShader<PixelShader>(PixelShader& shader) const
	{
		m_DeviceContext->PSSetShader(&shader.GetData(),
		                             nullptr,
		                             0);
	}
}
