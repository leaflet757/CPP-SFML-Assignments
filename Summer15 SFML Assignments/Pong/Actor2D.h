#pragma once

#include <vector>
#include <glm\vec2.hpp>
#include <glm\vec3.hpp>

namespace OpenSFMLEngine
{
	class Actor2D
	{
	protected:
		glm::vec3 m_position;
		glm::vec3 m_scale;

		glm::vec3 m_velocity;

		std::vector<glm::vec3> m_verts;

	public:
		Actor2D();
		virtual ~Actor2D();

		virtual void update();

		std::vector<glm::vec3> getVerts() const;
		glm::vec3 getPosition() const;
		glm::vec3 getVelocity() const;
		glm::vec3 getScale() const;

		void setPosition(float x, float y, float z);
	};
}
