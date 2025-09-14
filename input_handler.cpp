#include "input_handler.h"
#include <iostream>
#include <cmath>
#include <cctype>

using namespace std;

// Global input state variables
bool mouseDown = false;
int lastMouseX = 0, lastMouseY = 0;
bool isRotating = false;
float rotationSpeed = 1.0f;
LayerAnimation currentAnimation;

void handleMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            mouseDown = true;
            lastMouseX = x;
            lastMouseY = y;
        } else {
            mouseDown = false;
        }
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        // Right click to reset camera
        resetCube();
        glutPostRedisplay();
    }
    
    // Mouse wheel for zooming
    if (button == 3 && state == GLUT_DOWN) { // Wheel up
        if (camera) {
            camera->zoom(-0.5f);
            glutPostRedisplay();
        }
    } else if (button == 4 && state == GLUT_DOWN) { // Wheel down
        if (camera) {
            camera->zoom(0.5f);
            glutPostRedisplay();
        }
    }
}

void handleMouseMotion(int x, int y) {
    if (mouseDown && camera) {
        float deltaX = (x - lastMouseX);
        float deltaY = (y - lastMouseY);
        
        // Orbit camera around the cube
        float sensitivity = 0.5f;
        camera->orbit(deltaX * sensitivity, deltaY * sensitivity);
        
        lastMouseX = x;
        lastMouseY = y;
        
        glutPostRedisplay();
    }
}

void handleKeyboard(unsigned char key, int x, int y) {
    // Check if Shift is pressed for counter-clockwise rotation
    int modifiers = glutGetModifiers();
    bool shiftPressed = (modifiers & GLUT_ACTIVE_SHIFT) != 0;
    bool clockwise = !shiftPressed; // Regular key = clockwise, Shift+key = counter-clockwise
    
    // Convert to lowercase for consistent handling
    unsigned char lowerKey = tolower(key);
    
    switch (lowerKey) {
        case 27: // Escape key
            cout << "Exiting Rubik's Cube..." << endl;
            delete rubiksCube;
            exit(0);
            break;
            
        case 'r':
            resetCube();
            cout << "Camera and cube reset!" << endl;
            glutPostRedisplay();
            break;
            
        case 'h':
            printControls();
            break;
            
        // Layer rotations - Y-axis (horizontal layers)
        case 'u': // Up/Top layer
            if (rubiksCube && !currentAnimation.active) {
                startLayerAnimation(rubiksCube->topOrigin, 1, clockwise);
                cout << "Rotating top layer " << (clockwise ? "clockwise" : "counter-clockwise") << endl;
            }
            break;
            
        case 'm': // Middle horizontal layer
            if (rubiksCube && !currentAnimation.active) {
                startLayerAnimation(rubiksCube->middleOrigin, 1, clockwise);
                cout << "Rotating middle horizontal layer " << (clockwise ? "clockwise" : "counter-clockwise") << endl;
            }
            break;
            
        case 'd': // Down/Bottom layer
            if (rubiksCube && !currentAnimation.active) {
                startLayerAnimation(rubiksCube->bottomOrigin, 1, clockwise);
                cout << "Rotating bottom layer " << (clockwise ? "clockwise" : "counter-clockwise") << endl;
            }
            break;
            
        // Layer rotations - X-axis (vertical layers)
        case 'l': // Left layer
            if (rubiksCube && !currentAnimation.active) {
                startLayerAnimation(rubiksCube->leftOrigin, 0, clockwise);
                cout << "Rotating left layer " << (clockwise ? "clockwise" : "counter-clockwise") << endl;
            }
            break;
            
        case 'c': // Center vertical layer
            if (rubiksCube && !currentAnimation.active) {
                startLayerAnimation(rubiksCube->centerOrigin, 0, clockwise);
                cout << "Rotating center vertical layer " << (clockwise ? "clockwise" : "counter-clockwise") << endl;
            }
            break;
            
        case 'x': // Right layer (using 'x' since 'r' is reset)
            if (rubiksCube && !currentAnimation.active) {
                startLayerAnimation(rubiksCube->rightOrigin, 0, clockwise);
                cout << "Rotating right layer " << (clockwise ? "clockwise" : "counter-clockwise") << endl;
            }
            break;
            
        // Layer rotations - Z-axis (front/back layers)
        case 'f': // Front layer
            if (rubiksCube && !currentAnimation.active) {
                startLayerAnimation(rubiksCube->frontOrigin, 2, clockwise);
                cout << "Rotating front layer " << (clockwise ? "clockwise" : "counter-clockwise") << endl;
            }
            break;
            
        case 'b': // Back layer
            if (rubiksCube && !currentAnimation.active) {
                startLayerAnimation(rubiksCube->backOrigin, 2, clockwise);
                cout << "Rotating back layer " << (clockwise ? "clockwise" : "counter-clockwise") << endl;
            }
            break;
    }
}


