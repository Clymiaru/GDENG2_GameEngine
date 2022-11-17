#include "pch.h"
#include "UIIDGenerator.h"

namespace Engine
{
	UIIDGenerator::UIIDGenerator() :
		m_ReservedUIIDList{},
		m_CurrentUIIDToGenerate{1} {}
	
	UIIDGenerator::~UIIDGenerator() = default;
	
	UIID UIIDGenerator::GenerateUIID()
	{
		UIID generatedUIID;

		if (!m_ReservedUIIDList.empty())
		{
			generatedUIID = m_ReservedUIIDList.front();

			auto reservedListIter = std::ranges::remove(m_ReservedUIIDList, generatedUIID);
			m_ReservedUIIDList.erase(reservedListIter.begin(), reservedListIter.end());
			m_ReservedUIIDList.shrink_to_fit();
			
			return generatedUIID;
		}

		if (m_CurrentUIIDToGenerate == std::numeric_limits<UIID>::max())
		{
			generatedUIID = 0;
		}
		else
		{
			generatedUIID = m_CurrentUIIDToGenerate;
			++m_CurrentUIIDToGenerate;
		}

		return generatedUIID;
	}

	// Don't reserve an ID of 0 as it is used as error detection if all UIID has been used!
	void UIIDGenerator::AddReservedUIID(UIID idToReserve)
	{
		if (idToReserve == 0)
			return;

		if (const auto foundID = std::ranges::find(m_ReservedUIIDList, idToReserve);
			foundID != m_ReservedUIIDList.end())
		{
			return; // Attempting to reserve an existing ID will do nothing.
		}
		
		m_ReservedUIIDList.emplace_back(idToReserve);
	}
}
