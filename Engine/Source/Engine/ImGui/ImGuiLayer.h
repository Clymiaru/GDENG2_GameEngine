#pragma once
#include "Engine/Core/Layer.h"

namespace Engine
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() override;
	
		void OnAttach() override;
	
		void OnPollInput(InputHandler* inputHandlerRef) override;
	
		void OnUpdate() override;
	
		void OnRender() override;
	
		void OnDetach() override;
	};
}
