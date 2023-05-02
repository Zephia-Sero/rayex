#include <raylib.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include "rayex/texmode.h"

struct TextureModeStack *_rayexTexModeStack = NULL;

// Begin drawing to render texture, maintaining the previous state in a stack.
void PushTextureMode(RenderTexture2D target)
{
	struct TextureModeStack *prev = _rayexTexModeStack;
	_rayexTexModeStack = malloc(sizeof(struct TextureModeStack));
	assert (_rayexTexModeStack != NULL);
	_rayexTexModeStack->entry = target;
	_rayexTexModeStack->previous = prev;
	BeginTextureMode(target);
}

// Ends drawing to render texture, going back to the previous one. Returns the
// old value for cleanup purposes.
RenderTexture2D PopTextureMode(void)
{
	assert (_rayexTexModeStack != NULL);
	struct TextureModeStack *prev = _rayexTexModeStack->previous;
	RenderTexture2D poppedValue = _rayexTexModeStack->entry;
	free(_rayexTexModeStack);
	_rayexTexModeStack = prev;

	EndTextureMode();
	if (prev != NULL)
		BeginTextureMode(_rayexTexModeStack->entry);

	return poppedValue;
}

void RayexCleanupTextureMode(void)
{
	while (_rayexTexModeStack != NULL) {
		struct TextureModeStack *prev = _rayexTexModeStack->previous;
		free(_rayexTexModeStack);
		_rayexTexModeStack = prev;
	}
}
