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
#include "Camera.h"
#include "Material.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"

vec3 color(const ray& r, const std::shared_ptr<Hitable> world, int depth) {
    HitRecord rec;
    if (world->hit(r, 0.0001f, FLT_MAX, rec)) {
        ray scattered{};
        vec3 attenuation{};
        if (depth < 50 && rec.mat->scatter(r, rec, attenuation, scattered)) {
            return attenuation * color(scattered, world, depth+1);
        }
        else {
            return vec3{ 0.0f,0.0f,0.0f };
        }
    }
    else {
        //Calculate background color
        vec3 direction{ unitVector(r.direction()) };
        float t = (1.0f + direction.y())*0.5f;
        return vec3{ (1.0f - t)*vec3 { 1.0f,1.0f,1.0f } +t * vec3{ 0.5f,0.7f,1.0f } };
    }
}

int main()
{
    int nx = 400;
    int ny = 300;
    int ns = 100;
    std::ofstream outputImage;
    outputImage.open("myImage.ppm");
    outputImage << "P3\n" << nx << " " << ny << "\n255\n";

    Camera myCamera{ vec3{-2.0f,2.0f,1.0f },vec3{ 0.0f,0.0f,-1.0f }, vec3{ 0.0f,1.0f,0.0f }, 90.0f, float(nx)/float(ny) };

    std::list<std::shared_ptr<Hitable>> myList;
    myList.push_front(std::make_shared<Sphere>(Sphere{ vec3(0.0f, 0.0f, -1.0f), 0.5f,std::make_shared<Lambertian>(Lambertian{ vec3{ 0.1f,0.2f,0.5f } }) }));
    myList.push_front(std::make_shared<Sphere>(Sphere{ vec3(0.0f, -100.5f, -1.0f), 100.0f,std::make_shared<Lambertian>(Lambertian{ vec3{ 0.8f,0.8f,0.0f } }) }));
    myList.push_front(std::make_shared<Sphere>(Sphere{ vec3(1.0f, 0.0f, -1.0f), 0.5f,std::make_shared<Metal>(Metal{ vec3{ 0.8f,0.6f,0.2f }, 0.3f  }) }));
    myList.push_front(std::make_shared<Sphere>(Sphere{ vec3(-1.0f, 0.0f, -1.0f), 0.5f,std::make_shared<Dielectric>(Dielectric{ 1.5f }) }));
    myList.push_front(std::make_shared<Sphere>(Sphere{ vec3(-1.0f, 0.0f, -1.0f), -0.45f,std::make_shared<Dielectric>(Dielectric{1.5f})}));
    std::shared_ptr<Hitable> world( new HitableList(std::move(myList)));
    for (int j = ny-1; j >=0 ; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 c{ 0.0f,0.0f,0.0f };
            for (int k = 0; k < ns; k++) {
                float random = float(rand()) / RAND_MAX;
                float v = float(j + random) / float(ny);
                float u = float(i + random) / float(nx);
                ray r{ myCamera.getRay(u, v) };
                c += color(r, world,0);
            }
            c /= float(ns);
            c = vec3(sqrtf(c.r()), sqrtf(c.g()), sqrtf(c.b()));
            int ir = int(255.99*c.r());
            int ig = int(255.99*c.g());
            int ib = int(255.99*c.b());
            outputImage << ir << " " << ig << " " << ib << "\n";
        }
    }

    outputImage.close();
    return 0;
}

