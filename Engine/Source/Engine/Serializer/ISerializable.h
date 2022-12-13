#pragma once

namespace Engine
{
	class ISerializable
	{
	public:
		virtual std::string Serialize() = 0;
	};
}
