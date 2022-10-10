#pragma once
#include "AnimatedQuad.h"

#include "Engine/Core/Layer.h"
#include "Engine/Graphics/RenderObjects/Quad.h"
#include "Engine/Utils/DataStructures.h"
#include "Engine/Utils/Pointers.h"

namespace Editor
{
	class EditorLayer : public Engine::Layer
	{
	public:
		explicit EditorLayer();

		~EditorLayer() override;

		auto OnAttach() -> void override;

		auto OnUpdate() -> void override;

		auto OnRender() -> void override;

		auto OnDetach() -> void override;

	private:
		float m_Time = 0;

		float m_MaxTime = 10.0f;

		float m_Offset = 0.0f;

		Engine::List<Engine::UniquePtr<Engine::Quad>> m_Quads;

		Engine::List<Engine::UniquePtr<AnimatedQuad>> m_AnimQuads;
	};
}
