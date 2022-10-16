#include "pch.h"
#include "Primitive.h"

#include "Engine/Graphics/ShaderLibrary.h"

namespace Engine
{
	void Primitive::InitializeImpl(VertexData vertexData,
	                               VertexLayoutData vertexLayoutData,
	                               IndexData indexLayoutData,
	                               const std::wstring shaderName)
	{
		m_VertexData       = std::move(&vertexData);
		m_VertexLayoutData = std::move(&vertexLayoutData);
		m_IndexData        = std::move(&indexLayoutData);
		m_VertexShader     = ShaderLibrary::GetShaderRef<VertexShader>(shaderName);
		m_PixelShader      = ShaderLibrary::GetShaderRef<PixelShader>(shaderName);
		InitializeBuffers();
	}

	void Primitive::TerminateImpl() const
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
