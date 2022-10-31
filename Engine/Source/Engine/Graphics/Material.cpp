#include "pch.h"
#include "Material.h"

Engine::Material::Material(const String& shader)
{
	
}

Engine::Material::~Material()
{
}

Engine::VertexShader& Engine::Material::GetVertexShader()
{
	return *m_VertexShader;
}

Engine::PixelShader& Engine::Material::GetPixelShader()
{
	return *m_PixelShader;
}
