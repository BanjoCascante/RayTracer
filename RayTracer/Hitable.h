#pragma once

#include "Ray.h"
#include <memory>
#include "Material.h"

class HitRecord
{
public:
    float t;
    vec3 p;
    vec3 normal;
    std::shared_ptr<Material>mat;
};
class Hitable
{
public:
    Hitable();
    virtual bool hit(const ray& r, float tMin, float tMax, HitRecord& rec) const;
    virtual ~Hitable();
};

