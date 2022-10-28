#pragma once

#include "Engine/Core/Core.h"

namespace Engine
{
	class Layer
	{
	public:
		explicit Layer(const std::string& name);

		virtual ~Layer();

		// Executes when this layer is created
		virtual void OnAttach() = 0;

		// Executes per frame
		virtual void OnUpdate() = 0;

		// Executes per frame
		virtual void OnRender() = 0;

		// Executes when this layer is destroyed
		virtual void OnDetach() = 0;

		[[nodiscard]]
		const std::string& GetName() const;

		// Delete Move and Copy functionality for now until we decide on
		// what happens when layers are copied
		Layer(const Layer&) = delete;
	
		Layer& operator=(const Layer& v) = delete;
	
		Layer(Layer&&) noexcept = delete;
	
		Layer& operator=(Layer&&) noexcept = delete;

	private:
		std::string m_Name;
	};
}
