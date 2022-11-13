#pragma once
#include <Engine/SceneManagement/Scene.h>

namespace Editor
{
	class SampleScene : public Engine::Scene
	{
	public:
		SampleScene();
		~SampleScene() override;
		void OnBegin() override;
		void OnEnd() override;
	};
}
