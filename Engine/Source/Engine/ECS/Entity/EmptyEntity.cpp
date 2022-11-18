#include "pch.h"
#include "EmptyEntity.h"

namespace Engine
{
	EmptyEntity::EmptyEntity(const EntityID id,
	                         const StringView name,
	                         ComponentRegistry* componentRegistry) :
		Entity{id, name, componentRegistry} {}
	
	EmptyEntity::~EmptyEntity() = default;
}
