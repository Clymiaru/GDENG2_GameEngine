#pragma once
#include <d3d11.h>
#include "RenderDevice.h"
#include "RenderContext.h"

namespace Engine
{
	class Renderer final
	{
	public:
		explicit Renderer();
		
		~Renderer();

		// Takes in the Framebuffer to clear then set it as current render target
		void StartRender(const Framebuffer& framebuffer);
		
		// Removes the bound framebuffer as rendertarget
		void EndRender();
		
		void SetViewportSize(const Vector2Uint& viewportSize) const;
		
		void SetFramebuffer(const Framebuffer& framebuffer) const;
		
		void ClearFramebuffer(const Framebuffer& framebuffer) const;
		
		// TODO: Maybe set RasterState
		
		[[nodiscard]]
		RenderDevice& GetDevice() const;

		RenderContext& GetContext() const;

		Renderer(const Renderer&)                = delete;
		Renderer& operator=(const Renderer&)     = delete;
		Renderer(Renderer&&) noexcept            = delete;
		Renderer& operator=(Renderer&&) noexcept = delete;

	private:
		RenderContext* m_Context;

		RenderDevice* m_Device;

		D3D_FEATURE_LEVEL m_FeatureLevel;
	};
}
