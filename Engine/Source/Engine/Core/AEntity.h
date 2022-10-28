#pragma once

#include "Core.h"

#include "Engine/Math/Matrix4.h"
#include "Engine/Math/Vector3.h"
namespace Engine
{
	class AEntity
	{
	public:
		explicit AEntity(const String& name);
		virtual ~AEntity();

		virtual void Update(float deltaTime);
		virtual void Draw();

		void Position(const Vector3& newPosition);
		Vector3& Position();

		void Scale(const Vector3& newScale);
		Vector3& Scale();

		void Rotation(const Vector3& newRotation);
		Vector3& Rotation();

		Matrix4& Transform();
	private:
		String m_Name;
		Vector3 m_Position;
		Vector3 m_Scale;
		Vector3 m_Rotation;
		Matrix4 m_Transform;
	};

}
