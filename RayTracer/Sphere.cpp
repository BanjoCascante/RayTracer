#include "stdafx.h"
#include "Sphere.h"


Sphere::Sphere()
{
}
bool Sphere::hit(const ray & r, float tMin, float tMax, HitRecord & rec) const
{
    vec3 originToCenter = r.origin - center;
    vec3 rayDirection = r.direction;
    float a = dot(rayDirection, rayDirection);
    float b = dot(originToCenter, rayDirection);
    float c = dot(originToCenter, originToCenter) - radius * radius;
    float discriminant = b * b - a*c;
    if (discriminant > 0.0f) {
        float temp = (-b - sqrtf(discriminant)) / a;
        if (temp <tMax && temp>tMin) {
            rec.t = temp;
            rec.p = r.pointAtParameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat = mat;
            return true;
        }
        temp = (-b + sqrtf(discriminant)) / a;
        if (temp <tMax && temp>tMin) {
            rec.t = temp;
            rec.p = r.pointAtParameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat = mat;
            return true;
        }
    }
    return false;
}

Sphere::~Sphere()
{
}


