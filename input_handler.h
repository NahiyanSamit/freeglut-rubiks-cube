#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <GL/glut.h>
#include "cube.h"
#include "camera.h"

// Input state variables
extern bool mouseDown;
extern int lastMouseX, lastMouseY;

extern LayerAnimation currentAnimation;

// Input handling functions
void handleMouse(int button, int state, int x, int y);
void handleMouseMotion(int x, int y);
void handleKeyboard(unsigned char key, int x, int y);

// Cube manipulation functions
void resetCube();
void printControls();

// Animation functions
void updateLayerAnimation();
void startLayerAnimation(point3f origin, int axis, bool clockwise);
bool isAnimating();


#endif
