#pragma once
#include "Material.h"
#include "Hitable.h"
class Lambertian: public Material
{
public:
    Lambertian(const vec3& a) : albedo{ a } {};
    ~Lambertian();
    // Inherited via Material
    virtual bool scatter(const ray & r_in, const HitRecord & rec, vec3 & attenuation, ray & scattered) const override;
private:
    vec3 albedo;
};

