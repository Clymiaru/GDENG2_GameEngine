#pragma once

namespace Engine
{
	class ISystem
	{
	public:
		ISystem() = default;

		virtual ~ISystem() = default;

		virtual void Start() = 0;

		virtual void Close() = 0;
	};
}
