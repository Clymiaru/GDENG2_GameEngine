#pragma once
#include "Engine/ECS/Core/Entity.h"

namespace Engine
{
	class EmptyEntity final : public Entity
	{
	public:
		explicit EmptyEntity(EntityID id,
		                     StringView name,
		                     ComponentRegistry* componentRegistry);
		~EmptyEntity() override;
	};
}
