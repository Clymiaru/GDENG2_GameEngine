#pragma once
#include "AnimatedQuad.h"

#include "Engine/Core/Layer.h"
#include "Engine/Utils/DataStructures.h"
#include "Engine/Utils/Pointers.h"

namespace Editor
{
	class AnimQuadLayer : public Engine::Layer
	{
	public:
		AnimQuadLayer();

		~AnimQuadLayer() override;

		void OnAttach() override;

		void OnUpdate() override;

		void OnRender() override;

		void OnDetach() override;

	private:
		float m_Time = 0;

		float m_MaxTime = 10.0f;

		Engine::List<Engine::UniquePtr<Editor::AnimatedQuad>> m_AnimQuads;
	};
}
