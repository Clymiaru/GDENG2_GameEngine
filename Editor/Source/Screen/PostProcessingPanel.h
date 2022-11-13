#pragma once
#include <Engine/Core/Core.h>

#include <Engine/UI/AUIScreen.h>

namespace Engine
{
	struct SimpleChromaticAberrationEffectData;

	class PostProcessHandler;

	struct VignetteEffectData;

	struct PostProcessEntry;
}

namespace Editor
{
	class VignetteEffectPropertiesHUD : public Engine::AUIScreen
	{
	public:
		VignetteEffectPropertiesHUD(Engine::PostProcessEntry& effectRef,
		                            Engine::VignetteEffectData& initialData,
		                            Engine::PostProcessHandler& postProcessHandlerRef);

		~VignetteEffectPropertiesHUD() override;

		Engine::PostProcessEntry& GetEffectRef() const;

	private:
		void DrawImpl() override;

		Engine::PostProcessEntry& m_EffectRef;

		Engine::PostProcessHandler& m_PostProcessHandlerRef;

		Engine::VignetteEffectData* m_VignetteEffectData;
	};

	class ChromaticAberrationHUD : public Engine::AUIScreen
	{
	public:
		ChromaticAberrationHUD(Engine::PostProcessEntry& effectRef,
		                       Engine::SimpleChromaticAberrationEffectData& initialData,
		                       Engine::PostProcessHandler& postProcessHandlerRef);

		~ChromaticAberrationHUD() override;

		Engine::PostProcessEntry& GetEffectRef() const;

	private:
		void DrawImpl() override;

		Engine::PostProcessEntry& m_EffectRef;

		Engine::PostProcessHandler& m_PostProcessHandlerRef;

		Engine::SimpleChromaticAberrationEffectData* m_ChromaticAberrationData;
	};

	class PostProcessingPanel final : public Engine::AUIScreen
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
			"Chromatic Aberration",
			"Custom"
		};

		Engine::List<VignetteEffectPropertiesHUD*> m_VignetteEffectHUDList;
		Engine::List<ChromaticAberrationHUD*> m_ChromaticAberrationHUDList;
	};
}
