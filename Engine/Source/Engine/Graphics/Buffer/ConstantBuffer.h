#pragma once
#include "Buffer.h"

namespace Engine
{
	class RenderDevice;
	class RenderContext;

	class ConstantBuffer final : public Buffer
	{
	public:
		explicit ConstantBuffer(ID3D11Device& deviceRef,
						const void* bufferData,
						size_t bufferSize);

		void Update(ID3D11DeviceContext& deviceContext,
					const void* updatedBufferData) const;

		~ConstantBuffer() override;
		
		ConstantBuffer(const ConstantBuffer&) = delete;
		ConstantBuffer& operator=(const ConstantBuffer&) = delete;
		ConstantBuffer(Buffer&&) noexcept = delete;
		ConstantBuffer& operator=(ConstantBuffer&&) = delete;
		
	private:
		friend class Renderer;

		friend class RenderDevice;
		friend class RenderContext;
	};
}
