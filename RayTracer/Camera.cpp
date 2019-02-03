#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
}

ray Camera::getRay(float u, float v) {
    return ray(origin, lowerLeftCorner + (u*horizontal) + (v*vertical - origin));
}


Camera::~Camera()
{
}
