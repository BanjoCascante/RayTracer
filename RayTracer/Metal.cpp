#include "stdafx.h"
#include "Metal.h"




Metal::~Metal()
{
}

bool Metal::scatter(const ray & r_in, const HitRecord & rec, vec3 & attenuation, ray & scattered) const
{
    vec3 reflected = reflect(unitVector(r_in.direction()), rec.normal);
    scattered = ray(rec.p, reflected + fuzz* randomInUnitSphere());
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
    return false;
}

