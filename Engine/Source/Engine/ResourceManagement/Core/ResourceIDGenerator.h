#pragma once
#include <queue>

namespace Engine
{
	class ResourceIDGenerator
	{

	protected:
		std::queue<uint64_t> m_DeletedResourceID;
	};
}
