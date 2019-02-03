#pragma once

#include "Ray.h"
#include <memory>


struct HitRecord
{
    float t;
    vec3 p;
    vec3 normal;
};
class Hitable
{
public:
    virtual bool hit(const ray& r, float tMin, float tMax, HitRecord& rec) const;
    virtual ~Hitable();
};

