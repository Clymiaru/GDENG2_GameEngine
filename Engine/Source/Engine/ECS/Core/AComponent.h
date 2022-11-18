#pragma once

#define MAKE_COMPONENT(component)     static const char* GetStaticName() { return #component; }               \
									  String GetName() const override { return #component; }

namespace Engine
{
	using EntityID = uint64_t;
	class AComponent
	{
	public:
		explicit AComponent(const EntityID& ownerID);
		virtual ~AComponent();

		[[nodiscard]]
		const EntityID& GetOwnerID() const;

		[[nodiscard]]
		EntityID GetOwnerID();

		[[nodiscard]]
		virtual String GetName() const = 0;

		bool operator==(const AComponent& other) const;
		bool operator!=(const AComponent& other) const;

		AComponent(const AComponent&) = delete;
		AComponent& operator=(const AComponent&) = delete;
		AComponent(AComponent&&) noexcept = delete;
		AComponent& operator=(AComponent&&) noexcept = delete;

	private:
		EntityID m_OwnerID;
	};
}
