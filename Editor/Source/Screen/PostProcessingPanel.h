#pragma once
#include <Engine/Core/Core.h>
#include <Engine/UI/AUIPanel.h>

namespace Engine
{
	class PostProcessHandler;
}

namespace Editor
{
	class PostProcessingPanel final : public Engine::AUIPanel
	{
	public:
		explicit PostProcessingPanel(Engine::PostProcessHandler& postProcessHandler);

		~PostProcessingPanel() override;

		void DrawImpl() override;

	private:
		int m_CurrentToCreate;
		Engine::String m_CurrentToCreatePreview;

		Engine::List<std::pair<int, bool>> m_EffectActiveFlags;

		Engine::PostProcessHandler& m_PostProcessHandlerRef;

		Engine::List<Engine::String> m_AvailablePostEffectOptions =
		{
			"Vignette",
			"Chromatic Aberration"
		};


	};
}
