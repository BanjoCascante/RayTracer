#pragma once
#include "Material.h"
#include "Hitable.h"
class Metal: public Material
{
public:
    Metal(const vec3& a, float f) :albedo{ a } { if (f < 1) { fuzz = f; } else { fuzz = 1; } };
    ~Metal();

    // Inherited via Material
    virtual bool scatter(const ray & r_in, const HitRecord & rec, vec3 & attenuation, ray & scattered) const override;
private:
    vec3 albedo;
    float fuzz;
};

