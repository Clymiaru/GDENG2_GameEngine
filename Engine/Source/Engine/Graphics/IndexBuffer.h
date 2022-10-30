#pragma once
#include <d3d11.h>

#include "Buffer.h"

#include "Engine/Core/Core.h"
#include "Engine/Math/Math.h"

namespace Engine
{
 	class Renderer;
 	class DeviceContext;

 	class IndexBuffer final : public Buffer
 	{
 	public:
 		IndexBuffer(const uint32_t* indexList,
 		            uint32_t indexListCount);

 		~IndexBuffer() override;

 	private:
 		friend class DeviceContext;
 	};
 }
