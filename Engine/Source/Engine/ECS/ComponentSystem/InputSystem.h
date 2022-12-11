#pragma once
#include "Engine/Input/InputData.h"

namespace Engine
{
	class InputSystem
	{
	public:
		InputSystem() = default;
		~InputSystem() = default;
		
		void ProcessInput(const InputData& inputData);
	};
}
