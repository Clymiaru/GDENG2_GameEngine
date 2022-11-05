#pragma once

#define MAKE_COMPONENT(component)     static const char* GetStaticName() { return #component; }               \
									  String GetName() const override { return #component; }

namespace Engine
{
	class Entity;

	class AComponent
	{
	public:
		// TODO: Decide to switch to UUID?
		explicit AComponent(Entity& owner);

		virtual ~AComponent();

		Entity& GetOwner() const;

		virtual String GetName() const = 0;

		bool operator==(const AComponent& other) const;

		bool operator!=(const AComponent& other) const;

		AComponent(const AComponent&) = delete;
	
		AComponent& operator=(const AComponent&) = delete;
	
		AComponent(AComponent&&) noexcept = delete;
	
		AComponent& operator=(AComponent&&) noexcept = delete;

	protected:
		Entity& m_EntityRef;
	};
}
