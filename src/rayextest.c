#include "rayex/rayex.h"
#include "rayex/button.h"
#include "rayex/spritesheet.h"
#include "rayex/tilemap.h"
#include <raylib.h>
#include <stdbool.h>

typedef enum {
	MENU_TEST,
	SPRITESHEET_TEST,
	TILEMAP_TEST,
} Gamestate;

Gamestate state = MENU_TEST;

Spritesheet sheet;
Tilemap map;
int frame = 0;

void LoadTestSpritesheet(void)
{
	sheet = LoadSpritesheet("testassets/sheet0.png", 32, 32);
	SpritesheetSet(&sheet, 3, (Rectangle) {
			.x = 0,
			.y = 32,
			.width = 64,
			.height = 32
		       }
	);
}

void LoadTestTilemap(void)
{
	LoadTestSpritesheet();
	map = LoadTilemap(sheet, 5, 5, 32, 32, 0);
	for (unsigned int x = 0; x < 5; ++x) {
		for (unsigned int y = 0; y < 5; ++y) {
			int id = 2 + 3 * ((x + y) % 2 == 0);
			TilemapSet(&map, x, y, id, WHITE);
		}
	}
}

void LoadSceneMenu(Button *_button, MouseButton mouseBtn)
{
	if (mouseBtn != MOUSE_BUTTON_LEFT)
		return;
	state = MENU_TEST;
}

void UnloadSpritesheetScenes(Button *_button, MouseButton mouseBtn)
{
	if (mouseBtn != MOUSE_BUTTON_LEFT)
		return;
	state = MENU_TEST;
	UnloadSpritesheet(sheet, true);
}

void UnloadTilemapScenes(Button *_button, MouseButton mouseBtn)
{
	if (mouseBtn != MOUSE_BUTTON_LEFT)
		return;
	state = MENU_TEST;
	UnloadTilemap(map, true, true);
}

void LoadSceneSpritesheetTest(Button *_button, MouseButton mouseBtn)
{
	if (mouseBtn != MOUSE_BUTTON_LEFT)
		return;
	state = SPRITESHEET_TEST;
	LoadTestSpritesheet();
}

void LoadSceneTilemapTest(Button *_button, MouseButton mouseBtn)
{
	if (mouseBtn != MOUSE_BUTTON_LEFT)
		return;
	state = TILEMAP_TEST;
	LoadTestTilemap();
}

#define NUM_TESTS 2

typedef struct {
	Button button;
	Texture2D *background;
	Texture2D *hoverBg;
	char *text;
} TextButton;

void DrawTextButton(TextButton tbtn)
{
	if (!tbtn.button.mouseHovering)
		DrawTexture(*tbtn.background,
			    tbtn.button.rect.x,
			    tbtn.button.rect.y,
			    WHITE);
	else
		DrawTexture(*tbtn.hoverBg,
			    tbtn.button.rect.x,
			    tbtn.button.rect.y,
			    WHITE);
	DrawText(tbtn.text,
		 tbtn.button.rect.x+12, tbtn.button.rect.y+12,
		 16, BLACK);
}

void MenuFrame(TextButton *buttons)
{
	for (int i = 0; i < NUM_TESTS; ++i)
		UpdateButton(&buttons[i].button);
	BeginDrawing();
	ClearBackground(RAYWHITE);
	for (int i = 0; i < NUM_TESTS; ++i)
		DrawTextButton(buttons[i]);
	DrawFPS(0, 0);
	EndDrawing();
}

Texture2D buttonBg;
Texture2D hoverBg;

void SpritesheetTestFrame(void)
{
	TextButton backButton = {
		.button = NewButton(
				(Rectangle) { .x = 0, .y = 416, .width = buttonBg.width, .height = buttonBg.height },
				UnloadSpritesheetScenes,
				NULL
		),
		.text = "Back to menu",
		.background = &buttonBg,
		.hoverBg = &hoverBg,
	};
	UpdateButton(&backButton.button);
	if (state != SPRITESHEET_TEST)
		return;
	BeginDrawing();
	ClearBackground(RAYWHITE);

	DrawText("Red, 32x32", 			64, 48, 16, BLACK);
	DrawSpritesheet(sheet, 0, 		64, 64, WHITE);

	DrawText("White tinted purple, 32x32", 	192, 48, 16, BLACK);
	DrawSpritesheet(sheet, 1, 		192, 64, PURPLE);

	DrawText("Green, blue border, 64x32", 	64, 112, 16, BLACK);
	DrawSpritesheet(sheet, 3, 		64, 128, WHITE);

	DrawText("Full spritesheet (8x8 each, pre-scaled to 32x32)", 64, 256, 16, BLACK);
	DrawTexture(sheet._tex, 64, 272, WHITE);

	DrawTextButton(backButton);
	DrawFPS(0, 0);
	EndDrawing();
}

void TilemapTestFrame(void)
{
	TextButton backButton = {
		.button = NewButton(
				(Rectangle) { .x = 0, .y = 416, .width = buttonBg.width, .height = buttonBg.height },
				UnloadTilemapScenes,
				NULL
		),
		.text = "Back to menu",
		.background = &buttonBg,
		.hoverBg = &hoverBg,
	};
	UpdateButton(&backButton.button);
	if (state != TILEMAP_TEST)
		return;

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
	if (frame % 10 == 0) {
		for (unsigned int p = 0; p < 25; ++p) {
			Tile *tile = TilemapGet(map, p % 5, p / 5);
			TilemapSet(&map, p % 5, p / 5, tile->id, randColors[GetRandomValue(0, 7)]);
		}
	}

	Rotation rot = {
		.angle = 90. * frame * 1. / GetFPS(),
		.origin = { .x = 16, .y = 16 }
	};

	TilemapSetEx(&map, 2, 3, 3, rot, WHITE);
	BeginDrawing();
	ClearBackground(RAYWHITE);

	DrawText("5x5 disco floor!\n64x32 rotating @ 3,2", 448, 16, 16, BLACK);
	DrawTilemap(&map, 448, 64, WHITE);

	DrawTextButton(backButton);
	DrawFPS(0, 0);
	EndDrawing();
}

int main(int const argc, char const *const *const argv)
{
	InitWindow(640, 480, "RayEX Testing");
	buttonBg = LoadTexture("testassets/buttonbg.png");
	hoverBg = LoadTexture("testassets/buttonbg_hover.png");
	TextButton menuButtons[NUM_TESTS] = {
		(TextButton) {
			.button = NewButton(
				(Rectangle) { .x = 128, .y = 128, .width = buttonBg.width, .height = buttonBg.height },
				LoadSceneSpritesheetTest,
				NULL
			),
			.text = "Spritesheet\nTest",
			.background = &buttonBg,
			.hoverBg = &hoverBg,
		},
		(TextButton) {
			.button = NewButton(
				(Rectangle) { .x = 384, .y = 128, .width = buttonBg.width, .height = buttonBg.height },
				LoadSceneTilemapTest,
				NULL
			),
			.text = "Tilemap\nTest",
			.background = &buttonBg,
			.hoverBg = &hoverBg,
		},
	};

	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		++frame;
		switch(state) {
		case MENU_TEST:
			MenuFrame(menuButtons);
			break;
		case SPRITESHEET_TEST:
			SpritesheetTestFrame();
			break;
		case TILEMAP_TEST:
			TilemapTestFrame();
			break;
		}
	}
	return 0;
}
