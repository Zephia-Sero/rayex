#include <raylib.h>
#include "rayex/rotation.h"
#include "rayex/spritesheet.h"
#include "rayex/tilemap.h"
#include "rayex/texmode.h"
#include <stdio.h>

Tilemap LoadTilemap(Spritesheet const sheet,
		    unsigned int const mapWidth, unsigned int const mapHeight,
		    unsigned int const tileWidth, unsigned int const tileHeight,
		    int const initialId)
{
	Tilemap map = {
		._sheet = sheet,
		.mapWidth = mapWidth,
		.mapHeight = mapHeight,
		.tileWidth = tileWidth,
		.tileHeight = tileHeight,
		.tileCount = mapWidth * mapHeight,
		._rtex = LoadRenderTexture(mapWidth * tileWidth, mapHeight * tileHeight),
		._dirty = true,
	};
	map.tiles = malloc(sizeof(Tile) * map.tileCount);
	if (map.tiles == NULL)
		return map;

	for (unsigned int i = 0; i < map.tileCount; ++i) {
		map.tiles[i] = (Tile) {
			.id = initialId,
			.tint = WHITE,
			.rot = (Rotation) {
				.angle = 0,
				.origin = (Vector2) {
					.x = 0,
					.y = 0
				}
			}
		};
	}

	return map;
}

int _UpdateTilemap(Tilemap *const map)
{
	int failure = 0;
	if (map->_dirty) {
		PushTextureMode(map->_rtex);
		ClearBackground((Color) { 0 });
		for (unsigned int x = 0; x < map->mapWidth; ++x) {
			for (unsigned int y = 0; y < map->mapHeight; ++y) {
				Tile tile = map->tiles[x + y * map->mapWidth];
				failure |= DrawSpritesheetEx(map->_sheet,
							     tile.id,
							     (Vector2) {
								.x = x * map->tileWidth,
								.y = y * map->tileHeight
							     },
							     tile.rot,
							     tile.tint);
				if (failure)
					fprintf(stderr,
						"Unknown tile ID %d @ (%u, %u)\n",
						tile.id, x, y);
			}
		}
		PopTextureMode();
		map->_dirty = false;
	}

	// Check WaitTime in raylib to see why this doesn't sleep and is just
	// a busy loop.
	while (!IsRenderTextureReady(map->_rtex));

	return failure;
}

int DrawTilemapPro(Tilemap *const map,
		   Rectangle src, Rectangle dest,
		   Rotation const rot, Color const tint)
{
	int failure = _UpdateTilemap(map);
	// account for OpenGL stuff
	src.height = -src.height;
	dest.x += rot.origin.x;
	dest.y += rot.origin.y;
	DrawTexturePro(map->_rtex.texture, src, dest, rot.origin, rot.angle, tint);
	return failure;
}

int TilemapSetEx(Tilemap *map,
		 unsigned int const x, unsigned int const y,
		 int const id, Rotation const rot, Color const tint)
{
	Tile *tile = TilemapGet(*map, x, y);
	if (tile == NULL)
		return 1;

	tile->id = id;
	tile->rot = rot;
	tile->tint = tint;
	map->_dirty = true;
	return 0;
}

int TilemapSet(Tilemap *map,
		      unsigned int const x, unsigned int const y,
		      int const id, Color const tint)
{
	Tile *tile = TilemapGet(*map, x, y);
	if (tile == NULL)
		return 1;

	tile->id = id;
	tile->tint = tint;
	map->_dirty = true;
	return 0;
}
