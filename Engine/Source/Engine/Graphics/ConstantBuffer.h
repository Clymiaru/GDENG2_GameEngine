#pragma once
#include "Buffer.h"

namespace Engine
{
	class DeviceContext;

	class ConstantBuffer final : public Buffer
	{
	public:
		explicit ConstantBuffer(const void* buffer,
		                        size_t bufferSize);

		~ConstantBuffer() override;

		void Update(const DeviceContext& deviceContext,
		            const void* updatedBufferData) const;

		ConstantBuffer(const ConstantBuffer&) = delete;

		ConstantBuffer& operator=(const ConstantBuffer&) = delete;

		ConstantBuffer(Buffer&&) noexcept = delete;

		ConstantBuffer& operator=(ConstantBuffer&&) = delete;

	private:
		friend class Renderer;

		friend class DeviceContext;
	};
}
