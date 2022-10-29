#include "pch.h"
#include "Primitive.h"

#include "Engine/Graphics/RenderSystem.h"
#include "Engine/Graphics/ShaderLibrary.h"

namespace Engine
{
	void Primitive::Initialize(VertexData vertexData,
	                           VertexLayoutData vertexLayoutData,
	                           IndexData indexLayoutData,
	                           const String shaderName)
	{
		m_VertexData       = std::move(&vertexData);
		m_VertexLayoutData = std::move(&vertexLayoutData);
		m_IndexData        = std::move(&indexLayoutData);
		m_VertexShader     = ShaderLibrary::GetShaderRef<VertexShader>(shaderName);
		m_PixelShader      = ShaderLibrary::GetShaderRef<PixelShader>(shaderName);
	}

	void Primitive::InitializeBuffers(size_t vertexSize,
	                                  void* constantBufferData,
	                                  size_t constantBufferDataSize)
	{
		m_VertexBuffer = CreateUniquePtr<VertexBuffer>(m_VertexData->VertexList,
		                                               vertexSize,
		                                               m_VertexData->VertexListCount,
		                                               m_VertexShader->GetByteCodeData(),
		                                               static_cast<uint32_t>(m_VertexShader->GetByteCodeSizeData()),
		                                               m_VertexLayoutData->VertexLayout,
		                                               m_VertexLayoutData->VertexLayoutCount);

		m_IndexBuffer = CreateUniquePtr<IndexBuffer>(m_IndexData->IndexList,
		                                             m_IndexData->IndexListCount);

		m_ConstantBuffer = CreateUniquePtr<ConstantBuffer>(constantBufferData, constantBufferDataSize);
	}

	void Primitive::Draw(const void* newConstantData)
	{
		RenderSystem::GetDeviceContext().UpdateConstantBuffer(*m_ConstantBuffer, newConstantData);

		RenderSystem::Draw(*m_VertexShader, *m_PixelShader,
		                   *m_VertexBuffer, *m_IndexBuffer,
		                   *m_ConstantBuffer, nullptr,
		                   D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	void Primitive::Terminate() const
	{
		m_VertexBuffer->Release();
		m_IndexBuffer->Release();
	}

	Primitive::Primitive() :
		m_VertexData{nullptr},
		m_VertexLayoutData{nullptr},
		m_IndexData{nullptr},
		m_VertexShader{nullptr},
		m_PixelShader{nullptr},
		m_VertexBuffer{nullptr},
		m_IndexBuffer{nullptr},
		m_ConstantBuffer{nullptr}
	{
	}

	Primitive::~Primitive() = default;

	VertexBuffer& Primitive::GetVertexBuffer() const
	{
		return *m_VertexBuffer;
	}

	IndexBuffer& Primitive::GetIndexBuffer() const
	{
		return *m_IndexBuffer;
	}
}
