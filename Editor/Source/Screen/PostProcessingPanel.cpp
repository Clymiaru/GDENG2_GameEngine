#include "PostProcessingPanel.h"

#include <Engine/Core/Application.h>
#include <Engine/Math/Color.h>
#include <Engine/Math/Vector2.h>

#include <Engine/Graphics/PostProcessEffect/PostProcessHandler.h>
#include <Engine/Graphics/PostProcessEffect/VignettePostProcessEffect.h>
#include <Engine/Graphics/PostProcessEffect/SimpleChromaticAberrationPostProcessEffect.h>


namespace Editor
{
	PostProcessingPanel::PostProcessingPanel(Engine::PostProcessHandler& postProcessHandler) :
		AUIPanel{"Post Processing"},
		m_CurrentToCreate{0},
		m_CurrentToCreatePreview{"Default"},
		m_EffectActiveFlags{Engine::List<std::pair<int, bool>>()},
		m_PostProcessHandlerRef{postProcessHandler}
	{
	}

	PostProcessingPanel::~PostProcessingPanel() = default;

	void PostProcessingPanel::DrawImpl()
	{
		ImGui::Text("Post Processing Effects");
		
		m_CurrentToCreatePreview = m_AvailablePostEffectOptions[m_CurrentToCreate];
		
		if (ImGui::BeginCombo("##PostProcessEffectsControl", m_CurrentToCreatePreview.c_str()))
		{
			for (int i = 0; i < (int)m_AvailablePostEffectOptions.size(); i++)
			{
				const bool isSelected = m_CurrentToCreate == i;
		
				if (ImGui::Selectable(m_AvailablePostEffectOptions[i].c_str(), isSelected))
				{
					m_CurrentToCreate = i;
				}
		
				if (isSelected)
					ImGui::SetItemDefaultFocus();
			}
		
			ImGui::EndCombo();
		}
		
		ImGui::SameLine();
		
		if (ImGui::Button("Create##PostProcessEffectsControl"))
		{
			if (m_CurrentToCreate == 0)
			{
				const auto vignetteProperties = Engine::VignetteEffectData{
					Engine::Color(0.5f, 0.0f, 0.2f, 1.0f),
					Engine::Vector2Float(1.0f, 0.0f),
					Engine::Vector2Float(Engine::Application::WindowRect().Width,
					                     Engine::Application::WindowRect().Height)
				};
		
				m_PostProcessHandlerRef.AddEffect(new Engine::VignettePostProcessEffect(vignetteProperties));
			}
		
			if (m_CurrentToCreate == 1)
			{
				const auto chromaticAberrationProperties = Engine::SimpleChromaticAberrationEffectData{
					Engine::Vector2Float(Engine::Application::WindowRect().Width,
					                     Engine::Application::WindowRect().Height),
					Engine::Vector2Float(-1.0f, 1.0f)
				};
		
				m_PostProcessHandlerRef.
						AddEffect(new Engine::SimpleChromaticAberrationPostProcessEffect(chromaticAberrationProperties));
			}
		
			m_EffectActiveFlags.push_back({m_CurrentToCreate, true});
		}
		
		ImGui::Separator();

		if (m_PostProcessHandlerRef.GetPostProcessEffectCount() > 0)
		{
			const auto& entries = m_PostProcessHandlerRef.GetAllPostProcessEffects();
			for (auto i = 0; i < entries.size(); i++)
			{
				Engine::String effectName = entries[i].Effect->Name;
				effectName += "##PostProcessEffectChoice";
		
				if (ImGui::CollapsingHeader(effectName.c_str(), &m_EffectActiveFlags[i].second))
				{
					ImGui::Text("IsItemHovered: %d", ImGui::IsItemHovered());
				}
			}
		
			for (auto i = 0; i < entries.size(); i++)
			{
				if (const bool isEnabled = m_EffectActiveFlags[i].second;
					!isEnabled)
				{
					m_EffectActiveFlags.erase(m_EffectActiveFlags.begin() + i);
					m_PostProcessHandlerRef.RemoveEffect(entries[i].EffectID);
				}
			}
		}
	}
}
