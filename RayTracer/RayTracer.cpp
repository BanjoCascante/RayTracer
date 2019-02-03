// RayTracer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <list>
#include "vec3.h"
#include "ray.h"
#include "Hitable.h"
#include "Sphere.h"
#include "HitableList.h"

vec3 color(const ray& r, const std::shared_ptr<Hitable> world) {
    HitRecord rec;
    if (world->hit(r, 0.0, FLT_MAX, rec)) {
        return 0.5f*vec3(rec.normal.x() + 1.0f, rec.normal.y() + 1.0f, rec.normal.z() + 1.0f);
    }
    else {
        //Calculate background color
        vec3 direction{ unitVector(r.direction()) };
        float t = 1.0f + direction.y()*0.5f;
        return vec3{ (1.0f - t)*vec3 { 1.0f,1.0f,1.0f } +t * vec3{ 0.5f,0.7f,1.0f } };
    }
}

int main()
{
    int nx = 800;
    int ny = 600;
    std::ofstream outputImage;
    outputImage.open("myImage.ppm");
    outputImage << "P3\n" << nx << " " << ny << "\n255\n";

    vec3 lowerLeftCorner{ -1.3333f,-1.0, -1.0 };
    vec3 origin{ 0.0,0.0, 0.0 };
    vec3 xAxis{ 2.666f, 0.0, 0.0 };
    vec3 yAxis{ 0.0, 2.0, 0.0 };

    std::list<std::shared_ptr<Hitable>> myList;
    myList.push_front(std::shared_ptr<Hitable>(new Sphere(vec3(0.0f, 0.0f, -1.0f), 0.5f)));
    myList.push_front(std::shared_ptr<Hitable>(new Sphere(vec3(0.0f, -100.5f, -1.0f),100.0f)));
    std::shared_ptr<Hitable> world( new HitableList(std::move(myList)));
    for (int j = ny-1; j >=0 ; j--) {
        for (int i = 0; i < nx; i++) {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            ray r{ origin, lowerLeftCorner+(xAxis*u) + (yAxis*v)};
            vec3 c = color(r, world);
            int ir = int(255.99*c.r());
            int ig = int(255.99*c.g());
            int ib = int(255.99*c.b());
            outputImage << ir << " " << ig << " " << ib << "\n";
        }
    }

    outputImage.close();
    return 0;
}

