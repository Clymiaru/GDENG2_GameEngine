#pragma once
#include <d3d11.h>
#include <string>
#include <vector>

#include <Engine/Utils/Pointers.h>
#include "Engine/Utils/Color32.h"
#include "Engine/Utils/Math.h"

namespace Engine
{
	class SwapChain;

	class DeviceContext;

	class VertexBuffer;

	class ConstantBuffer;

	class VertexShader;

	class PixelShader;

	class IRenderable;

	class GraphicsEngine final
	{
	public:
		auto Init(HWND windowHandle,
		          const Vector2Int& windowSize) -> void;

		auto Release() const -> void;

		auto static Clear(const Color32 fillColor) -> void;

		auto static SetViewportSize(const UINT width,
		                            const UINT height) -> void;

		auto static Draw() -> void;

		static auto RegisterRenderable(const Ref<IRenderable>& toRegister) -> void;

		[[nodiscard]]
		auto CreateSwapChain() const -> Scope<SwapChain>;

		[[nodiscard]]
		auto CreateVertexBuffer() const -> Scope<VertexBuffer>;

		[[nodiscard]]
		auto CreateConstantBuffer() const -> Scope<ConstantBuffer>;

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

		~GraphicsEngine() = default;

		GraphicsEngine(const GraphicsEngine&);

		GraphicsEngine& operator=(const GraphicsEngine&) = delete;

		GraphicsEngine(const GraphicsEngine&&) noexcept;

		GraphicsEngine& operator=(const GraphicsEngine&&) = delete;

		Scope<DeviceContext> m_ImmediateDeviceContext;

		Scope<SwapChain> m_SwapChain;

		ID3D11Device* m_D3DDevice;

		D3D_FEATURE_LEVEL m_FeatureLevel;

		IDXGIDevice* m_DxgiDevice;

		IDXGIAdapter* m_DxgiAdapter;

		IDXGIFactory* m_DxgiFactory;

		ID3D11DeviceContext* m_DeviceContext;

		ID3DBlob* m_Blob = nullptr;

		ID3D11VertexShader* m_VertexShader = nullptr;

		ID3D11PixelShader* m_PixelShader = nullptr;

		std::vector<Ref<IRenderable>> m_RenderList;

		friend class SwapChain;

		friend class VertexBuffer;

		friend class ConstantBuffer;

		friend class VertexShader;

		friend class PixelShader;
	};
}
