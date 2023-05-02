// button.h - Button things!
#ifndef BUTTON_H
#define BUTTON_H
#ifdef __cplusplus
extern "C" {
#endif

#include <raylib.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum {
	ButtonStatusNone 	= 0x0,
	ButtonStatusHover 	= 0x1,
	ButtonStatusPressed 	= 0x2,
	ButtonStatusDown 	= 0x4,
	ButtonStatusReleased 	= 0x8
} EButtonStatus;

typedef struct Button {
	Rectangle rect;
	Vector2 prevMousePos;
	bool mouseHovering;
	// Bit masks for each mouse button, LSB is mouse button 0, MSB is mouse
	// button 7
	uint8_t mouseBtnsDown;
	uint8_t mouseBtnsUp;
	uint8_t mouseBtnsPressed;
	uint8_t mouseBtnsReleased;
	void (*onMousePressed)(struct Button *this, MouseButton mouseBtn);
	void (*onMouseReleased)(struct Button *this, MouseButton mouseBtn);
	void (*onMouseMove)(struct Button *this, Vector2 position, Vector2 delta);
	void (*onHoverStart)(struct Button *this);
	void (*onHoverEnd)(struct Button *this);
} Button;

void _EmptyButtonPressed(Button *const this, MouseButton const mouseBtn);
void _EmptyButtonReleased(Button *const this, MouseButton const mouseBtn);
void _EmptyButtonMove(Button *const this, Vector2 const position, Vector2 const delta);
void _EmptyButtonHoverStart(Button *const this);
void _EmptyButtonHoverEnd(Button *const this);

Button NewButtonPro(Rectangle const rect,
		    void (*onMousePressed)(struct Button *this, MouseButton mouseBtn),
		    void (*onMouseReleased)(struct Button *this, MouseButton mouseBtn),
		    void (*onMouseMove)(struct Button *this, Vector2 position, Vector2 delta),
		    void (*onHoverStart)(struct Button *this),
		    void (*onHoverEnd)(struct Button *this)
		   );

static inline Button NewButton(Rectangle const rect,
			       void (*onMousePressed)(struct Button *this, MouseButton mouseBtn),
			       void (*onMouseReleased)(struct Button *this, MouseButton mouseBtn)
			      )
{
	return NewButtonPro(rect,
			    onMousePressed, onMouseReleased,
			    _EmptyButtonMove,
			    _EmptyButtonHoverStart,
			    _EmptyButtonHoverEnd);
}

void UpdateButton(Button *const button);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
