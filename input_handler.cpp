#include "input_handler.h"
#include <iostream>
#include <cmath>

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
    switch (key) {
        case 27: // Escape key
            cout << "Exiting Rubik's Cube..." << endl;
            delete rubiksCube;
            exit(0);
            break;
            
        case 'r':
        case 'R':
            resetCube();
            cout << "Camera reset!" << endl;
            glutPostRedisplay();
            break;
            
        // Layer rotations using ZXCVBN keys
        case 'z':
        case 'Z':
            // Rotate top layer clockwise around Y-axis
            if (rubiksCube && !currentAnimation.active) {
                startLayerAnimation(rubiksCube->topOrigin, 1, true);
                cout << "Rotating top layer clockwise" << endl;
            }
            break;
            
        case 'x':
        case 'X':
            // Rotate middle horizontal layer clockwise around Y-axis
            if (rubiksCube && !currentAnimation.active) {
                startLayerAnimation(rubiksCube->middleOrigin, 1, true);
                cout << "Rotating middle horizontal layer clockwise" << endl;
            }
            break;
            
        case 'c':
        case 'C':
            // Rotate bottom layer clockwise around Y-axis
            if (rubiksCube && !currentAnimation.active) {
                startLayerAnimation(rubiksCube->bottomOrigin, 1, true);
                cout << "Rotating bottom layer clockwise" << endl;
            }
            break;
            
        case 'v':
        case 'V':
            // Rotate left layer clockwise around X-axis
            if (rubiksCube && !currentAnimation.active) {
                startLayerAnimation(rubiksCube->leftOrigin, 0, true);
                cout << "Rotating left layer clockwise" << endl;
                glutPostRedisplay();
            }
            break;
            
        case 'b':
        case 'B':
            // Rotate middle vertical layer clockwise around X-axis
            if (rubiksCube && !currentAnimation.active) {
                startLayerAnimation(rubiksCube->centerOrigin, 0, true);
                cout << "Rotating middle vertical layer clockwise" << endl;
            }
            break;
            
        case 'n':
        case 'N':
            // Rotate right layer clockwise around X-axis
            if (rubiksCube && !currentAnimation.active) {
                startLayerAnimation(rubiksCube->rightOrigin, 0, true);
                cout << "Rotating right layer clockwise" << endl;
            }
            break;
            
        // Front and back layer rotations
        case 'f':
        case 'F':
            // Rotate front layer clockwise around Z-axis
            if (rubiksCube && !currentAnimation.active) {
                startLayerAnimation(rubiksCube->frontOrigin, 2, true);
                cout << "Rotating front layer clockwise" << endl;
            }
            break;
            
        case 'g':
        case 'G':
            // Rotate back layer clockwise around Z-axis
            if (rubiksCube && !currentAnimation.active) {
                startLayerAnimation(rubiksCube->backOrigin, 2, true);
                cout << "Rotating back layer clockwise" << endl;
            }
            if (rubiksCube) {
                rubiksCube->rotateLayer(rubiksCube->backOrigin, 2, true);
                cout << "Rotating back layer clockwise" << endl;
                glutPostRedisplay();
            }
            break;
        
        // Counter-clockwise rotations (uppercase variations or different keys)
        case 'q':
        case 'Q':
            // Rotate top layer counter-clockwise
            if (rubiksCube) {
                rubiksCube->rotateLayer(rubiksCube->topOrigin, 1, false);
                cout << "Rotating top layer counter-clockwise" << endl;
                glutPostRedisplay();
            }
            break;
            
        case 'w':
        case 'W':
            // Rotate middle horizontal layer counter-clockwise
            if (rubiksCube) {
                rubiksCube->rotateLayer(rubiksCube->middleOrigin, 1, false);
                cout << "Rotating middle horizontal layer counter-clockwise" << endl;
                glutPostRedisplay();
            }
            break;
            
        case 'e':
        case 'E':
            // Rotate bottom layer counter-clockwise
            if (rubiksCube) {
                rubiksCube->rotateLayer(rubiksCube->bottomOrigin, 1, false);
                cout << "Rotating bottom layer counter-clockwise" << endl;
                glutPostRedisplay();
            }
            break;
            
        case 'a':
        case 'A':
            // Rotate left layer counter-clockwise
            if (rubiksCube) {
                rubiksCube->rotateLayer(rubiksCube->leftOrigin, 0, false);
                cout << "Rotating left layer counter-clockwise" << endl;
                glutPostRedisplay();
            }
            break;
            
        case 's':
        case 'S':
            // Rotate middle vertical layer counter-clockwise
            if (rubiksCube) {
                rubiksCube->rotateLayer(rubiksCube->centerOrigin, 0, false);
                cout << "Rotating middle vertical layer counter-clockwise" << endl;
                glutPostRedisplay();
            }
            break;
            
        case 'd':
        case 'D':
            // Rotate right layer counter-clockwise
            if (rubiksCube) {
                rubiksCube->rotateLayer(rubiksCube->rightOrigin, 0, false);
                cout << "Rotating right layer counter-clockwise" << endl;
                glutPostRedisplay();
            }
            break;
            
        case 't':
        case 'T':
            // Rotate front layer counter-clockwise
            if (rubiksCube) {
                rubiksCube->rotateLayer(rubiksCube->frontOrigin, 2, false);
                cout << "Rotating front layer counter-clockwise" << endl;
                glutPostRedisplay();
            }
            break;
            
        case 'y':
        case 'Y':
            // Rotate back layer counter-clockwise
            if (rubiksCube) {
                rubiksCube->rotateLayer(rubiksCube->backOrigin, 2, false);
                cout << "Rotating back layer counter-clockwise" << endl;
                glutPostRedisplay();
            }
            break;
            
        case 'h':
        case 'H':
            // Show help
            printControls();
            break;
    }
}


// Cube manipulation functions
void resetCube() {
    if (camera) {
        camera->reset();
    }
}

void printControls() {
    cout << "\n=== Rubik's Cube Controls (Camera Mode) ===" << endl;
    cout << "Mouse:" << endl;
    cout << "  Left click + drag: Orbit camera around cube" << endl;
    cout << "  Mouse wheel: Zoom in/out" << endl;
    cout << "  Right click: Reset camera" << endl;
    cout << "\nKeyboard:" << endl;
    cout << "  R: Reset camera position" << endl;
    cout << "  H: Show this help" << endl;
    cout << "  ESC: Exit program" << endl;
    cout << "  Arrow keys: Orbit camera" << endl;
    cout << "\nZoom:" << endl;
    cout << "  +/=: Zoom in" << endl;
    cout << "  -/_: Zoom out" << endl;
    cout << "\nLayer Rotations (Clockwise):" << endl;
    cout << "  Z: Top layer" << endl;
    cout << "  X: Middle horizontal layer" << endl;
    cout << "  C: Bottom layer" << endl;
    cout << "  V: Left layer" << endl;
    cout << "  B: Middle vertical layer" << endl;
    cout << "  N: Right layer" << endl;
    cout << "  F: Front layer" << endl;
    cout << "  G: Back layer" << endl;
    cout << "\nLayer Rotations (Counter-clockwise):" << endl;
    cout << "  Q: Top layer" << endl;
    cout << "  W: Middle horizontal layer" << endl;
    cout << "  E: Bottom layer" << endl;
    cout << "  A: Left layer" << endl;
    cout << "  S: Middle vertical layer" << endl;
    cout << "  D: Right layer" << endl;
    cout << "  T: Front layer" << endl;
    cout << "  Y: Back layer" << endl;
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

