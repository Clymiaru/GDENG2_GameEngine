#pragma once
#include "Buffer.h"

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
