#pragma once
#include "Primitive.h"

namespace Engine
{
	struct Constant;

	class Cube : public Primitive
	{
	public:
		Cube(const Vector3& position,
		     const Vector3& size,
		     const std::wstring& shaderName);

		~Cube() override;

		void Update(float deltaTime);

		void Render() const;

	private:
		void InitializeBuffers() override;

		std::pair<Vertex*, size_t> CreateVertices() override;

		std::pair<D3D11_INPUT_ELEMENT_DESC*, size_t> CreateVertexLayout() override;

		std::pair<Uint*, size_t> CreateIndices() override;

		Vector3 m_Position;

		Vector3 m_Scale;

		DirectX::XMMATRIX m_TransformMatrix;

		Constant* m_Constant;
	};
}
