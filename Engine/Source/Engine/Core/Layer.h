#pragma once

#include "Engine/Core/Core.h"

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

		// Executes when this layer is destroyed
		virtual void OnDetach() = 0;

		[[nodiscard]]
		const String& GetName() const
		{
			return m_Name;
		}

		Layer(const Layer&) = delete;
	
		Layer& operator=(const Layer&) = delete;
	
		Layer(Layer&&) noexcept = delete;
	
		Layer& operator=(Layer&&) noexcept = delete;

	private:
		String m_Name;
	};
}
