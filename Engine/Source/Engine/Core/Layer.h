#pragma once

#include "Time.h"

#include "Engine/Core/Core.h"
#include "Engine/Input/InputData.h"

namespace Engine
{
	class Layer
	{
	public:
		explicit Layer(const String& name);

		virtual ~Layer();

		// Executes when this layer is created
		virtual void OnAttach() = 0;

		// Executes when OnAttach is finished
		virtual void OnStart() = 0;

		virtual void OnPollInput(const InputData& inputData) = 0;

		virtual void OnUpdate(const TimeData& timeData) = 0;

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
