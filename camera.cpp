#include "camera.h"
#include <iostream>

// Global camera instance
Camera* camera = nullptr;

Camera::Camera() {
    distance = 8.0f;         // Start at a good viewing distance
    azimuth = 45.0f;         // Start at 45 degrees horizontally
    elevation = 30.0f;       // Start looking down slightly
    target = point3f(0.0f, 0.0f, 0.0f);  // Look at cube center
}

void Camera::orbit(float deltaAzimuth, float deltaElevation) {
    // Update rotation angles
    azimuth += deltaAzimuth;
    elevation += deltaElevation;
    
    // Clamp elevation to prevent camera flipping
    if (elevation > 89.0f) elevation = 89.0f;
    if (elevation < -89.0f) elevation = -89.0f;
    
    // Keep azimuth in 0-360 range for consistency
    while (azimuth < 0.0f) azimuth += 360.0f;
    while (azimuth >= 360.0f) azimuth -= 360.0f;
}

void Camera::zoom(float deltaDistance) {
    distance += deltaDistance;
    
    // Clamp distance to reasonable bounds
    if (distance < 2.0f) distance = 2.0f;     // Minimum distance
    if (distance > 50.0f) distance = 50.0f;   // Maximum distance
}

void Camera::apply() {
    // Convert spherical coordinates to cartesian coordinates
    float radAzimuth = azimuth * M_PI / 180.0f;
    float radElevation = elevation * M_PI / 180.0f;
    
    // Calculate eye position using spherical coordinates
    float eyeX = target.x + distance * cos(radElevation) * cos(radAzimuth);
    float eyeY = target.y + distance * sin(radElevation);
    float eyeZ = target.z + distance * cos(radElevation) * sin(radAzimuth);
    
    // Apply the camera transformation
    gluLookAt(eyeX, eyeY, eyeZ,              // Eye position
              target.x, target.y, target.z,  // Look at target
              0.0f, 1.0f, 0.0f);             // Up vector (Y is up)
}

void Camera::reset() {
    distance = 8.0f;
    azimuth = 45.0f;
    elevation = 30.0f;
    target = point3f(0.0f, 0.0f, 0.0f);
}

void Camera::setTarget(float x, float y, float z) {
    target.x = x;
    target.y = y;
    target.z = z;
}

void Camera::setDistance(float dist) {
    distance = dist;
    if (distance < 2.0f) distance = 2.0f;
    if (distance > 50.0f) distance = 50.0f;
}
