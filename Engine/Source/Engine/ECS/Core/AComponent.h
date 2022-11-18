#pragma once

#define MAKE_COMPONENT(component)     static const char* GetStaticName() { return #component; }               \
									  String GetName() const override { return #component; }

namespace Engine
{
	class Entity;
	class AComponent
	{
	public:
		explicit AComponent(Entity& owner);
		virtual ~AComponent();

		[[nodiscard]]
		Entity& GetOwner() const;

		[[nodiscard]]
		virtual String GetName() const = 0;

		bool operator==(const AComponent& other) const;
		bool operator!=(const AComponent& other) const;

		AComponent(const AComponent&) = delete;
		AComponent& operator=(const AComponent&) = delete;
		AComponent(AComponent&&) noexcept = delete;
		AComponent& operator=(AComponent&&) noexcept = delete;

	private:
		Entity& m_EntityRef;
	};
}
