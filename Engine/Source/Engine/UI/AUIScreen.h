#pragma once
#include "Engine/Core/Core.h"

namespace Engine
{
	using ScreenID = uint64_t;
	class AUIScreen
	{
	public:
		explicit AUIScreen(ScreenID id, StringView name);
		virtual ~AUIScreen() = default;

		[[nodiscard]]
		ScreenID GetID() const;

		[[nodiscard]]
		const char* GetNameAndIDLabel() const;

		void Draw();

		AUIScreen(const AUIScreen&) = delete;
		AUIScreen& operator=(const AUIScreen&) = delete;
		AUIScreen(AUIScreen&&) noexcept = delete;
		AUIScreen& operator=(AUIScreen&&) noexcept = delete;
	protected:
		ScreenID m_ID;
		std::string m_Name;
		std::string m_NameIDLabel;
		bool m_IsOpen = false;

	private:
		virtual void DrawImpl() = 0;
	};
}
