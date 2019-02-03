#pragma once

#include "Hitable.h"
class Sphere : public Hitable
{
public:
    Sphere();
    Sphere(vec3 cen, float r) : center(cen), radius(r) {};
    // Inherited via Hitable
    virtual bool hit(const ray & r, float tMin, float tMax, HitRecord & rec) const override;
    virtual ~Sphere();
private:
    vec3 center;
    float radius;
};

