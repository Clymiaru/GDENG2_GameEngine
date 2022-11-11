#pragma once

namespace Engine
{
	template <typename ObjectID, typename Object>
	class ListMapStorage final
	{
	public:
		explicit ListMapStorage(size_t expectedAmount);
		~ListMapStorage();

		void Add(Object toAdd);
		void Remove(ObjectID toRemove);
		
	private:
		List<Object> m_List;
		HashMap<ObjectID, Object*> m_Map;
	};
}
