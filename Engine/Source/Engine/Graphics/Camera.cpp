#include "pch.h"
#include "Camera.h"

#include "Engine/Core/Window.h"

Engine::Camera& Engine::Camera::Instance()
{
	static Camera instance;
	return instance;
}

void Engine::Camera::Translate(const Vector3Float& amount)
{
	m_Position += amount;
}

void Engine::Camera::Position(const Vector3Float& position)
{
	m_Position = position;
}

Engine::Matrix4 Engine::Camera::ViewProjMatrix()
{
	// To be transferred to camera later
	using namespace DirectX;
	m_ViewMatrix = Matrix4();
	m_ViewMatrix *= Matrix4::CreateTranslation(m_Position);
	m_ViewMatrix = m_ViewMatrix.Transpose();

	m_ProjMatrix = Matrix4();
	m_ProjMatrix *= Matrix4::CreatePerspective(1280, 1080, 0.001f, 1000.0f);
	//m_ProjMatrix *= XMMatrixOrthographicLH(winSize.X(), winSize.Y(), -1000.0f, 1000.0f);
	//m_ProjMatrix *= XMMatrixOrthographicLH(1280, 1080, 0.001f, 1000.0f);
	//auto winSize = Application::WindowRef().GetSize();
	//m_ProjMatrix *= XMMatrixOrthographicLH(winSize.X(), winSize.Y(), 0.001f, 1000.0f);
	m_ProjMatrix = m_ProjMatrix.Transpose();

	return m_ViewMatrix * m_ProjMatrix;
}
