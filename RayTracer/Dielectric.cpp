#include "stdafx.h"
#include "Dielectric.h"



Dielectric::~Dielectric()
{
}

bool Dielectric::scatter(const ray & r_in, const HitRecord & rec, vec3 & attenuation, ray & scattered) const
{
    vec3 outwardNormal{};
    vec3 reflected{ reflect(r_in.direction(), rec.normal) };
    float niOverNt{};
    vec3 refracted{};
    float reflectProb{};
    float cosine{};

    attenuation = vec3{ 1.0,1.0,1.0 };
    if (dot(r_in.direction(),rec.normal) > 0) {
        outwardNormal = -rec.normal;
        niOverNt = refIdx;
        //cosine = refIdx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
        cosine = dot(r_in.direction(), rec.normal) / r_in.direction().length();
        cosine = sqrtf(1.0f - refIdx * refIdx*(1.0f - cosine * cosine));
    }
    else {
        outwardNormal = rec.normal;
        niOverNt = 1.0f / refIdx;
        cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();

    }


    if (refract(r_in.direction(), outwardNormal, niOverNt, refracted)) {
        reflectProb = schlick(cosine, refIdx);
    }
    else {
        reflectProb = 1.0f;
    }

    if (randomDouble() < reflectProb) {
        scattered = ray(rec.p, reflected);
    }
    else {
        scattered = ray(rec.p, refracted);
    }
    return true;
}
