#pragma once

namespace Engine
{
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
	
	struct KeyboardInput
	{
		KeyCode KeyCode = KeyCode::None;
		KeyState KeyState    = KeyState::None; //Up, Down
		uint32_t RepeatCount = 0; // Not do this?
	};
}
