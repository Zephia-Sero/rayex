// rotation.h - Rotation information
#ifndef ROTATION_H
#define ROTATION_H
#ifdef __cplusplus
extern "C" {
#endif

#include <raylib.h>
typedef struct {
	Vector2 origin;
	float angle;
} Rotation;

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
