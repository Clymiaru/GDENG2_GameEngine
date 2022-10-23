#include "pch.h"
#include "Camera.h"

#include "Engine/Core/Window.h"

Engine::Camera& Engine::Camera::Instance()
{
	static Camera instance;
	return instance;
}

void Engine::Camera::Translate(const Vector3& amount)
{
	m_Position += amount;
}

DirectX::XMMATRIX Engine::Camera::ViewProjMatrix()
{
	// To be transferred to camera later
	using namespace DirectX;
	m_ViewMatrix = XMMatrixIdentity();

	

	m_ViewMatrix += XMMatrixTranslation(m_Position.X(), m_Position.Y(), m_Position.Z());
	m_ViewMatrix = XMMatrixTranspose(m_ViewMatrix);

	m_ProjMatrix = XMMatrixIdentity();
	auto winSize = Application::WindowRef().GetSize();
	m_ProjMatrix *= XMMatrixPerspectiveLH(winSize.X(), winSize.Y(), 0.001f, 1000.0f);
	m_ProjMatrix = XMMatrixTranspose(m_ProjMatrix);

	return m_ViewMatrix * m_ProjMatrix;
}
