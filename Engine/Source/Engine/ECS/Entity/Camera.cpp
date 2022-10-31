#include "pch.h"
#include "Camera.h"

#include "Engine/Core/Window.h"

namespace Engine
{
	Camera::Camera() :
		Entity{L"Camera"}
	{
	}

	Matrix4 Camera::ViewProjMatrix()
	{
		using namespace DirectX;
		Matrix4 viewMatrix = Matrix4();
		// m_ViewMatrix *= Matrix4::CreateTranslation(m_Position);
		// m_ViewMatrix = m_ViewMatrix.Transpose();

		m_ProjMatrix = Matrix4();
		m_ProjMatrix *= Matrix4::CreatePerspective(1280, 1080, 0.001f, 1000.0f);
		//m_ProjMatrix *= XMMatrixOrthographicLH(winSize.X(), winSize.Y(), -1000.0f, 1000.0f);
		//m_ProjMatrix *= XMMatrixOrthographicLH(1280, 1080, 0.001f, 1000.0f);
		//auto winSize = Application::WindowRef().GetSize();
		//m_ProjMatrix *= XMMatrixOrthographicLH(winSize.X(), winSize.Y(), 0.001f, 1000.0f);
		m_ProjMatrix = m_ProjMatrix.Transpose();

		return viewMatrix * m_ProjMatrix;
	}
}
