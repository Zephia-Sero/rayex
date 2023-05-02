// texoff.h - Offset textures without needing to mess around with destination rectangles
#ifndef TEXOFF_H
#define TEXOFF_H
#include "rayex/rotation.h"
#include <raylib.h>
#ifdef __cplusplus
extern "C" {
#endif


typedef enum {
	_EORIGIN_NEGATIVE_Y 	= 0x8,
	_EORIGIN_1Y 		= 0x4,
	_EORIGIN_NEGATIVE_X 	= 0x2,
	_EORIGIN_1X 		= 0x1,

	EORIGIN_BOTTOM 		= _EORIGIN_1Y,
	EORIGIN_RIGHT 		= _EORIGIN_1X,
	EORIGIN_TOP 		= _EORIGIN_NEGATIVE_Y | _EORIGIN_1Y,
	EORIGIN_LEFT 		= _EORIGIN_NEGATIVE_X | _EORIGIN_1X,
	EORIGIN_MIDDLE 		= 0,

	EORIGIN_TOP_LEFT 	= EORIGIN_TOP | EORIGIN_LEFT,
	EORIGIN_TOP_RIGHT 	= EORIGIN_TOP | EORIGIN_RIGHT,
	EORIGIN_BOTTOM_LEFT 	= EORIGIN_BOTTOM | EORIGIN_LEFT,
	EORIGIN_BOTTOM_RIGHT 	= EORIGIN_BOTTOM | EORIGIN_RIGHT,

} EOrigin;


Vector2 _CalculateTextureOOffset(Vector2 const dimensions,
				 EOrigin const origin);

void DrawTextureOPro(Texture2D const tex,
		     Rectangle const source, Rectangle dest,
		     EOrigin const drawOrigin,
		     Rotation rot,
		     EOrigin const rotOrigin,
		     Color const tint);

static inline void DrawTextureORec(Texture2D const tex,
				   Rectangle const source,
				   Vector2 const position,
				   EOrigin const drawOrigin,
				   Color const tint)
{
	DrawTextureOPro(tex,
			source,
			(Rectangle) {
				.x = position.x,
				.y = position.y,
				.width = tex.width,
				.height = tex.height
			},
			drawOrigin,
			(Rotation) {
				.origin = (Vector2) { .x = 0, .y = 0 },
				.angle = 0
			},
			EORIGIN_TOP_LEFT,
			tint);
}

static inline void DrawTextureOEx(Texture2D const tex,
				  Vector2 const position,
				  EOrigin const drawOrigin,
				  Rotation const rot,
				  EOrigin const rotOrigin,
				  Color const tint)
{
	DrawTextureOPro(tex,
			(Rectangle) {
				.x = 0,
				.y = 0,
				.width = tex.width,
				.height = tex.height
			},
			(Rectangle) {
				.x = position.x,
				.y = position.y,
				.width = tex.width,
				.height = tex.height
			},
			drawOrigin,
			rot,
			rotOrigin,
			tint);
}

static inline void DrawTextureOV(Texture2D const tex,
				 Vector2 const position,
				 EOrigin const origin,
				 Color const tint)
{
	DrawTextureOPro(tex,
			(Rectangle) {
				.x = 0,
				.y = 0,
				.width = tex.width,
				.height = tex.height
			},
			(Rectangle) {
				.x = position.x,
				.y = position.y,
				.width = tex.width,
				.height = tex.height
			},
			origin,
			(Rotation) {
				.origin = (Vector2) { .x = 0, .y = 0 },
				.angle = 0
			},
			EORIGIN_TOP_LEFT,
			tint);
}

static inline void DrawTextureO(Texture2D const tex,
				int const posX, int const posY,
				EOrigin const origin,
				Color const tint)
{
	DrawTextureOPro(tex,
			(Rectangle) {
				.x = 0,
				.y = 0,
				.width = tex.width,
				.height = tex.height
			},
			(Rectangle) {
				.x = posX,
				.y = posY,
				.width = tex.width,
				.height = tex.height
			},
			origin,
			(Rotation) {
				.origin = (Vector2) { .x = 0, .y = 0 },
				.angle = 0
			},
			EORIGIN_TOP_LEFT,
			tint);
}


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
