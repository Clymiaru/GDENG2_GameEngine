#pragma once

namespace Engine
{
	class Camera
	{
	public:
		~Camera() = default;
		static Camera& Instance();

		void Translate(const Vector3& amount);

		DirectX::XMMATRIX ViewProjMatrix();
		
	private:
		Camera() = default;
		DirectX::XMMATRIX m_ViewMatrix;
		DirectX::XMMATRIX m_ProjMatrix;
		Vector3 m_Position = Vector3::Zero;
	};
}
