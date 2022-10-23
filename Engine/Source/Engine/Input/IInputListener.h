#pragma once

namespace Engine
{
	//TODO: Redesign with polling events in mind
	enum class InputType
	{
		None,
		Keyboard,
		Mouse,
		Count
	};

	enum class MouseButton
	{
		
	};
	
	class IInputListener
	{
	public:
		IInputListener() = default;
		virtual ~IInputListener() = default;

		virtual void OnKeyDown(int keyCode) = 0;
		virtual void OnKeyUp(int keyCode) = 0;

		virtual void OnMouseMove(const Vector2& deltaMousePos) = 0;
		virtual void OnMouseButtonDown();
		virtual void OnMouseButtonUp();
	};
}
