// tilemap.h
#ifndef TILEMAP_H
#define TILEMAP_H
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif

#include <raylib.h>
#include "rayex/rotation.h"
#include "rayex/spritesheet.h"
#include "common.h"
#include <stdio.h>

typedef struct {
	int id;
	Rotation rot;
	Color tint;
} Tile;

typedef struct {
	// Spritesheet containing each tile and id
	Spritesheet _sheet;
	// Compiled texture to save on rerendering each tile.
	RenderTexture2D _rtex;
	// Tile width
	unsigned int tileWidth;
	// Tile height
	unsigned int tileHeight;
	// Width of map
	unsigned int mapWidth;
	// Height of map
	unsigned int mapHeight;
	// Tile count (mapWidth * mapHeight)
	unsigned int tileCount;
	// Tile ID list
	Tile *tiles;
	// Should _img and _tex be recomputed?
	bool _dirty;
} Tilemap;


Tilemap LoadTilemap(Spritesheet const sheet,
		    unsigned int const mapWidth, unsigned int const mapHeight,
		    unsigned int const tileWidth, unsigned int const tileHeight,
		    int const initialId);

inline void UnloadTilemap(Tilemap map, bool freeSheet, bool freeTex)
{
	UnloadRenderTexture(map._rtex);
	free(map.tiles);
	if (freeSheet)
		UnloadSpritesheet(map._sheet, freeTex);
}

int _UpdateTilemap(Tilemap *const map);


int DrawTilemapPro(Tilemap *const map,
		   Rectangle const src, Rectangle const dest,
		   Rotation const rot, Color const tint);

inline int DrawTilemapEx(Tilemap *const map,
			 Vector2 position, Rotation const rot,
			 Color const tint)
{
	return DrawTilemapPro(map,
			      (Rectangle) {
				.x = 0,
				.y = 0,
				.width = map->_rtex.texture.width,
				.height = map->_rtex.texture.height
			      },
			      (Rectangle) {
				.x = position.x + rot.origin.x,
				.y = position.y + rot.origin.y,
				.width = map->_rtex.texture.width,
				.height = map->_rtex.texture.height
			      },
			      (Rotation) {
				.angle = 0,
				.origin = { .x = 0, .y = 0 }
			      },
			      tint);
}

inline int DrawTilemap(Tilemap *const map, int const posX, int const posY,
		       Color const tint)
{
	return DrawTilemapPro(map,
			      (Rectangle) {
				.x = 0,
				.y = 0,
				.width = map->_rtex.texture.width,
				.height = map->_rtex.texture.height
			      },
			      (Rectangle) {
				.x = posX,
				.y = posY,
				.width = map->_rtex.texture.width,
				.height = map->_rtex.texture.height
			      },
			      (Rotation) {
				.angle = 0,
				.origin = { .x = 0, .y = 0 }
			      },
			      tint);
}

inline int DrawTilemapV(Tilemap *const map, Vector2 const position,
			Color const tint)
{
	return DrawTilemapPro(map,
			      (Rectangle) {
				.x = 0,
				.y = 0,
				.width = map->_rtex.texture.width,
				.height = map->_rtex.texture.height
			      },
			      (Rectangle) {
				.x = position.x,
				.y = position.y,
				.width = map->_rtex.texture.width,
				.height = map->_rtex.texture.height
			      },
			      (Rotation) {
				.angle = 0,
				.origin = { .x = 0, .y = 0 }
			      },
			      tint);
}

inline Tile *TilemapGet(Tilemap map,
			unsigned int const x, unsigned int const y)
{
	if (x >= map.mapWidth || y >= map.mapHeight)
		return NULL;
	return &map.tiles[x + y * map.mapWidth];
}

int TilemapSetEx(Tilemap *map,
		 unsigned int const x, unsigned int const y,
		 int const id, Rotation const rot, Color const tint);

int TilemapSet(Tilemap *map,
	       unsigned int const x, unsigned int const y,
	       int const id, Color const tint);



#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
