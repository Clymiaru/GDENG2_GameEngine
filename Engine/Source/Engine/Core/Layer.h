#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Graphics/Framebuffer.h"

namespace Engine
{
	class Input;
	class Renderer;
	class Layer
	{
	public:
		explicit Layer(const String& name);

		virtual ~Layer();

		// Executes when this layer is created
		virtual void OnAttach() = 0;

		virtual void OnPollInput() = 0;

		virtual void OnUpdate() = 0;

		virtual void OnRender() = 0;

		virtual void OnImGuiRender() = 0;
		
		// Executes when this layer is destroyed
		virtual void OnDetach() = 0;

		[[nodiscard]]
		const String& GetName() const
		{
			return m_Name;
		}

		[[nodiscard]]
		Framebuffer* GetFramebuffer() const
		{
			return m_Framebuffer.get();
		}

		// Delete Move and Copy functionality for now until we decide on
		// what happens when layers are copied
		Layer(const Layer&) = delete;
	
		Layer& operator=(const Layer&) = delete;
	
		Layer(Layer&&) noexcept = delete;
	
		Layer& operator=(Layer&&) noexcept = delete;

	private:
		String m_Name;

	protected:
		UniquePtr<Framebuffer> m_Framebuffer;
	};
}
