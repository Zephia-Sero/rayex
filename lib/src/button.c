#include "rayex/button.h"
#include <raylib.h>
#include <stddef.h>
#include <stdbool.h>



void UpdateButton(Button *const button)
{
	Vector2 mousePos = GetMousePosition();
	if (CheckCollisionPointRec(mousePos, button->rect)) {
		if (!button->mouseHovering) {
			button->mouseHovering = true;
			button->onHoverStart(button);
		}
	} else if (button->mouseHovering) {
		button->mouseHovering = false;
		button->onHoverEnd(button);
	}
	if (button->prevMousePos.x != mousePos.x
	 || button->prevMousePos.y != mousePos.y) {
		button->onMouseMove(button, mousePos, GetMouseDelta());
		button->prevMousePos = mousePos;
	}
	if (!button->mouseHovering)
		return;
	// 8 = max # of mouse buttons raylib supports
	for (int i = 0; i < 8; ++i) {
		if (IsMouseButtonDown(i))
			button->mouseBtnsDown |= 1 << i;
		if (IsMouseButtonUp(i))
			button->mouseBtnsUp |= 1 << i;
		if (IsMouseButtonPressed(i)) {
			button->mouseBtnsPressed |= 1 << i;
			button->onMousePressed(button, i);
		}
		if (IsMouseButtonReleased(i)) {
			button->mouseBtnsReleased |= 1 << i;
			button->onMouseReleased(button, i);
		}

	}
}

Button NewButtonPro(Rectangle const rect,
		    void (*onMousePressed)(struct Button *this, MouseButton mouseBtn),
		    void (*onMouseReleased)(struct Button *this, MouseButton mouseBtn),
		    void (*onMouseMove)(struct Button *this, Vector2 position, Vector2 delta),
		    void (*onHoverStart)(struct Button *this),
		    void (*onHoverEnd)(struct Button *this)
		   )
{
	Button btn = { 0 };
	btn.rect = rect;
#define DEFAULT_NULL(value, defaultValue) (value == NULL ? defaultValue : value)
	btn.onMousePressed = DEFAULT_NULL(onMousePressed, _EmptyButtonPressed);
	btn.onMouseReleased = DEFAULT_NULL(onMouseReleased, _EmptyButtonReleased);
	btn.onMouseMove = DEFAULT_NULL(onMouseMove, _EmptyButtonMove);
	btn.onHoverStart = DEFAULT_NULL(onHoverStart, _EmptyButtonHoverStart);
	btn.onHoverEnd = DEFAULT_NULL(onHoverEnd, _EmptyButtonHoverEnd);
	return btn;
}

void _EmptyButtonPressed(Button *const this, MouseButton const mouseBtn) {}
void _EmptyButtonReleased(Button *const this, MouseButton const mouseBtn) {}
void _EmptyButtonMove(Button *const this, Vector2 const position, Vector2 const delta) {}
void _EmptyButtonHoverStart(Button *const this) {}
void _EmptyButtonHoverEnd(Button *const this) {}
