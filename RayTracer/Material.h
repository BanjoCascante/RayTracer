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

inline bool refract(const vec3 &v, const vec3& n, float niOverNt, vec3& refracted) {

    vec3 uv{ unitVector(v) };
    float dt{ dot(uv, n) };
    float discriminant{ 1.0f - niOverNt * niOverNt* (1 - dt * dt) };
    if (discriminant > 0) {
        refracted = niOverNt * (uv - n * dt) - n * sqrtf(discriminant);
        return true;
    }
    else {
        return false;
    }
}

inline float schlick(float cosine, float refIdx) {
    float r0{ (1 - refIdx) / (1 + refIdx) };
    r0 = r0 * r0;
    return r0 + (1 - r0)*powf((1 - cosine), 5);
}
class Material
{
public:
    Material() = default;
    virtual bool scatter(const ray& r_in, const HitRecord& rec, vec3& attenuation, ray& scattered) const = 0;
    virtual ~Material() = default;
};

