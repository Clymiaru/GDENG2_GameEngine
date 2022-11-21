#pragma once
#include "Material.h"

#include "Engine/ResourceManagement/Core/Resource.h"

namespace Engine
{
	struct DiffuseTextureMaterial : public Material
	{
		SharedPtr<TextureResource> DiffuseTexture;
	};
}

