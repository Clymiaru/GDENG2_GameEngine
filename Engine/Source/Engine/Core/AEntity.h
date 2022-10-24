#pragma once

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

		DirectX::XMMATRIX& Transform();
	private:
		String m_Name;
		Vector3 m_Position;
		Vector3 m_Scale;
		Vector3 m_Rotation;
		DirectX::XMMATRIX m_Transform;
	};

}
