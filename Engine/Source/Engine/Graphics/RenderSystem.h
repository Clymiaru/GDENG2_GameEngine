#pragma once
#include <d3d11.h>

#include "DeviceContext.h"
#include "PixelShader.h"
#include "VertexShader.h"

namespace Engine
{
	class VertexShader;

	class DeviceContext;

	class Primitive;

	class SwapChain;

	class VertexBuffer;

	class IndexBuffer;

	class Window;

	class RenderSystem final
	{
	public:
		RenderSystem(const RenderSystem&) = delete;

		static void Start(Window& window);

		static void End();

		[[nodiscard]]
		static ID3D11Device& GetDevice();
		
		[[nodiscard]]
		static DeviceContext& GetDeviceContext();

		//---------- RENDER COMMANDS
		static void Clear(Color fillColor);

		template <typename ShaderType>
		static void SetShader(ShaderType& shader);

		template <typename ShaderType>
		static void SetConstantBuffer(const ConstantBuffer& constantBuffer);

		static void Draw(const VertexBuffer& vertexBuffer,
		                 const IndexBuffer& indexBuffer);

		// Submit(VertexShader, PixelShader, ConstantBuffer, VertexBuffer, IndexBuffer, Topology)
		static void Draw(VertexShader& vertexShader,
		                 PixelShader& pixelShader,
		                 const VertexBuffer& vertexBuffer,
		                 const IndexBuffer& indexBuffer,
		                 const ConstantBuffer& constantBuffer,
		                 const void* updatedConstantBuffer,
		                 D3D11_PRIMITIVE_TOPOLOGY topology);

		static void ShowFrame();

		static void SetViewportSize(Vector2 viewportSize);

	private:
		RenderSystem();

		~RenderSystem();

		static RenderSystem m_Instance;

		UniquePtr<SwapChain> m_SwapChain;

		UniquePtr<DeviceContext> m_DeviceContext;
	};

	template <typename ShaderType>
	void RenderSystem::SetShader(ShaderType& shader)
	{
	}

	template <>
	inline void RenderSystem::SetShader<VertexShader>(VertexShader& shader)
	{
		m_Instance.m_DeviceContext->SetShader(shader);
	}

	template <>
	inline void RenderSystem::SetShader<PixelShader>(PixelShader& shader)
	{
		m_Instance.m_DeviceContext->SetShader(shader);
	}

	template <typename ShaderType>
	void RenderSystem::SetConstantBuffer(const ConstantBuffer& constantBuffer)
	{
	}

	template <>
	inline void RenderSystem::SetConstantBuffer<VertexShader>(const ConstantBuffer& constantBuffer)
	{
		m_Instance.m_DeviceContext->SetConstantBuffer<VertexShader>(constantBuffer);
	}

	template <>
	inline void RenderSystem::SetConstantBuffer<PixelShader>(const ConstantBuffer& constantBuffer)
	{
		m_Instance.m_DeviceContext->SetConstantBuffer<PixelShader>(constantBuffer);
	}
}
