#include "stdafx.h"
#include "vec3.h"


vec3::vec3()
{
}

vec3::vec3(float x, float y, float z)
{
    v[0] = x;
    v[1] = y;
    v[2] = z;
}


inline void vec3::makeUnitVector()
{
    float l = length();
    v[0] /= l;
    v[1] /= l;
    v[2] /= l;
}

vec3::~vec3()
{
}

inline vec3 & vec3::operator+=(const vec3 & v2)
{
    v[0] += v2[0];
    v[1] += v2[1];
    v[2] += v2[2];
    return *this;
}

inline vec3 & vec3::operator-=(const vec3 & v2)
{
    v[0] -= v2[0];
    v[1] -= v2[1];
    v[2] -= v2[2];
    return *this;
}

inline vec3 & vec3::operator*=(const vec3 & v2)
{
    v[0] *= v2[0];
    v[1] *= v2[1];
    v[2] *= v2[2];
    return *this;
}

inline vec3 & vec3::operator/=(const vec3 & v2)
{
    v[0] /= v2[0];
    v[1] /= v2[1];
    v[2] /= v2[2];
    return *this;
}

inline vec3 & vec3::operator*=(const float & t)
{
    v[0] *= t;
    v[1] *= t;
    v[2] *= t;
    return *this;
}

inline vec3 & vec3::operator/=(const float & t)
{
    v[0] /= t;
    v[1] /= t;
    v[2] /= t;
    return *this;
}
