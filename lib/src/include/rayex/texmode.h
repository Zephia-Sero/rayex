// texmode.h - Additional TextureMode functions
#ifndef TEXMODE_H
#define TEXMODE_H
#ifdef __cplusplus
extern "C" {
#endif

#include <raylib.h>

// Begin drawing to render texture, maintaining the previous state in a stack.
void PushTextureMode(RenderTexture2D target);

// Ends drawing to render texture, going back to the previous one. Returns the
// old value for cleanup purposes.
RenderTexture2D PopTextureMode(void);

// Ends drawing to render texture, going back to the previous one. Cleans up
// the value popped!
static inline void CleanPopTextureMode(void)
{
	UnloadRenderTexture(PopTextureMode());
}

// Clean up all texture modes. NOTE: This does not unload the render textures!
void RayexCleanupTextureMode(void);

struct TextureModeStack {
	RenderTexture2D entry;
	struct TextureModeStack *previous;
};

extern struct TextureModeStack *_rayexTexModeStack;

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
