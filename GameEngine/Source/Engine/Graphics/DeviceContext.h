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

		auto Initialize() -> void;

		auto Terminate() -> void;

		auto Clear(const SwapChain& swapChain,
		           Color32 color) const -> void;

		auto SetViewportSize(Vector2Uint size) const -> void;

		template <typename T>
		auto SetBuffer(const T& buffer) const -> void;

		template <typename T>
		auto SetConstantBuffer(const ConstantBuffer& constantBuffer) const -> void;

		// Shaders
		template <typename T>
		auto SetShader(const std::wstring& shaderName) const -> void;

		template <typename T>
		auto SetShader(T& shader) const -> void;

		// Draw
		auto SetTopology(const D3D11_PRIMITIVE_TOPOLOGY& topology) -> void;

		auto Draw(Uint indexCount,
		          Uint startingIndex) const -> void;

	private:
		ID3D11DeviceContext* m_DeviceContext;
		D3D11_PRIMITIVE_TOPOLOGY m_Topology;

		friend class ConstantBuffer;
	};

	//---------- SET BUFFER
	template <typename T>
	auto DeviceContext::SetBuffer(const T& buffer) const -> void
	{
	}

	template <>
	inline auto DeviceContext::SetBuffer<VertexBuffer>(const VertexBuffer& buffer) const -> void
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
	inline auto DeviceContext::SetBuffer<IndexBuffer>(const IndexBuffer& buffer) const -> void
	{
		constexpr UINT offset = 0;
		m_DeviceContext->IASetIndexBuffer(buffer.m_Data, DXGI_FORMAT_R32_UINT, offset);
	}

	//---------- SET CONSTANT BUFFER
	template <typename T>
	auto DeviceContext::SetConstantBuffer(const ConstantBuffer& constantBuffer) const -> void
	{
	}

	template <>
	inline auto DeviceContext::SetConstantBuffer<VertexShader>(const ConstantBuffer& constantBuffer) const -> void
	{
		m_DeviceContext->VSSetConstantBuffers(0, 1, &constantBuffer.m_BufferData);
	}

	template <>
	inline auto DeviceContext::SetConstantBuffer<PixelShader>(const ConstantBuffer& constantBuffer) const -> void
	{
		m_DeviceContext->PSSetConstantBuffers(0, 1, &constantBuffer.m_BufferData);
	}

	//---------- SET SHADER
	template <typename T>
	auto DeviceContext::SetShader(const std::wstring& shaderName) const -> void
	{
	}

	template <>
	inline auto DeviceContext::SetShader<VertexShader>(const std::wstring& shaderName) const -> void
	{
		auto& vertexShader = ShaderLibrary::GetInstance().GetShader<VertexShader>(shaderName);
		m_DeviceContext->VSSetShader(&vertexShader.GetData(), nullptr, 0);
	}

	template <>
	inline auto DeviceContext::SetShader<PixelShader>(const std::wstring& shaderName) const -> void
	{
		auto& pixelShader = ShaderLibrary::GetInstance().GetShader<PixelShader>(shaderName);
		m_DeviceContext->PSSetShader(&pixelShader.GetData(), nullptr, 0);
	}

	template <>
	inline auto DeviceContext::SetShader<VertexShader>(VertexShader& shader) const -> void
	{
		m_DeviceContext->VSSetShader(&shader.GetData(), nullptr, 0);
	}

	template <>
	inline auto DeviceContext::SetShader<PixelShader>(PixelShader& shader) const -> void
	{
		m_DeviceContext->PSSetShader(&shader.GetData(), nullptr, 0);
	}
}
