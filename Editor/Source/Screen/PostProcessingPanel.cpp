#include "PostProcessingPanel.h"

#include <Engine/Core/Application.h>
#include <Engine/Math/Math.h>

#include "../Dependencies/ImGui/imgui.h"

#include <Engine/Graphics/PostProcessEffect/PostProcessHandler.h>
#include <Engine/Graphics/PostProcessEffect/VignettePostProcessEffect.h>
#include <Engine/Graphics/PostProcessEffect/SimpleChromaticAberrationPostProcessEffect.h>
#include <Engine/Graphics/PostProcessEffect/CustomPostProcessEffect.h>

namespace Editor
{
	//----------------------------------
	VignetteEffectPropertiesHUD::VignetteEffectPropertiesHUD(Engine::PostProcessEntry& effectRef,
	                                                         Engine::VignetteEffectData& initialData,
	                                                         Engine::PostProcessHandler& postProcessHandlerRef) :
		AUIHUD{"VignetteEffectProperties"},
		m_EffectRef{effectRef},
		m_PostProcessHandlerRef{postProcessHandlerRef},
		m_VignetteEffectData{new Engine::VignetteEffectData()}
	{
		m_VignetteEffectData->EffectColor         = initialData.EffectColor;
		m_VignetteEffectData->EffectPosition      = initialData.EffectPosition;
		m_VignetteEffectData->IntensitySmoothness = initialData.IntensitySmoothness;
	}

	VignetteEffectPropertiesHUD::~VignetteEffectPropertiesHUD()
	{
		delete m_VignetteEffectData;
	}

	Engine::PostProcessEntry& VignetteEffectPropertiesHUD::GetEffectRef() const
	{
		return m_EffectRef;
	}

	void VignetteEffectPropertiesHUD::DrawImpl()
	{
		Engine::String uiID = "##VignetteEffect";
		uiID += std::to_string(m_EffectRef.EffectID);

		Engine::String posLabel = "Position";
		posLabel += uiID;
		ImGui::DragFloat2(posLabel.c_str(),
		                  (float*)&m_VignetteEffectData->EffectPosition, 0.01f);

		Engine::String colorLabel = "Color";
		colorLabel += uiID;
		ImGui::ColorEdit4(colorLabel.c_str(),
		                  (float*)&m_VignetteEffectData->EffectColor);

		Engine::String intensityLabel = "Intensity";
		intensityLabel += uiID;
		ImGui::DragFloat(intensityLabel.c_str(),
		                 &m_VignetteEffectData->IntensitySmoothness.x,
		                 0.01);

		Engine::String smoothnessLabel = "Smoothness";
		smoothnessLabel += uiID;
		ImGui::DragFloat(smoothnessLabel.c_str(),
		                 &m_VignetteEffectData->IntensitySmoothness.y,
		                 0.01);

		m_PostProcessHandlerRef.UpdateEffectData(m_EffectRef.EffectID, m_VignetteEffectData);
	}

	//----------------------------------

	ChromaticAberrationHUD::ChromaticAberrationHUD(Engine::PostProcessEntry& effectRef,
	                                               Engine::SimpleChromaticAberrationEffectData& initialData,
	                                               Engine::PostProcessHandler& postProcessHandlerRef) :
		AUIHUD{"ChromaticAberrationProperties"},
		m_EffectRef{effectRef},
		m_PostProcessHandlerRef{postProcessHandlerRef},
		m_ChromaticAberrationData{new Engine::SimpleChromaticAberrationEffectData()}
	{
		m_ChromaticAberrationData->Direction  = initialData.Direction;
		m_ChromaticAberrationData->ScreenSize = initialData.ScreenSize;
		m_ChromaticAberrationData->RGBOffset  = initialData.RGBOffset;
	}

	ChromaticAberrationHUD::~ChromaticAberrationHUD()
	{
		delete m_ChromaticAberrationData;
	}

	Engine::PostProcessEntry& ChromaticAberrationHUD::GetEffectRef() const
	{
		return m_EffectRef;
	}

	void ChromaticAberrationHUD::DrawImpl()
	{
		Engine::String uiID = "##ChromaticAberration";
		uiID += std::to_string(m_EffectRef.EffectID);

		Engine::String directionLabel = "Direction";
		directionLabel += uiID;
		ImGui::DragFloat2(directionLabel.c_str(),
		                  (float*)&m_ChromaticAberrationData->Direction, 0.01f);

		Engine::String rgbOffsetLabel = "RGBOffset";
		rgbOffsetLabel += uiID;
		ImGui::DragFloat4(rgbOffsetLabel.c_str(),
		                  (float*)&m_ChromaticAberrationData->RGBOffset, 0.01f);

		m_PostProcessHandlerRef.UpdateEffectData(m_EffectRef.EffectID, m_ChromaticAberrationData);
	}

