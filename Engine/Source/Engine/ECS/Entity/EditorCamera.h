#pragma once
#include "Engine/Math/Math.h"

#include "Engine/ECS/Core/Entity.h"
#include "Engine/ECS/Component/TransformComponent.h"

namespace Engine
{
	class EditorCamera final : public Entity
	{
	public:
		explicit EditorCamera(EntityID id,
						StringView name,
						ComponentRegistry* componentRegistry,
						uint64_t renderWidth,
						uint64_t renderHeight);

		~EditorCamera() override;
	};
}
