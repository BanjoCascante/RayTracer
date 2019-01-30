// RayTracer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "vec3.h"
#include "ray.h"

bool hitSphere(const vec3& center, float radius, const ray& r) {
    vec3 originToCenter = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0f * dot(originToCenter, r.direction());
    float c = dot(originToCenter, originToCenter) - radius * radius;
    float discriminant = b * b - 4 * a*c;
    return (discriminant > 0);
}
vec3 color(const ray& r) {
    if (hitSphere(vec3{ 0.0f,0.0f,-1.0f }, 0.5f, r)) {
        return vec3{ 1.0f,0.0f,0.0f };
    }
    vec3 direction{ unitVector(r.direction())};
    float t{ 1.0f + direction.y()*0.5f };
    return vec3{ (1.0f - t)*vec3 { 1.0f,1.0f,1.0f } +t * vec3{0.5f,0.7f,1.0f} };
}

int main()
{
    int nx = 800;
    int ny = 600;
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    vec3 lowerLeftCorner{ -1.3333f,-1.0, -1.0 };
    vec3 origin{ 0.0,0.0, 0.0 };
    vec3 xAxis{ 2.666f, 0.0, 0.0 };
    vec3 yAxis{ 0.0, 2.0, 0.0 };

    for (int j = ny-1; j >=0 ; j--) {
        for (int i = 0; i < nx; i++) {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            ray r{ origin, lowerLeftCorner+(xAxis*u) + (yAxis*v)};
            vec3 c = color(r);
            int ir = int(255.99*c.r());
            int ig = int(255.99*c.g());
            int ib = int(255.99*c.b());
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
    return 0;
}

