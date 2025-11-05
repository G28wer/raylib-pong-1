#pragma once

#include <raylib.h>


class Paddle
{
  protected:
	float m_x, m_y;
	float m_speed;
	float m_width, m_height;

	void MovmentLimit();

  public:
	Paddle(float width, float height, float speed, float x, float y);

	void Draw() const;

	void Update();

	Rectangle Position();
};

class CpuPaddle : public Paddle
{
  public:
	CpuPaddle(float width, float height, float speed, float x, float y);

	void Update(float ballY);

};
