#pragma once
#include "Engine/Core/Core.h"
#include "Engine/Math/Vector2.h"

namespace Engine
{
	struct Event
	{
		enum class Type
		{
			Key,
			Mouse
		};
	};

	enum class KeyCode
	{
		None,
		Space = 32,
		D0 = 48,
		D1 = 49,
		D2 = 50,
		D3 = 51,
		D4 = 52,
		D5 = 53,
		D6 = 54,
		D7 = 55,
		D8 = 56,
		D9 = 57,
		A = 65,
		B = 66,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z
	};

	enum class KeyState
	{
		None,
		KeyDown,
		KeyUp
	};

	inline std::string KeyStateToString(const KeyState keyState)
	{
		switch (keyState)
		{
			case KeyState::KeyDown:
				return "KeyDown";
			case KeyState::KeyUp:
				return "KeyUp";
			default:
				return "None";
		}
	}

	struct KeyEvent : Event
	{
		KeyCode KeyCode = KeyCode::None;

		KeyState KeyState    = KeyState::None; //Up, Down
		
		uint32_t RepeatCount = 0; // Not do this?
	};

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

	enum class MouseState
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

	struct MouseEvent : Event
	{
		Vector2Int MousePosition;

		Vector2Int DeltaMousePosition;

		MouseButton Button = MouseButton::None;

		MouseState State = MouseState::None;
	};
}
