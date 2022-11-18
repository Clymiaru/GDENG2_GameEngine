#pragma once

namespace Engine
{
	class RenderSystem final
	{
	public:
		RenderSystem() = default;
		~RenderSystem() = default;
		
		void Render() const;
	};
}

