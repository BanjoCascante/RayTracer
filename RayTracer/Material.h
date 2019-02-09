#pragma once
#include "ray.h"
#include "vec3.h"
#include <cstdlib>
class HitRecord;

inline vec3 randomInUnitSphere() {
    vec3 p{ 0.0f,0.0f,0.0f };
    do {
        float random{ float(rand()) / RAND_MAX };
        p = 2.0f* vec3(random, random, random) - vec3(1.0f, 1.0f, 1.0f);
    } while (p.squaredLength() >= 1.0);
    return p;
}

inline vec3 reflect(const vec3 & light, const vec3 & n)
{
    return light - 2 * dot(light, n)*n;
}

class Material
{
public:
    Material() = default;
    virtual bool scatter(const ray& r_in, const HitRecord& rec, vec3& attenuation, ray& scattered) const = 0;
    virtual ~Material() = default;
};

