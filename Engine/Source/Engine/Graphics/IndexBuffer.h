#pragma once
#include "Buffer.h"
#include "RenderData.h"

namespace Engine
{
 	class DeviceContext;

 	class IndexBuffer final : public Buffer
 	{
 	public:
 		explicit IndexBuffer(const RenderData& renderDataRef);

 		~IndexBuffer() override;

 		IndexBuffer(const IndexBuffer&) = delete;

 		IndexBuffer& operator=(const IndexBuffer&) = delete;

 		IndexBuffer(IndexBuffer&&) noexcept = delete;

 		IndexBuffer& operator=(IndexBuffer&&) noexcept = delete;

 	private:
 		friend class DeviceContext;
 	};
 }
