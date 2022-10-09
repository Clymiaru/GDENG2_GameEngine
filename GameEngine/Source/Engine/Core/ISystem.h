#pragma once

namespace Engine
{
	class ISystem
	{
	public:
		ISystem() = default;
		virtual ~ISystem() = default;

		virtual auto Start() -> void = 0;
		virtual auto Close() -> void = 0;
	};
}