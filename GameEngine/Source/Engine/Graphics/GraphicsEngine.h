#pragma once
#include <d3d11.h>

#include "Engine/Utils/Math.h"
#include <Engine/Utils/Pointers.h>

#include "Engine/Utils/Color32.h"

namespace Engine
{
	class SwapChain;
	class DeviceContext;
	class VertexBuffer;
	class GraphicsEngine
	{
	public:
		GraphicsEngine(const GraphicsEngine&) = delete;
		~GraphicsEngine();

		void Init(HWND windowHandle, const Engine::Vector2Int& windowSize);
		void Release();

		void Clear(Color32 fillColor);
		void Draw();

		VertexBuffer* CreateVertexBuffer();

		bool CreateShaders();
		bool SetShaders();
		void GetShaderBufferAndSize(void** bytecode, UINT* size);


		static GraphicsEngine& GetInstance();

		static Scope<SwapChain> CreateSwapChain();

		const Scope<DeviceContext>& GetImmediateDeviceContext();
	private:
		GraphicsEngine();

		bool InitSwapChain(HWND windowHandle, const Engine::Vector2Int& windowSize);

		ID3D11Device* m_D3DDevice;
		D3D_FEATURE_LEVEL m_FeatureLevel;
		ID3D11DeviceContext* m_DeviceContext;

		IDXGIDevice* m_DXGIDevice;
		IDXGIAdapter* m_DXGIAdapter;
		IDXGIFactory* m_DXGIFactory;

		Scope<DeviceContext> m_ImmediateDeviceContext;
		Scope<SwapChain> m_SwapChain;

		ID3DBlob* m_VSblob = nullptr;
		ID3DBlob* m_PSblob = nullptr;
		ID3D11VertexShader* m_VS = nullptr;
		ID3D11PixelShader* m_PS = nullptr;

	private:
		friend class SwapChain;
		friend class VertexBuffer;

	};
}