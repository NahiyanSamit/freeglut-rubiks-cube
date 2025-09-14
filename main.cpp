#include <GL/glut.h>
#include <iostream>
#include "cube.h"
#include "input_handler.h"

using namespace std;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Apply camera transformation
    if (camera) {
        camera->apply();
    }
    
    // Update animations
    updateLayerAnimation();
    
    // Draw the Rubik's cube
    if (rubiksCube) {
        rubiksCube->draw();
    }
    
    glutSwapBuffers();
}

void timer(int value) {
    // Continuous timer for smooth animation
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); // ~60 FPS
}

void initGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    // Set up lighting
    GLfloat light_position[] = {1.0f, 1.0f, 1.0f, 0.0f};
    GLfloat light_ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat light_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    
    // Enable color material
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 100.0);
}

void mouse(int button, int state, int x, int y) {
    handleMouse(button, state, x, y);
}

void mouseMotion(int x, int y) {
    handleMouseMotion(x, y);
}

void keyboard(unsigned char key, int x, int y) {
    handleKeyboard(key, x, y);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Rubik's Cube - Camera Mode");
    
    initGL();
    
    // Create cube and camera
    rubiksCube = new RubiksCube();
    camera = new Camera();
    
    // Set callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutKeyboardFunc(keyboard);
    
    // Set timer for smooth animations
    glutTimerFunc(16, timer, 0);
    
    glutMainLoop();
    
    delete rubiksCube;
    delete camera;
    return 0;
}