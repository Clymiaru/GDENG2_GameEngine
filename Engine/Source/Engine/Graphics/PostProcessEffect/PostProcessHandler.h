#pragma once
#include <d3d11.h>
#include <queue>

#include "PostProcessQuad.h"

#include "Engine/Core/Core.h"

namespace Engine
{
	class Framebuffer;

	struct PostProcessEntry
	{
		int EffectID = -1;
		
		PostProcessQuad* Frame = nullptr;

		Framebuffer* Framebuffer = nullptr;

		PostProcessEffect* Effect = nullptr;

		bool operator==(const PostProcessEntry& other) const
		{
			return EffectID == other.EffectID; 
		}

		bool operator!=(const PostProcessEntry& other) const
		{
			return EffectID != other.EffectID; 
		}
	};

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

		void UpdateEffectData(int effectID,
		                      void* updatedEffectData) const;

		void RemoveEffect(int effectID);

		ID3D11ShaderResourceView& ProcessEffects(const Framebuffer& originalFrame) const;

		PostProcessEntry* GetPostProcessEffect(int effectID);

		void SwapEffects(int effectAID, int effectBID);

		List<PostProcessEntry>& GetAllPostProcessEffects()
		{
			return m_PostProcessEffectList;
		}
		
		int GetPostProcessEffectCount() const
		{
			return m_PostProcessEffectList.size();
		}
	private:
		List<PostProcessEntry> m_PostProcessEffectList;
		std::queue<int> m_ReservedID;
	};
}
