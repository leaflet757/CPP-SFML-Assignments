#include "Actor2D.h"

namespace OpenSFMLEngine
{
	Actor2D::Actor2D()
	{
		m_scale.x = 1;
		m_scale.y = 1;
		m_scale.z = 1;
	}


	Actor2D::~Actor2D()
	{
	}

	void Actor2D::update()
	{
	}

	std::vector<glm::vec3> Actor2D::getVerts() const
	{
		return m_verts;
	}

	glm::vec3 Actor2D::getPosition() const
	{
		return m_position;
	}

	glm::vec3 Actor2D::getScale() const
	{
		return m_scale;
	}

	glm::vec3 Actor2D::getVelocity() const
	{
		return m_velocity;
	}

	void Actor2D::setPosition(float x, float y, float z)
	{
		m_position.x = x;
		m_position.y = y;
		m_position.z = z;
	}
}