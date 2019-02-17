#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
}

Camera::Camera(vec3 lookFrom, vec3 lookAt, vec3 vecUp, float fov, float aspect)
{
    vec3 u, v, w;
    float theta{ fov * float(M_PI) / 180.0f };
    float halfHeight{ tanf(theta / 2) };
    float halfWidth{ aspect*halfHeight };
    origin = lookFrom;
    w = unitVector(lookFrom - lookAt);
    u = unitVector(cross(vecUp, w));
    v = cross(w, u);
    lowerLeftCorner = origin - halfWidth * u - halfHeight * v - w;
    horizontal = 2 * halfWidth *u;
    vertical = 2 * halfHeight*v;

}

ray Camera::getRay(float u, float v) {
    return ray(origin, lowerLeftCorner + (u*horizontal) + (v*vertical - origin));
}


Camera::~Camera()
{
}
