#include "rayex/rayex.h"
#include "rayex/spritesheet.h"
#include <raylib.h>
#include <stdbool.h>



int main(int const argc, char const *const *const argv)
{
	InitWindow(640, 480, "RayEX Testing");
	Spritesheet sheet = LoadSpritesheet("testassets/sheet0.png", 32, 32);
	SpritesheetSet(&sheet, 3, (Rectangle) {
			.x = 0,
			.y = 32,
			.width = 64,
			.height = 32
		       }
	);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);

		DrawText("Red, 32x32", 			64, 48, 16, BLACK);
		DrawSpritesheet(sheet, 0, 		64, 64, WHITE);

		DrawText("White tinted purple, 32x32", 	192, 48, 16, BLACK);
		DrawSpritesheet(sheet, 1, 		192, 64, PURPLE);

		DrawText("Green, blue border, 64x32", 	64, 112, 16, BLACK);
		DrawSpritesheet(sheet, 3, 		64, 128, WHITE);

		DrawText("Checkered floor,\n5x5 * 32x32", 448, 48, 16, BLACK);
		for (int x = 0; x < 5; ++x) {
			for (int y = 0; y < 5; ++y) {
				int id = 2 + 3 * ((x + y) % 2 == 0);
				DrawSpritesheet(sheet, id, 448 + x * 32, 64 + y * 32, WHITE);
			}
		}

		DrawText("Full spritesheet (8x8 each, pre-scaled to 32x32)", 64, 256, 16, BLACK);
		DrawTexture(sheet._tex, 64, 272, WHITE);

		EndDrawing();
	}
	UnloadSpritesheet(sheet, true);

	return 0;
}
