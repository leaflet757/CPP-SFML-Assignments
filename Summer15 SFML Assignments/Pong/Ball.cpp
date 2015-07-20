#include "Ball.h"


Ball::Ball()
{
	m_position.x = 0;
	m_position.y = 0;

	m_scale.x = 0.05;
	m_scale.y = 0.05;
	m_scale.z = 1;

	m_velocity.x = 0.5;
	m_velocity.y = 0;
	m_velocity.z = 0;

	float interval = 2 * 3.14159 / 36;
	for (int i = 0; i < 36; i++)
	{
		m_verts.push_back(glm::vec3(cos(i*interval), sin(i*interval), 1.0f));
	}
}


Ball::~Ball()
{
}

void Ball::update()
{

	// TODO: get window dimensions from game or window or somethign
}