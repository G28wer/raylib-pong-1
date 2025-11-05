#include "Paddle.hpp"

void Paddle::MovmentLimit()
{
	if (m_y < 0)
		m_y = 0;
	if (m_y + m_height > GetScreenHeight())
		m_y = GetScreenHeight() - m_height;
}

Paddle::Paddle(float width, float height, float speed, float x, float y)
    : m_width(width), m_height(height), m_speed(speed), m_x(x), m_y(y)
{
}

void Paddle::Draw() const
{
	DrawRectangleRounded({m_x, m_y, m_width, m_height}, 0.8, 0, ORANGE);
}

void Paddle::Update()
{
	if (IsKeyDown(KEY_UP))
		m_y -= m_speed;
	if (IsKeyDown(KEY_DOWN))
		m_y += m_speed;

	MovmentLimit();
}

Rectangle Paddle::Position()
{
	return {m_x, m_y, m_width, m_height};
}

CpuPaddle::CpuPaddle(float width, float height, float speed, float x, float y) : Paddle(width, height, speed, x, y)
{
}

void CpuPaddle::Update(float ballY)
{
	if (m_y + m_height > ballY)
	{
		m_y -= m_speed;
	}
	if (m_y + m_height <= ballY)
	{
		m_y += m_speed;
	}
	MovmentLimit();
}
