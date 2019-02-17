#pragma once
#include "Material.h"
#include "Hitable.h"
class Dielectric : public Material
{
public:
    Dielectric(float ri) : refIdx{ ri } {};
    ~Dielectric();

    // Inherited via Material
    virtual bool scatter(const ray & r_in, const HitRecord & rec, vec3 & attenuation, ray & scattered) const override;
    float refIdx;
};

