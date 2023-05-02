#include "rayex/texoff.h"

Vector2 _CalculateTextureOOffset(Vector2 const dimensions,
				 EOrigin const origin)
{
#define BOOLIFY(n) (!!(n))
	int const halfWidth = dimensions.x / 2;
	int const halfHeight = dimensions.y / 2;
							  // Converts `{ 0,  1}`
							  //       to `{ 1, -1}`
							  // vvvvvvvv
	int const xSign 	= BOOLIFY(origin & _EORIGIN_NEGATIVE_X) * -2 + 1;
	int const ySign 	= BOOLIFY(origin & _EORIGIN_NEGATIVE_Y) * -2 + 1;
	int const isXOffset 	= BOOLIFY(origin & _EORIGIN_1X);
	int const isYOffset 	= BOOLIFY(origin & _EORIGIN_1Y);
	// `1 +` to add an extra halfWidth and halfHeight, to account for the
	// images drawing from the top left and not the middle normally.
	return (Vector2) {
		.x = (1 + xSign * isXOffset) * halfWidth,
		.y = (1 + ySign * isYOffset) * halfHeight
	};
#undef BOOLIFY
}


void DrawTextureOPro(Texture2D const tex,
		     Rectangle const source, Rectangle dest,
		     EOrigin const drawOrigin,
		     Rotation rot,
		     EOrigin const rotOrigin,
		     Color const tint)
{
	Vector2 const dimensions = (Vector2) {
		.x = dest.width,
		.y = dest.height
	};
	Vector2 const drawOffset = _CalculateTextureOOffset(dimensions, drawOrigin);
	Vector2 const rotOffset = _CalculateTextureOOffset(dimensions, rotOrigin);
	dest.x += drawOffset.x;
	dest.y += drawOffset.y;
	rot.origin.x += rotOffset.x;
	rot.origin.y += rotOffset.y;
	DrawTexturePro(tex, source, dest, rot.origin, rot.angle, tint);
}
