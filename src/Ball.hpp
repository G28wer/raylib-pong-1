#pragma once

#include <raylib.h>

class Ball
{
  private:
	float m_x, m_y;
	float m_speedX, m_speedY;
	float m_radius;

  public:
	Ball(float x, float y, float radius);

	Vector2 GetVector();

	void Draw() const;

	void SetSpeed(float speedX, float speedY);

	float GetY() const;

	float Getradius();

	void Update(int& PlayerScore, int& CPUScore);

	void CheckCollision(const Rectangle& rectangle);

	void Reset();
};
