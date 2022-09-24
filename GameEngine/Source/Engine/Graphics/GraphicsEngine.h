#pragma once
#include <d3d11.h>
#include <string>

#include <Engine/Utils/Pointers.h>
#include "Engine/Utils/Color32.h"
#include "Engine/Utils/Math.h"

namespace Engine
{
	class SwapChain;

	class DeviceContext;

	class VertexBuffer;

	class VertexShader;

	class PixelShader;

	class GraphicsEngine final
	{
	public:
		GraphicsEngine(const GraphicsEngine&) = delete;

		~GraphicsEngine() = default;

		auto Init() -> void;

		auto Release() const -> void;

		auto Clear(const Scope<SwapChain>& swapChain,
		           Color32 fillColor) const -> void;

		[[nodiscard]]
		auto CreateSwapChain() const -> Scope<SwapChain>;

		[[nodiscard]]
		auto CreateVertexBuffer() const -> Scope<VertexBuffer>;

		auto CreateVertexShader(const void* shaderByteCode,
		                        size_t byteCodeSize) const -> Scope<VertexShader>;

		auto CreatePixelShader(const void* shaderByteCode,
								size_t byteCodeSize) const -> Scope<PixelShader>;

		auto CompileVertexShader(const std::wstring& fileName,
		                         const std::string& entryPointName,
		                         void** shaderByteCode,
		                         size_t* byteCodeSize) -> bool;

		auto CompilePixelShader(const std::wstring& fileName,
								 const std::string& entryPointName,
								 void** shaderByteCode,
								 size_t* byteCodeSize) -> bool;

		auto ReleaseCompiledShader() const -> void;

		static auto GetInstance() -> GraphicsEngine&;

		auto GetImmediateDeviceContext() -> const Scope<DeviceContext>&;

	private:
		GraphicsEngine();

		Scope<DeviceContext> m_ImmediateDeviceContext;

		ID3D11Device* m_D3DDevice;

		D3D_FEATURE_LEVEL m_FeatureLevel;

		IDXGIDevice* m_DxgiDevice;

		IDXGIAdapter* m_DxgiAdapter;

		IDXGIFactory* m_DxgiFactory;

		ID3D11DeviceContext* m_DeviceContext;

		ID3DBlob* m_Blob = nullptr;

		ID3DBlob* m_VSblob = nullptr;

		ID3DBlob* m_PSblob = nullptr;

		ID3D11VertexShader* m_VertexShader = nullptr;

		ID3D11PixelShader* m_PixelShader = nullptr;

		friend class SwapChain;

		friend class VertexBuffer;

		friend class VertexShader;

		friend class PixelShader;
	};
}
