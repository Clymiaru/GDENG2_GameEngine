#pragma once
#include <d3d11.h>
#include <vector>

#include "Engine/Graphics/SwapChain.h"

#include "Engine/Utils/Color32.h"
#include "Engine/Utils/Pointers.h"

namespace Engine
{
	class VertexBuffer;

	// Idea is that all objects to be rendered are stored here with pre-allocated memory.
	// Then, when rendering occurs, all stored will be rendered. (Not sure how to do other stuff
	// like rendering in order)

	struct RenderObject
	{
		// Entity -> When we need reference to the one being rendered
		ScopePtr<VertexBuffer> VertexBuffer;
	};

	class RenderSystem final
	{
	public:
		static auto GetInstance() -> RenderSystem&;

		auto Initialize(HWND windowHandle,
		                Vector2Int windowSize) -> void;

		auto Terminate() -> void;

		auto GetDevice() -> ID3D11Device*;

		auto GetDeviceContext() -> DeviceContext&;

		auto RegisterObject(void* listOfVertices,
		                    UINT vertexSize,
		                    UINT listSize,
		                    void* shaderByteCode,
		                    UINT byteShaderSize) -> void;

		auto static Clear(Color32 fillColor) -> void;

		auto static Draw() -> void;

		auto static SetViewportSize(Vector2Uint viewportSize) -> void;

		auto CompileVertexShader(const std::wstring& fileName,
		                         const std::string& entryPointName,
		                         void** shaderByteCode,
		                         size_t* byteCodeSize) -> bool;

		auto CompilePixelShader(const std::wstring& fileName,
		                        const std::string& entryPointName,
		                        void** shaderByteCode,
		                        size_t* byteCodeSize) -> bool;

		auto ReleaseCompiledShader() const -> void;

	private:
		RenderSystem();

		~RenderSystem() = default;

		RenderSystem(const RenderSystem&);

		auto operator=(const RenderSystem&) -> RenderSystem& = delete;

		RenderSystem(const RenderSystem&&) noexcept;

		auto operator=(const RenderSystem&&) -> RenderSystem& = delete;

		ScopePtr<SwapChain> m_SwapChain;

		ScopePtr<DeviceContext> m_DeviceContext;

		ID3D11Device* m_Device;

		D3D_FEATURE_LEVEL m_FeatureLevel;

		IDXGIDevice* m_DxgiDevice;

		IDXGIAdapter* m_DxgiAdapter;

		IDXGIFactory* m_DxgiFactory;

		std::vector<ScopePtr<RenderObject>> m_RenderList;

		// Transfer to a ShaderCompilerClass?
		ID3DBlob* m_Blob = nullptr;

		ID3D11VertexShader* m_VertexShader = nullptr;

		ID3D11PixelShader* m_PixelShader = nullptr;
	};
}
