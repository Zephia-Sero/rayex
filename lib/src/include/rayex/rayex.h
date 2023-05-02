// rayex.h - Global rayex header (includes all other rayex headers)
#ifndef RAYEX_H
#define RAYEX_H
#ifdef __cplusplus
extern "C" {
#endif

#include "rotation.h"
#include "tilemap.h"
#include "spritesheet.h"
#include "texmode.h"


inline void RayexCleanup(void)
{
	RayexCleanupTextureMode();
}

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
