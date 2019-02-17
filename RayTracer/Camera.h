#pragma once
#define _USE_MATH_DEFINES
#include "ray.h"
#include <math.h>
#include <stdlib.h> 
inline vec3 randomInUnitDisk() {
    vec3 p;
    do {
        p = 2.0f* vec3{ float(rand()) / RAND_MAX,float(rand()) / RAND_MAX, 0.0f } -vec3{ 1.0f,1.0f,0.0f };
    } while (dot(p, p) >= 1.0f);
    return p;
}
class Camera
{
public:
    Camera();
    Camera(vec3 o, vec3 llc, vec3 h, vec3 v) : origin{ o }, lowerLeftCorner{ llc }, horizontal{ h }, vertical{ v } {};
    Camera(vec3 lookFrom, vec3 lookAt, vec3 vecUp, float fov, float aspect, float aperture, float focusDist);
    ray getRay(float u, float v);
    ~Camera();
private:
    vec3 origin;
    vec3 lowerLeftCorner;
    vec3 horizontal;
    vec3 vertical;
    float lensRadius;
    vec3 u, v, w;

};

