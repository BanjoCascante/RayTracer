#include "stdafx.h"
#include "ray.h"


ray::ray()
{
}

ray::ray(const vec3 & origin, const vec3 & direction)
{
    originVec = origin;
    directionVec = direction;
}

vec3 ray::origin() const
{

    return originVec;
}

vec3 ray::direction() const
{
    return directionVec;
}

vec3 ray::pointAtParameter(float t)
{
    return originVec + t*directionVec;
}


ray::~ray()
{
}
