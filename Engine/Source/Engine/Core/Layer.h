#pragma once

// Game Loop

// All OnCreate executes (Executes once)

// All OnUpdate executes

// All OnDestroy executes (Executes once)

namespace Engine
{
	class Layer
	{
	public:
		Layer(const std::string& name);

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

	private:
		std::string m_Name;
	};
}
