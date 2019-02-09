#pragma once

#include "Hitable.h"
class Sphere : public Hitable
{
public:
    Sphere();
    Sphere(vec3 cen, float r, std::shared_ptr<Material> m) : center(cen), radius(r), mat{m} {};
    // Inherited via Hitable
    virtual bool hit(const ray & r, float tMin, float tMax, HitRecord & rec) const override;
    virtual ~Sphere();
private:
    vec3 center;
    float radius;
    std::shared_ptr<Material> mat;
};

