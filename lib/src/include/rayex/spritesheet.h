// spritesheet.h - Spritesheet header
#ifndef SPRITESHEET_H
#define SPRITESHEET_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdlib.h>
#include <raylib.h>
#include "rotation.h"
#include "common.h"

typedef struct {
	int id;
	Rectangle src;
} SpritesheetEntry;

typedef struct {
	Texture2D _tex;
	size_t _alloced;
	size_t numEntries;
	SpritesheetEntry *entries;
} Spritesheet;


Spritesheet LoadSpritesheetTex(Texture2D const tex,
			       unsigned int const entryWidth,
			       unsigned int const entryHeight);

// Load a uniform (constant dimensions for each entry) spritesheet from file.
inline Spritesheet LoadSpritesheet(char const *const fileName,
				     unsigned int const entryWidth,
				     unsigned int const entryHeight)
{
	return LoadSpritesheetTex(LoadTexture(fileName),
				  entryWidth, entryHeight);
}

// Change or add spritesheet entries.
// Returns 0 on success, 1 on failure.
int SpritesheetSet(Spritesheet *const sheet, int const id, Rectangle newSrc);

// Unload spritesheet entries list from RAM, and unload texture from VRAM
// if `unloadTex` is true.
inline void UnloadSpritesheet(Spritesheet sheet, bool unloadTex)
{
	free(sheet.entries);
	if (unloadTex)
		UnloadTexture(sheet._tex);
}

// Draw an entry of a spritesheet with pro parameters.
// Returns 0 on success, 1 on failure.
int DrawSpritesheetPro(Spritesheet const sheet, int const id,
		       Rectangle dest, Rotation rot, Color tint);

// Draw an entry of a spritesheet with extended parameters.
// Returns 0 on success, 1 on failure.
inline int DrawSpritesheetEx(Spritesheet const sheet, int const id,
			     Vector2 const position, Rotation const rot,
			     Color const tint)
{
	return DrawSpritesheetPro(sheet, id,
				  (Rectangle) { .x = position.x, .y = position.y,
						.width = -1, .height = -1 },
				  rot, tint);
}
// Draw an entry of a spritesheet with position defined as Vector2.
// Returns 0 on success, 1 on failure.
inline int DrawSpritesheetV(Spritesheet const sheet, int const id,
			   Vector2 const position,
			   Color const tint)
{
	return DrawSpritesheetPro(sheet, id,
				  (Rectangle) { .x = position.x, .y = position.y,
						.width = -1, .height = -1 },
				  (Rotation) {
					.origin = { .x = 0, .y = 0 },
					.angle = 0},
				  tint);
}

// Draw an entry of a spritesheet.
// Returns 0 on success, 1 on failure.
inline int DrawSpritesheet(Spritesheet const sheet, int const id,
			   float const x, float const y,
			   Color const tint)
{
	return DrawSpritesheetPro(sheet, id,
				  (Rectangle) { .x = x, .y = y,
						.width = -1, .height = -1 },
				  (Rotation) {
					.origin = { .x = 0, .y = 0 },
					.angle = 0},
				  tint);
}



#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
