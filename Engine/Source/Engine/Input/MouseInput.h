#pragma once
#include "Engine/Math/Math.h"

namespace Engine
{
	enum class MouseButton
	{
		None,
		LeftButton = 0x01,
		RightButton = 0x02,
		MiddleButton = 0x04
	};

	inline std::string MouseButtonToString(const MouseButton button)
	{
		switch (button)
		{
			case MouseButton::LeftButton:
				return "LeftButton";
			case MouseButton::RightButton:
				return "RightButton";
			case MouseButton::MiddleButton:
				return "MiddleButton";
			default:
				return "None";
		}
	}

	enum class	MouseState
	{
		None,
		ButtonPressed,
		ButtonReleased,
		Moved
	};
	
	inline std::string MouseStateToString(const MouseState state)
	{
		switch (state)
		{
			case MouseState::ButtonPressed:
				return "ButtonPressed";
			case MouseState::ButtonReleased:
				return "ButtonReleased";
			case MouseState::Moved:
				return "Moved";
			default:
				return "None";
		}
	}
	
	struct MouseInput
	{
		Vector2Int MousePosition;
		Vector2Int DeltaMousePosition;
		MouseButton Button = MouseButton::None;
		MouseState State = MouseState::None;
	};
}
