#pragma once
#include <d3d11.h>

#include "Engine/Core/Core.h"

namespace Engine
{
	class PostProcessEffect;
	class Framebuffer;
	class PostProcessQuad;
	class PostProcessHandler
	{
	public:
		explicit PostProcessHandler(int numberOfPostProcessEffects);
		~PostProcessHandler();

		void Start();
		void End();

		// Return an Id so that whenever an object wants to update
		// They can update a particular post process effect's data 
		int AddEffect(PostProcessEffect* postProcessEffect);

		void UpdateEffectData(int effectID, void* updatedEffectData) const;

		void RemoveEffect(int effectID);

		ID3D11ShaderResourceView& ProcessEffects(const Framebuffer& originalFrame) const;
	private:
		List<PostProcessQuad*> m_PostProcessQuads;
		List<Framebuffer*> m_PostProcessFramebuffers;
		List<PostProcessEffect*> m_PostProcessEffects;
	};
}
