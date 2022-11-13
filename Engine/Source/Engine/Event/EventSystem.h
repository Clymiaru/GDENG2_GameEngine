#pragma once
#include "Event.h"

namespace Engine
{
	class EventSystem
	{
	public:
		void Init();
		void Terminate();
	
		// Window polls the events that the EventSystem adds these events to the eventQueue

		// ProcessEvents();
	
		// Register(); 
		// Deregister();
		private:
		List<Event> m_EventList;
	};

}
