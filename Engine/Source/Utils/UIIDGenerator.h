#pragma once

namespace Engine
{
	using UIID = uint64_t;
	
	class UIIDGenerator final
	{
	public:
		UIIDGenerator();
		~UIIDGenerator();
		
		// Check if the output is 0. As a 0 ID means Entity creation failed due to reaching max EntityID count.
		UIID GenerateUIID();
		void AddReservedUIID(UIID idToReserve);
	private:
		std::vector<UIID> m_ReservedUIIDList{};
		UIID m_CurrentUIIDToGenerate;
	};
}

