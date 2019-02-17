#pragma once
#define _USE_MATH_DEFINES
#include "ray.h"
#include <math.h>
class Camera
{
public:
    Camera();
    Camera(vec3 o, vec3 llc, vec3 h, vec3 v) : origin{ o }, lowerLeftCorner{ llc }, horizontal{ h }, vertical{ v } {};
    Camera(vec3 lookFrom, vec3 lookAt, vec3 vecUp, float fov, float aspect);
    ray getRay(float u, float v);
    ~Camera();
private:
    vec3 origin;
    vec3 lowerLeftCorner;
    vec3 horizontal;
    vec3 vertical;
};

