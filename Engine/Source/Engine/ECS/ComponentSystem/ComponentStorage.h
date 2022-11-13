#pragma once

namespace Engine
{
	template <typename EntityID, typename ComponentType>
	class ComponentStorage
	{
	public:
		ComponentStorage();

	private:
		List<ComponentType*> m_ComponentList;
		HashMap<EntityID, ComponentType*> m_ComponentMap;
	};
}
