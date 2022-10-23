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

		virtual void OnMouseMove(const Vector2& deltaMousePosition) = 0;
		virtual void OnLeftMouseButtonDown(const Vector2& mousePosition) = 0;
		virtual void OnLeftMouseButtonUp(const Vector2& mousePosition) = 0;

		virtual void OnRightMouseButtonDown(const Vector2& mousePosition) = 0;
		virtual void OnRightMouseButtonUp(const Vector2& mousePosition) = 0;
	};
}
