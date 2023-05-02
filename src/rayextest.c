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

	Tilemap map = LoadTilemap(sheet, 5, 5, 32, 32, 0);
	for (unsigned int x = 0; x < 5; ++x) {
		for (unsigned int y = 0; y < 5; ++y) {
			int id = 2 + 3 * ((x + y) % 2 == 0);
			TilemapSet(&map, x, y, id, WHITE);
		}
	}

	Rotation rot = {
		.angle = 0,
		.origin = { .x = 16, .y = 16 }
	};

	SetTargetFPS(60);

#define CYAN CLITERAL(Color) { .r = ORANGE.b, .g = YELLOW.r, .b = YELLOW.r, .a = 255 }
	Color randColors[8] = {
		RED,
		ORANGE,
		YELLOW,
		GREEN,
		CYAN,
		BLUE,
		MAGENTA,
		PURPLE,
	};

	int frame = 0;

	while (!WindowShouldClose()) {
		if (frame++ % 10 == 0) {
			for (unsigned int p = 0; p < 25; ++p) {
				Tile *tile = TilemapGet(map, p % 5, p / 5);
				TilemapSet(&map, p % 5, p / 5, tile->id, randColors[GetRandomValue(0, 7)]);
			}
		}
		rot.angle += 90 * GetFrameTime();
		TilemapSetEx(&map, 2, 3, 3, rot, WHITE);

		BeginDrawing();
		ClearBackground(RAYWHITE);


		DrawText("Red, 32x32", 			64, 48, 16, BLACK);
		DrawSpritesheet(sheet, 0, 		64, 64, WHITE);

		DrawText("White tinted purple, 32x32", 	192, 48, 16, BLACK);
		DrawSpritesheet(sheet, 1, 		192, 64, PURPLE);

		DrawText("Green, blue border, 64x32", 	64, 112, 16, BLACK);
		DrawSpritesheet(sheet, 3, 		64, 128, WHITE);

		DrawText("5x5 disco floor!\n64x32 rotating @ 3,2", 448, 16, 16, BLACK);
		DrawTilemap(&map, 448, 64, WHITE);

		DrawText("Full spritesheet (8x8 each, pre-scaled to 32x32)", 64, 256, 16, BLACK);
		DrawTexture(sheet._tex, 64, 272, WHITE);

		DrawFPS(0, 0);
		EndDrawing();
	}
	UnloadSpritesheet(sheet, true);

	return 0;
}