// Cube manipulation functions
void resetCube() {
    if (camera) {
        camera->reset();
    }
    if (rubiksCube) {
        rubiksCube->resetCube();
    }
}

void printControls() {
    cout << "\n=== Rubik's Cube Controls (Updated) ===" << endl;
    cout << "Mouse:" << endl;
    cout << "  Left click + drag: Orbit camera around cube" << endl;
    cout << "  Mouse wheel: Zoom in/out" << endl;
    cout << "  Right click: Reset camera and cube" << endl;
    cout << "\nGeneral:" << endl;
    cout << "  R: Reset camera and cube" << endl;
    cout << "  H: Show this help" << endl;
    cout << "  ESC: Exit program" << endl;
    cout << "\nLayer Rotations:" << endl;
    cout << "  Key alone = Clockwise rotation" << endl;
    cout << "  Shift + Key = Counter-clockwise rotation" << endl;
    cout << "\nHorizontal Layers (Y-axis):" << endl;
    cout << "  U: Top/Up layer" << endl;
    cout << "  M: Middle horizontal layer" << endl;
    cout << "  D: Down/Bottom layer" << endl;
    cout << "\nVertical Layers (X-axis):" << endl;
    cout << "  L: Left layer" << endl;
    cout << "  C: Center vertical layer" << endl;
    cout << "  X: Right layer" << endl;
    cout << "\nDepth Layers (Z-axis):" << endl;
    cout << "  F: Front layer" << endl;
    cout << "  B: Back layer" << endl;
    cout << "\nExamples:" << endl;
    cout << "  U = Top layer clockwise" << endl;
    cout << "  Shift+U = Top layer counter-clockwise" << endl;
    cout << "  F = Front layer clockwise" << endl;
    cout << "  Shift+F = Front layer counter-clockwise" << endl;
    cout << "==========================================\n" << endl;
}

// Animation functions
void updateLayerAnimation() {
    if (currentAnimation.active) {
        currentAnimation.currentAngle += currentAnimation.speed;
        
        if (currentAnimation.currentAngle >= currentAnimation.targetAngle) {
            // Animation complete - apply final rotation to cube state
            currentAnimation.currentAngle = currentAnimation.targetAngle;
            currentAnimation.active = false;
            
            // Apply the rotation to the actual cube data
            if (rubiksCube) {
                rubiksCube->rotateLayer(currentAnimation.origin, currentAnimation.axis, currentAnimation.clockwise);
            }
            
            cout << "Animation complete!" << endl;
        }
        
        // Request redraw
        glutPostRedisplay();
    }
}

void startLayerAnimation(point3f origin, int axis, bool clockwise) {
    if (!currentAnimation.active) {
        currentAnimation.active = true;
        currentAnimation.origin = origin;
        currentAnimation.axis = axis;
        currentAnimation.clockwise = clockwise;
        currentAnimation.currentAngle = 0;
        currentAnimation.targetAngle = 90; // 90 degrees
        currentAnimation.speed = 3.0f; // degrees per frame
        
        cout << "Starting animation..." << endl;
    }
}

bool isAnimating() {
    return currentAnimation.active;
}

