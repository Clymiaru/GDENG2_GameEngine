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
		m_PostProcessQuads{List<PostProcessQuad*>()}
	{
		m_PostProcessQuads.reserve(numberOfPostProcessEffects);
		m_PostProcessFramebuffers.reserve(numberOfPostProcessEffects);
		m_PostProcessEffects.reserve(numberOfPostProcessEffects);
	}

	PostProcessHandler::~PostProcessHandler()
	{
		m_PostProcessQuads.clear();
		m_PostProcessFramebuffers.clear();
		m_PostProcessEffects.clear();
	}

	void PostProcessHandler::Start()
	{
		ShaderLibrary::Register<VertexShader>("Assets/Shaders/PostProcess/PostProcess_VS.hlsl",
		                                      "VSMain");
	}

	void PostProcessHandler::End()
	{
		m_PostProcessQuads.clear();
		m_PostProcessFramebuffers.clear();
	}

	int PostProcessHandler::AddEffect(PostProcessEffect* postProcessEffect)
	{
		m_PostProcessEffects.push_back(postProcessEffect);
		m_PostProcessQuads.push_back(new PostProcessQuad());

		FramebufferProfile postProcessFramebufferProfile;
		postProcessFramebufferProfile.Width  = Application::WindowRect().Width;
		postProcessFramebufferProfile.Height = Application::WindowRect().Height;
		m_PostProcessFramebuffers.push_back(new Framebuffer(postProcessFramebufferProfile));

		return (int)m_PostProcessEffects.size() - 1;
	}

	void PostProcessHandler::UpdateEffectData(int effectID,
	                                          void* updatedEffectData) const
	{
		m_PostProcessEffects[effectID]->UpdateEffectData(updatedEffectData);
	}

	// TODO: Implement actual removal
	void PostProcessHandler::RemoveEffect(int effectID)
	{
		PostProcessEffect* effectToRemove = m_PostProcessEffects[effectID];
		std::erase(m_PostProcessEffects, effectToRemove);
		delete effectToRemove;
	}

	ID3D11ShaderResourceView& PostProcessHandler::ProcessEffects(const Framebuffer& originalFrame) const
	{
		const auto* currentFrame = &originalFrame;

		for (int i = 0; i < m_PostProcessEffects.size(); i++)
		{
			Renderer::StartRender(*m_PostProcessFramebuffers[i]);
			m_PostProcessQuads[i]->Draw(currentFrame->GetFrame(), *m_PostProcessEffects[i]);
			currentFrame = m_PostProcessFramebuffers[i];
		}

		// RenderTarget and ShaderResourceView is bound to the same texture
		return currentFrame->GetFrame();
	}
}
