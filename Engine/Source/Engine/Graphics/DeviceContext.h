#pragma once
#include <d3d11.h>

#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "PixelShader.h"
#include "ShaderLibrary.h"
#include "VertexBuffer.h"
#include "VertexShader.h"

#include "Engine/Utils/Color32.h"
#include "Engine/Utils/Math.h"
#include "Engine/Utils/Pointers.h"

namespace Engine
{
	class SwapChain;

	class VertexBuffer;

	class IndexBuffer;

	class ConstantBuffer;

	class VertexShader;

	class PixelShader;

	class DeviceContext final
	{
	public:
		explicit DeviceContext(ID3D11DeviceContext* deviceContext);

		~DeviceContext();

		static void Initialize();

		void Terminate() const;

		void Clear(const SwapChain& swapChain,
		           Color32 color) const;

		void SetViewportSize(Vector2Uint size) const;

		template <typename T>
		void SetBuffer(const T& buffer) const;

		template <typename T>
		void SetConstantBuffer(const ConstantBuffer& constantBuffer) const;

		// Shaders
		template <typename T>
		void SetShader(const std::wstring& shaderName) const;

		template <typename T>
		void SetShader(T& shader) const;

		// Draw
		void SetTopology(const D3D11_PRIMITIVE_TOPOLOGY& topology);

		void Draw(Uint indexCount,
		          Uint startingIndex) const;

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
		const UINT stride     = buffer.m_DataSize;
		constexpr UINT offset = 0;
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
		m_DeviceContext->VSSetConstantBuffers(0, 1, &constantBuffer.m_BufferData);
	}

	template <>
	inline void DeviceContext::SetConstantBuffer<PixelShader>(const ConstantBuffer& constantBuffer) const
	{
		m_DeviceContext->PSSetConstantBuffers(0, 1, &constantBuffer.m_BufferData);
	}

	//---------- SET SHADER
	template <typename T>
	void DeviceContext::SetShader(const std::wstring& shaderName) const
	{
	}

	template <typename T>
	void DeviceContext::SetShader(T& shader) const
	{
	}

	template <>
	inline void DeviceContext::SetShader<VertexShader>(const std::wstring& shaderName) const
	{
		auto& vertexShader = ShaderLibrary::GetShader<VertexShader>(shaderName);
		m_DeviceContext->VSSetShader(&vertexShader.GetData(), nullptr, 0);
	}

	template <>
	inline void DeviceContext::SetShader<PixelShader>(const std::wstring& shaderName) const
	{
		auto& pixelShader = ShaderLibrary::GetShader<PixelShader>(shaderName);
		m_DeviceContext->PSSetShader(&pixelShader.GetData(), nullptr, 0);
	}

	template <>
	inline void DeviceContext::SetShader<VertexShader>(VertexShader& shader) const
	{
		m_DeviceContext->VSSetShader(&shader.GetData(), nullptr, 0);
	}

	template <>
	inline void DeviceContext::SetShader<PixelShader>(PixelShader& shader) const
	{
		m_DeviceContext->PSSetShader(&shader.GetData(), nullptr, 0);
	}
}
