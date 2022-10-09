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
		virtual auto OnAttach() -> void = 0;

		// Executes per frame
		virtual auto OnUpdate() -> void = 0;

		// Executes per frame
		virtual auto OnRender() -> void = 0;

		// Executes when this layer is destroyed
		virtual auto OnDetach() -> void = 0;

		[[nodiscard]]
		auto GetName() const -> const std::string&;

	private:
		std::string m_Name;
	};
}
