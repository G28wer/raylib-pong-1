#include <raylib.h>

int PlayerScore = 0;
int CPUScore = 0;

Color LightGreen = Color{129, 204, 184, 255};
Color Green = Color{38, 185, 154, 255};
Color DarkGreen = Color{20, 160, 133, 255};

class Ball
{
  private:
	float m_x, m_y;
	float m_speedX, m_speedY;
	float m_radius;

  public:
	Ball(float x, float y, float radius)
	    : m_x(x), m_y(y), m_radius(radius), m_speedX(0), m_speedY(0)
	{
	}

	Vector2 GetVector()
	{
		return {m_x, m_y};
	}

	void Draw() const
	{
		DrawCircle(m_x, m_y, m_radius, ORANGE);
	}

	void SetSpeed(float speedX, float speedY)
	{
		m_speedX = speedX;
		m_speedY = speedY;
	}

	float GetY() const
	{
		return m_y;
	}

	float Getradius()
	{
		return m_radius;
	}

	void Update()
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

	void CheckCollision(const Rectangle& rectangle)
	{
		if (CheckCollisionCircleRec({m_x, m_y}, m_radius, rectangle))
			m_speedX *= -1;
	}

	void Reset()
	{
		m_x = GetScreenWidth() / 2.0f;
		m_y = GetScreenHeight() / 2.0f;

		int RandSpeed[2] = {1, -1};
		m_speedX *= RandSpeed[GetRandomValue(0, 1)];
		m_speedX *= RandSpeed[GetRandomValue(0, 1)];
	}
};

class Paddle
{
  protected:
	float m_x, m_y;
	float m_speed;
	float m_width, m_height;

	void MovmentLimit()
	{
		if (m_y < 0)
			m_y = 0;
		if (m_y + m_height > GetScreenHeight())
			m_y = GetScreenHeight() - m_height;
	}

  public:
	Paddle(float width, float height, float speed, float x, float y)
	    : m_width(width), m_height(height), m_speed(speed), m_x(x), m_y(y)
	{
		// m_x = GetScreenWidth() - width - 10;
		// m_y = GetScreenHeight() / 2.0f - height / 2.0f;
	}

	void Draw() const
	{
		DrawRectangleRounded({m_x, m_y, m_width, m_height}, 0.8, 0, ORANGE);
		// DrawRectangle(m_x, m_y, m_width, m_height, ORANGE);
	}

	void Update()
	{
		if (IsKeyDown(KEY_UP))
			m_y -= m_speed;
		if (IsKeyDown(KEY_DOWN))
			m_y += m_speed;

		MovmentLimit();
	}

	Rectangle Position()
	{
		return {m_x, m_y, m_width, m_height};
	}
};

class CpuPaddle : public Paddle
{
  public:
	CpuPaddle(float width, float height, float speed, float x, float y) : Paddle(width, height, speed, x, y)
	{
	}

	void Update(float ballY)
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
};

int main()
{

	constexpr int screenWidth = 1080;
	constexpr int screenHeight = 720;

	InitWindow(screenWidth, screenHeight, "Game");
	SetTargetFPS(60);

	Ball ball(screenWidth / 2.0f, screenHeight / 2.0f, 15.0f);
	ball.SetSpeed(8.0f, 8.0f);

	Paddle player(20.0f, 120.0f, 8.0f, GetScreenWidth() - 25.0f - 10, GetScreenHeight() / 2.0f - 120.0f / 2.0f);
	CpuPaddle cpu(20.0f, 120.0f, 6.5, 10, screenHeight / 2.0f - 120 / 2.0f);

	while (!WindowShouldClose())
	{
		ball.Update();
		player.Update();
		cpu.Update(ball.GetY());

		ball.CheckCollision(player.Position());
		ball.CheckCollision(cpu.Position());

		BeginDrawing();
		ClearBackground(DarkGreen);
		DrawRectangle(screenWidth / 2, 0, screenWidth / 2, screenHeight, Green);
		DrawCircle(screenWidth / 2, screenHeight / 2, 200, LightGreen);
		DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
		ball.Draw();
		player.Draw();
		cpu.Draw();
		DrawText(TextFormat("%i", CPUScore), screenWidth / 4.0f - 20, 20, 80, WHITE);
		DrawText(TextFormat("%i", PlayerScore), 3 * screenWidth / 4.0f - 20, 20, 80, WHITE);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
