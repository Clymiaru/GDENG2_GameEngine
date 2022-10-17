#include "pch.h"
#include "AEntity.h"

Engine::AEntity::AEntity(const String& name) :
	m_Name{name},
	m_Position{Vector3::Zero},
	m_Scale{Vector3::One},
	m_Rotation{Vector3::Zero}
{
}

Engine::AEntity::~AEntity() = default;

void Engine::AEntity::Update(float deltaTime)
{
}

void Engine::AEntity::Draw()
{
}

void Engine::AEntity::Position(const Vector3& newPosition)
{
	m_Position = newPosition;
}

Engine::Vector3& Engine::AEntity::Position()
{
	return m_Position;
}

void Engine::AEntity::Scale(const Vector3& newScale)
{
	m_Scale = newScale;
}

Engine::Vector3& Engine::AEntity::Scale()
{
	return m_Scale;
}

void Engine::AEntity::Rotation(const Vector3& newRotation)
{
	m_Rotation = newRotation;
}

Engine::Vector3& Engine::AEntity::Rotation()
{
	return m_Rotation;
}

DirectX::XMMATRIX& Engine::AEntity::Transform()
{
	using namespace DirectX;
	m_Transform = XMMatrixIdentity();
	m_Transform *= XMMatrixRotationAxis(Vector3::Forward,
	                                    XMConvertToRadians(m_Rotation.Z()));
	m_Transform *= XMMatrixRotationAxis(Vector3::Up,
	                                    XMConvertToRadians(m_Rotation.Y()));
	m_Transform *= XMMatrixRotationAxis(Vector3::Right,
	                                    XMConvertToRadians(m_Rotation.X()));
	
	m_Transform *= XMMatrixScaling(m_Scale.X(),
	                               m_Scale.Y(),
	                               m_Scale.Z());
	m_Transform *= XMMatrixTranslation(m_Position.X(),
	                                   m_Position.Y(),
	                                   m_Position.Z());
	
	m_Transform = XMMatrixTranspose(m_Transform);
	return m_Transform;
}
