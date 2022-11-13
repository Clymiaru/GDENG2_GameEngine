#include "pch.h"
#include "PostProcessHandler.h"

#include "PostProcessEffect.h"
#include "PostProcessQuad.h"

#include "Engine/Core/Application.h"
#include "Engine/Graphics/Framebuffer.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/ShaderLibrary.h"

namespace Engine
{
	PostProcessHandler::PostProcessHandler(int numberOfPostProcessEffects) :
		m_PostProcessEffectList{List<PostProcessEntry>()}
	{
		m_PostProcessEffectList.reserve(numberOfPostProcessEffects);
	}

	PostProcessHandler::~PostProcessHandler()
	{
		m_PostProcessEffectList.clear();
	}

	void PostProcessHandler::Start()
	{
		ShaderLibrary::Register<VertexShader>("Assets/Shaders/PostProcess/VSQuad_FX.hlsl");
	}

	void PostProcessHandler::End()
	{
		m_PostProcessEffectList.erase(m_PostProcessEffectList.begin(),
		                              m_PostProcessEffectList.end());
	}

	int PostProcessHandler::AddEffect(PostProcessEffect* postProcessEffect)
	{
		FramebufferProfile postProcessFramebufferProfile;
		postProcessFramebufferProfile.Width  = Application::GetWindowInfo().Width;
		postProcessFramebufferProfile.Height = Application::GetWindowInfo().Height;

		int postProcessEffectID = (int)m_PostProcessEffectList.size();
		if (!m_ReservedID.empty())
		{
			postProcessEffectID = m_ReservedID.front();
			m_ReservedID.pop();
		}

		PostProcessEntry entry;
		entry.EffectID    = postProcessEffectID;
		entry.Effect      = std::move(postProcessEffect);
		entry.Frame       = new PostProcessQuad();
		entry.Framebuffer = new Framebuffer(postProcessFramebufferProfile,
		                                    Renderer::GetDevice());

		m_PostProcessEffectList.emplace_back(entry);

		return (int)m_PostProcessEffectList.size() - 1;
	}

	void PostProcessHandler::UpdateEffectData(int effectID,
	                                          void* updatedEffectData) const
	{
		m_PostProcessEffectList[effectID].Effect->UpdateEffectData(updatedEffectData);
	}

	void PostProcessHandler::RemoveEffect(int effectID)
	{
		auto postEffectFindPred = [effectID](const PostProcessEntry other) -> bool
		{
			return other.EffectID == effectID;
		};

		const auto foundEffect = std::ranges::find_if(m_PostProcessEffectList,
		                                              postEffectFindPred);

		if (foundEffect == m_PostProcessEffectList.end())
		{
			return;
		}

		m_ReservedID.push(effectID);

		std::erase(m_PostProcessEffectList, *foundEffect);
		m_PostProcessEffectList.shrink_to_fit();
	}

	ID3D11ShaderResourceView& PostProcessHandler::ProcessEffects(const Framebuffer& originalFrame) const
	{
		const auto* currentFrame = &originalFrame;

		for (int i = 0; i < m_PostProcessEffectList.size(); i++)
		{
			Renderer::StartRender(*m_PostProcessEffectList[i].Framebuffer);
			m_PostProcessEffectList[i].Frame->Draw(currentFrame->GetFrame(),
			                                       *m_PostProcessEffectList[i].Effect);
			currentFrame = m_PostProcessEffectList[i].Framebuffer;
		}

		// RenderTarget and ShaderResourceView is bound to the same texture
		return currentFrame->GetFrame();
	}

	PostProcessEntry* PostProcessHandler::GetPostProcessEffect(int effectID)
	{
		for (int i = 0; i < m_PostProcessEffectList.size(); i++)
		{
			if (m_PostProcessEffectList[i].EffectID == effectID)
			{
				return &m_PostProcessEffectList[i];
			}
		}
		return nullptr;
	}

	void PostProcessHandler::SwapEffects(int effectAID,
	                                     int effectBID)
	{
		if (effectAID == effectBID)
			return;
		
		PostProcessEntry* effectA = nullptr;
		PostProcessEntry* effectB = nullptr;
		
		for (int i = 0; i < m_PostProcessEffectList.size(); i++)
		{
			if (m_PostProcessEffectList[i].EffectID == effectAID)
			{
				effectA = &m_PostProcessEffectList[i];
			}

			if (m_PostProcessEffectList[i].EffectID == effectBID)
			{
				effectB = &m_PostProcessEffectList[i];
			}
		}

		if (effectA == nullptr || effectB == nullptr)
			return;
		
		std::swap(effectA, effectB);
	}
}
