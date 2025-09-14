#ifndef CUBE_H
#define CUBE_H

#include <GL/glut.h>
#include <vector>
#include "camera.h"

// Color constants for Rubik's cube faces
enum CubeColor
{
    WHITE = 0,
    YELLOW,
    RED,
    ORANGE,
    BLUE,
    GREEN
};

// Structure to represent a single small cube (cubie)
struct Cubie
{
    point3f position;
    int colors[6];

    Cubie(float px, float py, float pz);
    void draw();
};

// Main Rubik's cube class (simplified - no rotation methods)
class RubiksCube
{
private:
    std::vector<std::vector<std::vector<Cubie *>>> cube;

public:
    RubiksCube();
    ~RubiksCube();

    void draw();
    void initializeCube();

    // Origins
    point3f topOrigin = point3f(0.0f, 1.0f, 0.0f);
    point3f middleOrigin = point3f(0.0f, 0.0f, 0.0f);
    point3f bottomOrigin = point3f(0.0f, -1.0f, 0.0f);
    point3f leftOrigin = point3f(-1.0f, 0.0f, 0.0f);
    point3f centerOrigin = point3f(0.0f, 0.0f, 0.0f);
    point3f rightOrigin = point3f(1.0f, 0.0f, 0.0f);
    point3f frontOrigin = point3f(0.0f, 0.0f, 1.0f);
    point3f backOrigin = point3f(0.0f, 0.0f, -1.0f);

    void rotateLayer(point3f origin, int axis, bool clockwise);
};

extern RubiksCube *rubiksCube;


#endif