	//----------------------------------
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
			int effectID = -1;
			if (m_CurrentToCreate == 0)
			{
				auto vignetteProperties = Engine::VignetteEffectData(
				                                                     Engine::Color(0.5f,
				                                                                   0.0f,
				                                                                   0.2f,
				                                                                   1.0f),
				                                                     Engine::Vector2Float(0.0f,
				                                                                          0.0f),
				                                                     Engine::Vector2Float(15.0f,
				                                                                          0.75f)
				                                                    );

				effectID = m_PostProcessHandlerRef.
						AddEffect(new Engine::VignettePostProcessEffect(vignetteProperties));

				Engine::PostProcessEntry* entry = m_PostProcessHandlerRef.GetPostProcessEffect(effectID);
				m_VignetteEffectHUDList.push_back(new VignetteEffectPropertiesHUD(*entry,
				                                                                  vignetteProperties,
				                                                                  m_PostProcessHandlerRef));
			}

			if (m_CurrentToCreate == 1)
			{
				auto chromaticAberrationProperties = Engine::SimpleChromaticAberrationEffectData{
					Engine::Color(0.009f, 0.006f, -0.006f, 1.0f),
					Engine::Vector2Float(Engine::Application::WindowRect().Width,
					                     Engine::Application::WindowRect().Height),
					Engine::Vector2Float(-1.0f, 1.0f)
				};

				effectID = m_PostProcessHandlerRef.
						AddEffect(new Engine::SimpleChromaticAberrationPostProcessEffect(chromaticAberrationProperties));

				Engine::PostProcessEntry* entry = m_PostProcessHandlerRef.GetPostProcessEffect(effectID);
				m_ChromaticAberrationHUDList.push_back(new ChromaticAberrationHUD(*entry,
				                                                                  chromaticAberrationProperties,
				                                                                  m_PostProcessHandlerRef));
			}

			if (m_CurrentToCreate == 2)
			{
				effectID = m_PostProcessHandlerRef.
						AddEffect(new Engine::CustomPostProcessEffect());
			}

			m_EffectActiveFlags.push_back({effectID, true});
		}

		ImGui::Separator();

		if (m_PostProcessHandlerRef.GetPostProcessEffectCount() > 0)
		{
			const auto& entries = m_PostProcessHandlerRef.GetAllPostProcessEffects();

			for (auto i = 0; i < entries.size(); i++)
			{
				Engine::String effectName = entries[i].Effect->Name;
				effectName += "##PostProcessEffectChoice";
				effectName += entries[i].EffectID;

				if (ImGui::CollapsingHeader(effectName.c_str(), &m_EffectActiveFlags[i].second))
				{
					if (entries[i].Effect->Name == "VignetteEffect")
					{
						for (int vigHUDIndex = 0; vigHUDIndex < m_VignetteEffectHUDList.size(); vigHUDIndex++)
						{
							if (m_VignetteEffectHUDList[vigHUDIndex]->GetEffectRef().EffectID == entries[i].EffectID)
							{
								m_VignetteEffectHUDList[vigHUDIndex]->Draw();
							}
						}
					}

					if (entries[i].Effect->Name == "SimpleChromaticAberration")
					{
						for (int chromHUDIndex = 0; chromHUDIndex < m_ChromaticAberrationHUDList.size(); chromHUDIndex++)
						{
							if (m_ChromaticAberrationHUDList[chromHUDIndex]->GetEffectRef().EffectID == entries[i].EffectID)
							{
								m_ChromaticAberrationHUDList[chromHUDIndex]->Draw();
							}
						}
					}
				}
			}

			for (auto i = 0; i < entries.size(); i++)
			{
				if (const bool isEnabled = m_EffectActiveFlags[i].second;
					!isEnabled)
				{
					m_EffectActiveFlags.erase(m_EffectActiveFlags.begin() + i);

					for (int vigHUDIndex = 0; vigHUDIndex < m_VignetteEffectHUDList.size(); vigHUDIndex++)
					{
						if (m_VignetteEffectHUDList[vigHUDIndex]->GetEffectRef().EffectID == entries[i].EffectID)
						{
							m_VignetteEffectHUDList.erase(m_VignetteEffectHUDList.begin() + vigHUDIndex);
							m_VignetteEffectHUDList.shrink_to_fit();
						}
					}

					for (int chromHUDIndex = 0; chromHUDIndex < m_ChromaticAberrationHUDList.size(); chromHUDIndex++)
					{
						if (m_ChromaticAberrationHUDList[chromHUDIndex]->GetEffectRef().EffectID == entries[i].EffectID)
						{
							m_ChromaticAberrationHUDList.erase(m_ChromaticAberrationHUDList.begin() + chromHUDIndex);
							m_ChromaticAberrationHUDList.shrink_to_fit();
						}
					}
					
					m_PostProcessHandlerRef.RemoveEffect(entries[i].EffectID);
				}
			}
		}
	}
}
