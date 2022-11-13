#pragma once
#include "Engine/Core/Core.h"

namespace Engine
{
	class AUIScreen
	{
	public:
		explicit AUIScreen(StringView name);
		virtual ~AUIScreen() = default;

		void Draw();

		AUIScreen(const AUIScreen&) = delete;
		AUIScreen& operator=(const AUIScreen&) = delete;
		AUIScreen(AUIScreen&&) noexcept = delete;
		AUIScreen& operator=(AUIScreen&&) noexcept = delete;
	protected:
		std::string m_Name;

	private:
		virtual void DrawImpl() = 0;
	};
}
