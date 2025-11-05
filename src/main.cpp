#include "Ball.hpp"
#include "Paddle.hpp"


int PlayerScore = 0;
int CPUScore = 0;

Color LightGreen = Color{129, 204, 184, 255};
Color Green = Color{38, 185, 154, 255};
Color DarkGreen = Color{20, 160, 133, 255};



int main()
{

	constexpr int screenWidth = 1080;
	constexpr int screenHeight = 720;

	InitWindow(screenWidth, screenHeight, "Game");
	SetTargetFPS(60);

	Ball ball(screenWidth / 2.0f, screenHeight / 2.0f, 13.0f);
	ball.SetSpeed(8.0f, 6.0f);

	Paddle player(20.0f, 120.0f, 8.0f, GetScreenWidth() - 25.0f - 10, GetScreenHeight() / 2.0f - 120.0f / 2.0f);
	CpuPaddle cpu(20.0f, 120.0f, 6.5, 10, screenHeight / 2.0f - 120 / 2.0f);

	while (!WindowShouldClose())
	{
		ClearBackground(DarkGreen);

		// update
		ball.Update(PlayerScore, CPUScore);
		player.Update();
		cpu.Update(ball.GetY());

		ball.CheckCollision(player.Position());
		ball.CheckCollision(cpu.Position());

		// Draw
		BeginDrawing();

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
