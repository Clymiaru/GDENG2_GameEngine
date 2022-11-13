#pragma once
#include "Engine/Core/Core.h"
#include <functional>

#define MAKE_EVENT_TYPE(eventType)	static Type GetStaticType() { return Type::eventType; }\
									Type GetType() const override { return Type::eventType; }\
									const char* GetName() const { return #eventType; }

namespace Engine
{
	class Event
	{
	public:
		enum class Type
		{
			None,
			WindowClose, WindowResize, WindowFocus, WindowUnfocus,
			// KeyPressed, KeyReleased,
			// MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
		};

		Event() = default;
		virtual ~Event() = default;

		bool IsHandled = false;

		[[nodiscard]]
		virtual Type GetType() const = 0;

		[[nodiscard]]
		virtual const char* GetName() const = 0;
	};

	class WindowCloseEvent final : public Event
	{
	public:
		WindowCloseEvent() = default;
		~WindowCloseEvent() override = default;
		
		MAKE_EVENT_TYPE(WindowClose)
	};

	class WindowResizeEvent final : public Event
	{
	public:
		WindowResizeEvent(const unsigned int width, const unsigned int height) :
			Width{width},
			Height{height} {}

		~WindowResizeEvent() override = default;

		MAKE_EVENT_TYPE(WindowResize)

		unsigned int Width;
		unsigned int Height;
	};

	class WindowFocusEvent final : public Event
	{
	public:
		WindowFocusEvent() = default;
		~WindowFocusEvent() override = default;
		
		MAKE_EVENT_TYPE(WindowFocus)
	};

	class WindowUnfocusEvent final : public Event
	{
	public:
		WindowUnfocusEvent() = default;
		~WindowUnfocusEvent() override = default;
		
		MAKE_EVENT_TYPE(WindowUnfocus)
	};
}
