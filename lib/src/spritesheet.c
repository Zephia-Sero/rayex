#include "rayex/rayex.h"
Spritesheet LoadSpritesheetTex(Texture2D const tex,
			       unsigned int const entryWidth,
			       unsigned int const entryHeight)
{
	Spritesheet ret;
	ret._tex = tex;
	int sswidth = ret._tex.width / entryWidth;
	int ssheight = ret._tex.height / entryHeight;
	ret.numEntries = sswidth * ssheight;
	ret._alloced = ret.numEntries;
	ret.entries = (SpritesheetEntry *) malloc(sizeof(SpritesheetEntry) * ret._alloced);
	if (ret.entries == NULL)
		return ret;

	for (int y = 0; y < ssheight; ++y) {
		for (int x = 0; x < sswidth; ++x) {
			int id = x + y * sswidth;
			ret.entries[id] = (SpritesheetEntry) {
				.id = id,
				.src = {
					.x = (float) x * entryWidth,
					.y = (float) y * entryHeight,
					.width = (float) entryWidth,
					.height = (float) entryHeight
				}
			};
		}
	}

	return ret;
}

int SpritesheetSet(Spritesheet *const sheet, int const id, Rectangle newSrc)
{
	for (size_t i = 0; i < sheet->numEntries; ++i) {
		if (sheet->entries[i].id == id) {
			sheet->entries[i].src = newSrc;
			return 0;
		}
	}
	if (sheet->_alloced <= sheet->numEntries)
		sheet->entries = (SpritesheetEntry *) realloc(sheet->entries, sheet->_alloced *= 2);

	if (sheet->entries == NULL)
		return 1;

	sheet->entries[sheet->numEntries++] = (SpritesheetEntry) {
		.id = id,
		.src = newSrc
	};

	return 0;
}

int DrawSpritesheetPro(Spritesheet const sheet, int const id,
		       Rectangle dest, Rotation rot, Color tint)
{
	for (size_t i = 0; i < sheet.numEntries; ++i) {
		SpritesheetEntry entry = sheet.entries[i];
		if (entry.id == id) {
			if (dest.width == -1)
				dest.width = entry.src.width;
			if (dest.height == -1)
				dest.height = entry.src.height;
			dest.x += rot.origin.x;
			dest.y += rot.origin.y;
			DrawTexturePro(sheet._tex, entry.src, dest, rot.origin, rot.angle, tint);
			return 0;
		}
	}
	return 1;
}
