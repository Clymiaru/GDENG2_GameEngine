#pragma once
#include <d3d11.h>

#include "Buffer.h"

namespace Engine
{
	class DeviceContext;

	class ConstantBuffer final : public Buffer
	{
	public:
		ConstantBuffer(const void* buffer,
		               size_t bufferSize,
		               Renderer* renderer);

		~ConstantBuffer() override;

		void Release() override;

	private:
		friend class DeviceContext;
	};
}
