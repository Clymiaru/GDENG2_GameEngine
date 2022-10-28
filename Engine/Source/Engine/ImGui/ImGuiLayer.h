#pragma once
#include "Engine/Core/Layer.h"

namespace Engine
{
	class ImGuiLayer final : public Layer
	{
	public:
		explicit ImGuiLayer();

		~ImGuiLayer() override;

		void OnAttach() override;

		void OnUpdate() override;

		void OnRender() override;

		void OnDetach() override;
	};
}
