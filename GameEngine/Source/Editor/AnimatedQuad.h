#pragma once

#include "Engine/Graphics/RenderObjects/RenderObject.h"
#include "Engine/Utils/Color32.h"

namespace Engine
{
	struct Constant;

	class ConstantBuffer;
}

namespace Editor
{
	class AnimatedQuad final : public Engine::RenderObject
	{
	public:
		AnimatedQuad(const Engine::Vector3Float& v0_start,
		             const Engine::Vector3Float& v0_end,
		             const Engine::Vector3Float& v1_start,
		             const Engine::Vector3Float& v1_end,
		             const Engine::Vector3Float& v2_start,
		             const Engine::Vector3Float& v2_end,
		             const Engine::Vector3Float& v3_start,
		             const Engine::Vector3Float& v3_end,
		             const Engine::Color32& v0_color_start,
		             const Engine::Color32& v0_color_end,
		             const Engine::Color32& v1_color_start,
		             const Engine::Color32& v1_color_end,
		             const Engine::Color32& v2_color_start,
		             const Engine::Color32& v2_color_end,
		             const Engine::Color32& v3_color_start,
		             const Engine::Color32& v3_color_end);

		~AnimatedQuad();

		auto Update(float deltaTime) -> void;

		auto Render() const -> void;

	private:
		Engine::UniquePtr<Engine::ConstantBuffer> m_ConstantBuffer;

		DirectX::XMMATRIX m_TransformMatrix;

		Engine::Constant* m_Constant;

		Engine::Vector3Float m_V0Start;

		Engine::Vector3Float m_V0End;

		Engine::Vector3Float m_V1Start;

		Engine::Vector3Float m_V1End;

		Engine::Vector3Float m_V2Start;

		Engine::Vector3Float m_V2End;

		Engine::Vector3Float m_V3Start;

		Engine::Vector3Float m_V3End;

		Engine::Color32 m_V0ColorStart;

		Engine::Color32 m_V0ColorEnd;

		Engine::Color32 m_V1ColorStart;

		Engine::Color32 m_V1ColorEnd;

		Engine::Color32 m_V2ColorStart;

		Engine::Color32 m_V2ColorEnd;

		Engine::Color32 m_V3ColorStart;

		Engine::Color32 m_V3ColorEnd;

		auto SetBuffers() -> void;

		auto InitializeVertexData() -> VertexData override;

		auto InitializeVertexLayout() -> VertexLayoutData override;

		auto InitializeIndexData() -> IndexData override;

		auto InitializeShaderData() -> void override;
	};
}
