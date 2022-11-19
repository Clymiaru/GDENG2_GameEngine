#pragma once
#include "Engine/ECS/Core/Entity.h"

namespace Engine
{
	class RenderEntity final : public Entity
	{
	public:
		explicit RenderEntity(EntityID id,
		                      StringView name,
		                      ComponentRegistry* componentRegistry);

		~RenderEntity() override;
	};
}
