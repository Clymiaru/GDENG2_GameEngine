#pragma once
#include <d3d11.h>
#include <vector>

#include "Core/SwapChain.h"

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
		Scope<VertexBuffer> VertexBuffer;
	};

	class RenderSystem final
	{
	public:
		static auto GetInstance() -> RenderSystem&;

		auto Initialize(HWND windowHandle,
		                Vector2Int windowSize) -> void;

		auto Release() -> void;

		auto RegisterObject(void* listOfVertices,
		                    UINT vertexSize,
		                    UINT listSize,
		                    void* shaderByteCode,
		                    UINT byteShaderSize) -> void;

		auto static Clear(Color32 fillColor) -> void;

		auto static Draw() -> void;

		auto static SetViewportSize(Vector2Uint viewportSize) -> void;

	private:
		RenderSystem();

		~RenderSystem() = default;

		RenderSystem(const RenderSystem&);

		auto operator=(const RenderSystem&) -> RenderSystem& = delete;

		RenderSystem(const RenderSystem&&) noexcept;

		auto operator=(const RenderSystem&&) -> RenderSystem& = delete;

		Scope<SwapChain> m_SwapChain;

		std::vector<Scope<RenderObject>> m_RenderList;
	};
}
