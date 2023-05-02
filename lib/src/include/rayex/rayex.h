// rayex.h - Global rayex header (includes all other rayex headers)
#ifndef RAYEX_H
#define RAYEX_H
#ifdef __cplusplus
extern "C" {
#endif

#include "button.h"
#include "common.h"
#include "rotation.h"
#include "spritesheet.h"
#include "texmode.h"
#include "texoff.h"
#include "tilemap.h"


inline void RayexCleanup(void)
{
	RayexCleanupTextureMode();
}

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
