#pragma once

#include <glm\vec2.hpp>
#include <glm\vec3.hpp>


namespace OpenSFMLEngine
{
	class Actor2D
	{
	private:
		glm::vec2 m_position;

	public:
		Actor2D();
		virtual ~Actor2D();
	};
}
