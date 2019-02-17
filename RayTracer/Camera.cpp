#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
}

Camera::Camera(vec3 lookFrom, vec3 lookAt, vec3 vecUp, float fov, float aspect, float aperture, float focusDist)
{
    lensRadius = aperture / 2;
    float theta{ fov * float(M_PI) / 180.0f };
    float halfHeight{ tanf(theta / 2) };
    float halfWidth{ aspect*halfHeight };
    origin = lookFrom;
    w = unitVector(lookFrom - lookAt);
    u = unitVector(cross(vecUp, w));
    v = cross(w, u);
    lowerLeftCorner = origin - halfWidth *focusDist* u - halfHeight *focusDist* v - focusDist*w;
    horizontal = 2 * halfWidth *focusDist*u;
    vertical = 2 * halfHeight*focusDist*v;

}

ray Camera::getRay(float s, float t) {
    vec3 rd{ lensRadius * randomInUnitDisk() };
    vec3 offset { u*rd.x() + v * rd.y() };
    return ray(origin+ offset, lowerLeftCorner + (s*horizontal) + (t*vertical) - origin - offset);
}


Camera::~Camera()
{
}
