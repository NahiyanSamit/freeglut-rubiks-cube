#include "cube.h"
#include <iostream>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Global variables
RubiksCube* rubiksCube = nullptr;

// Color RGB values for each face
float colors[6][3] = {
    {1.0f, 1.0f, 1.0f},  // WHITE
    {1.0f, 1.0f, 0.0f},  // YELLOW
    {1.0f, 0.0f, 0.0f},  // RED
    {1.0f, 0.5f, 0.0f},  // ORANGE
    {0.0f, 0.0f, 1.0f},  // BLUE
    {0.0f, 1.0f, 0.0f}   // GREEN
};

// Cubie implementation
Cubie::Cubie(float px, float py, float pz) : position{px, py, pz} {
    // Initialize colors based on position
    for (int i = 0; i < 6; i++) {
        colors[i] = -1; // No color initially
    }
    
    // Assign colors based on position
    if (position.z > 0.5f) colors[0] = WHITE;   // Front face
    if (position.z < -0.5f) colors[1] = YELLOW; // Back face
    if (position.x < -0.5f) colors[2] = RED;    // Left face
    if (position.x > 0.5f) colors[3] = ORANGE;  // Right face
    if (position.y > 0.5f) colors[4] = BLUE;    // Top face
    if (position.y < -0.5f) colors[5] = GREEN;  // Bottom face
}

void Cubie::draw() {
    glPushMatrix();
    glTranslatef(this->position.x, this->position.y, this->position.z);
    
    // Draw cube faces
    glBegin(GL_QUADS);
    
    // Front face (z = 0.5)
    if (colors[0] != -1) {
        glColor3fv(::colors[colors[0]]);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f);
    }
    
    // Back face (z = -0.5)
    if (colors[1] != -1) {
        glColor3fv(::colors[colors[1]]);
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);
    }
    
    // Left face (x = -0.5)
    if (colors[2] != -1) {
        glColor3fv(::colors[colors[2]]);
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f, -0.5f, 0.5f);
    }
    
    // Right face (x = 0.5)
    if (colors[3] != -1) {
        glColor3fv(::colors[colors[3]]);
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f);
    }
    
    // Top face (y = 0.5)
    if (colors[4] != -1) {
        glColor3fv(::colors[colors[4]]);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-0.5f, 0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f);
    }
    
    // Bottom face (y = -0.5)
    if (colors[5] != -1) {
        glColor3fv(::colors[colors[5]]);
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(-0.5f, -0.5f, 0.5f);
    }
    
    glEnd();
    
    // Draw black edges
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(5.0f);
    glBegin(GL_LINES);
    
    // Draw cube edges
    // Bottom face edges
    glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f); glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f); glVertex3f(-0.5f, -0.5f, -0.5f);
    
    // Top face edges
    glVertex3f(-0.5f, 0.5f, -0.5f); glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f); glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f); glVertex3f(-0.5f, 0.5f, -0.5f);
    
    // Vertical edges
    glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f); glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f); glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f); glVertex3f(-0.5f, 0.5f, 0.5f);
    
    glEnd();
    
    glPopMatrix();
}

// RubiksCube implementation
RubiksCube::RubiksCube() {
    initializeCube();
}

RubiksCube::~RubiksCube() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                delete cube[i][j][k];
            }
        }
    }
}

void RubiksCube::initializeCube() {
    cube.resize(3);
    for (int i = 0; i < 3; i++) {
        cube[i].resize(3);
        for (int j = 0; j < 3; j++) {
            cube[i][j].resize(3);
            for (int k = 0; k < 3; k++) {
                float x = (i - 1) * 1.1f;
                float y = (j - 1) * 1.1f;
                float z = (k - 1) * 1.1f;
                cube[i][j][k] = new Cubie(x, y, z);
            }
        }
    }
}

void RubiksCube::draw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                cube[i][j][k]->draw();
            }
        }
    }
}

