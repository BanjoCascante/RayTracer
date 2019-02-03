#include "stdafx.h"
#include "Sphere.h"


Sphere::Sphere()
{
}
bool Sphere::hit(const ray & r, float tMin, float tMax, HitRecord & rec) const
{
    vec3 originToCenter = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = dot(originToCenter, r.direction());
    float c = dot(originToCenter, originToCenter) - radius * radius;
    float discriminant = b * b - a*c;
    if (discriminant > 0) {
        float temp = (-b - float(sqrt(discriminant))) / a;
        if (temp <tMax && temp>tMin) {
            rec.t = temp;
            rec.p = r.pointAtParameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
        temp = (-b + float(sqrt(discriminant))) / a;
        if (temp <tMax && temp>tMin) {
            rec.t = temp;
            rec.p = r.pointAtParameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
    }
    return false;
}

Sphere::~Sphere()
{
}


