#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>

#include "DeviceContext.h"
#include "VertexShader.h"
#include "PixelShader.h"

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

		static void ShowFrame();

		static void SetViewportSize(Vector2 viewportSize);

	private:
		RenderSystem();

		~RenderSystem();

		static RenderSystem m_Instance;

		UniquePtr<SwapChain> m_SwapChain;

		UniquePtr<DeviceContext> m_DeviceContext;

		ID3D11Device* m_Device;

		D3D_FEATURE_LEVEL m_FeatureLevel;

		IDXGIDevice* m_DxgiDevice;

		IDXGIAdapter* m_DxgiAdapter;

		IDXGIFactory* m_DxgiFactory;
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