void RubiksCube::rotateLayer(point3f origin, int axis, bool clockwise) {
    // Find all cubies that belong to this layer
    std::vector<Cubie*> layerCubies;
    std::vector<point3f> oldPositions;
    
    float tolerance = 0.6f; // Tolerance for position matching
    
    // Collect cubies in the layer based on the origin and axis
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                Cubie* cubie = cube[i][j][k];
                bool inLayer = false;
                
                // Check if cubie is in the layer based on axis
                switch (axis) {
                    case 0: // X-axis rotation (around vertical line through origin)
                        if (fabs(cubie->position.x - origin.x) < tolerance) {
                            inLayer = true;
                        }
                        break;
                    case 1: // Y-axis rotation (around horizontal line through origin)  
                        if (fabs(cubie->position.y - origin.y) < tolerance) {
                            inLayer = true;
                        }
                        break;
                    case 2: // Z-axis rotation (around front-back line through origin)
                        if (fabs(cubie->position.z - origin.z) < tolerance) {
                            inLayer = true;
                        }
                        break;
                }
                
                if (inLayer) {
                    layerCubies.push_back(cubie);
                    oldPositions.push_back(cubie->position);
                }
            }
        }
    }
    
    // Rotate each cubie's position around the origin
    for (size_t i = 0; i < layerCubies.size(); i++) {
        Cubie* cubie = layerCubies[i];
        point3f pos = oldPositions[i];
        
        // Translate to origin
        pos.x -= origin.x;
        pos.y -= origin.y;
        pos.z -= origin.z;
        
        // Apply rotation based on axis
        point3f newPos = pos;
        float angle = clockwise ? -M_PI/2 : M_PI/2; // 90 degrees
        
        switch (axis) {
            case 0: // Rotate around X-axis
                newPos.y = pos.y * cos(angle) - pos.z * sin(angle);
                newPos.z = pos.y * sin(angle) + pos.z * cos(angle);
                break;
            case 1: // Rotate around Y-axis
                newPos.x = pos.x * cos(angle) + pos.z * sin(angle);
                newPos.z = -pos.x * sin(angle) + pos.z * cos(angle);
                break;
            case 2: // Rotate around Z-axis
                newPos.x = pos.x * cos(angle) - pos.y * sin(angle);
                newPos.y = pos.x * sin(angle) + pos.y * cos(angle);
                break;
        }
        
        // Translate back from origin
        newPos.x += origin.x;
        newPos.y += origin.y;
        newPos.z += origin.z;
        
        // Round to nearest grid position to avoid floating point errors
        newPos.x = round(newPos.x / 1.1f) * 1.1f;
        newPos.y = round(newPos.y / 1.1f) * 1.1f;
        newPos.z = round(newPos.z / 1.1f) * 1.1f;
        
        cubie->position = newPos;
    }
    
    // Update the cube array to reflect new positions
    // First, clear the cube array
    std::vector<std::vector<std::vector<Cubie*>>> newCube(3);
    for (int i = 0; i < 3; i++) {
        newCube[i].resize(3);
        for (int j = 0; j < 3; j++) {
            newCube[i][j].resize(3);
            for (int k = 0; k < 3; k++) {
                newCube[i][j][k] = nullptr;
            }
        }
    }
    
    // Place all cubies in their new positions
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (cube[i][j][k] != nullptr) {
                    Cubie* cubie = cube[i][j][k];
                    // Calculate new array indices based on position
                    int newI = (int)round(cubie->position.x / 1.1f) + 1;
                    int newJ = (int)round(cubie->position.y / 1.1f) + 1;
                    int newK = (int)round(cubie->position.z / 1.1f) + 1;
                    
                    // Bounds checking
                    if (newI >= 0 && newI < 3 && newJ >= 0 && newJ < 3 && newK >= 0 && newK < 3) {
                        newCube[newI][newJ][newK] = cubie;
                    }
                }
            }
        }
    }
    
    // Update the main cube array
    cube = newCube;
}


