#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glut.h>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

struct point3f {
    float x, y, z;
    
    point3f(float px = 0.0f, float py = 0.0f, float pz = 0.0f) : x(px), y(py), z(pz) {}
};

// Camera/Viewport class for 3D navigation like Blender
class Camera {
private:
    float distance;      // Distance from target
    float azimuth;       // Horizontal rotation (around Y axis) in degrees
    float elevation;     // Vertical rotation (up/down) in degrees
    point3f target;      // What we're looking at (cube center)

public:
    Camera();
    
    // Camera control methods
    void orbit(float deltaAzimuth, float deltaElevation);
    void zoom(float deltaDistance);
    void apply();
    void reset();
    
    // Getters for debugging
    float getDistance() const { return distance; }
    float getAzimuth() const { return azimuth; }
    float getElevation() const { return elevation; }
    point3f getTarget() const { return target; }
    
    // Setters
    void setTarget(float x, float y, float z);
    void setDistance(float dist);
};

// Global camera instance
extern Camera* camera;

#endif
