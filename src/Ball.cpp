#include "Ball.hpp"



Ball::Ball(float x, float y, float radius)
    : m_x(x), m_y(y), m_radius(radius), m_speedX(0), m_speedY(0)
{
}

Vector2 Ball::GetVector()
{
	return {m_x, m_y};
}

void Ball::Draw() const
{
	DrawCircle(m_x, m_y, m_radius, ORANGE);
}

void Ball::SetSpeed(float speedX, float speedY)
{
	m_speedX = speedX;
	m_speedY = speedY;
}

float Ball::GetY() const
{
	return m_y;
}

float Ball::Getradius()
{
	return m_radius;
}

void Ball::Update(int& PlayerScore, int& CPUScore)
{
	m_x += m_speedX;
	m_y += m_speedY;

	if (m_x + m_radius >= GetScreenWidth())
	{
		CPUScore++;
		Reset();
	}

	if (m_x + m_radius <= 0)
	{
		PlayerScore++;
		Reset();
	}

	if (m_y + m_radius >= GetScreenHeight() || m_y - m_radius <= 0)
		m_speedY *= -1;
}

void Ball::CheckCollision(const Rectangle& rectangle)
{
	if (CheckCollisionCircleRec({m_x, m_y}, m_radius, rectangle))
		m_speedX *= -1;
}

void Ball::Reset()
{
	m_x = GetScreenWidth() / 2.0f;
	m_y = GetScreenHeight() / 2.0f;

	int RandSpeed[2] = {1, -1};
	m_speedX *= RandSpeed[GetRandomValue(0, 1)];
	m_speedX *= RandSpeed[GetRandomValue(0, 1)];
}
