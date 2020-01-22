#include "stdafx.h"
#include "ray.h"


ray::ray()
{
}

ray::ray(const vec3 & originParam, const vec3 & directionParam)
{
    origin= originParam;
    direction = directionParam;
}

vec3 ray::pointAtParameter(float t) const
{
    return origin + t*direction;
}


ray::~ray()
{
}
