#pragma once

namespace Engine
{
	class CameraSystem final
	{
	public:
		CameraSystem() = default;
		~CameraSystem() = default;
		
		void CameraUpdate() const;
	};
}
