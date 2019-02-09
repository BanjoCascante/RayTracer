#include "stdafx.h"
#include "Lambertian.h"

Lambertian::~Lambertian()
{
}

bool Lambertian::scatter(const ray & r_in, const HitRecord & rec, vec3 & attenuation, ray & scattered) const
{
    vec3 target = rec.p + rec.normal + randomInUnitSphere();
    scattered = ray(rec.p, target - rec.p);
    attenuation = albedo;
    return true;
}
