// RayTracer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
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
#include <chrono>
#include <sstream>
using std::make_shared;

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

std::list<std::shared_ptr<Hitable>> randomScene() {
    std::list<std::shared_ptr<Hitable>> myList;
    myList.push_back(make_shared<Sphere>(vec3{ 0.0f, -1000.0f,0.0f }, 100.0f, make_shared<Lambertian>(vec3{ 0.5f,0.5f, 0.5f })));
    
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            float chooseMat = float(rand()) / RAND_MAX;
            vec3 center{a+0.9f*(float(rand()) / RAND_MAX),0.2f,b + 0.9f*(float(rand()) / RAND_MAX) };

            if (chooseMat < 0.80f) {
                myList.push_back(make_shared<Sphere>(center, 0.2f, make_shared<Lambertian>(vec3{ float(rand()) / RAND_MAX,float(rand()) / RAND_MAX, float(rand()) / RAND_MAX })));

            }
            else if (chooseMat < 0.95f) {
                myList.push_back(make_shared<Sphere>(center, 0.2f, make_shared<Metal>(vec3{ float(rand()) / RAND_MAX,float(rand()) / RAND_MAX, float(rand()) / RAND_MAX }, float(rand()) / RAND_MAX)));

            }
            else {
                myList.push_back(make_shared<Sphere>(center, 0.2f, make_shared<Dielectric>(1.5f)));
            }

        }
    }
    return std::move(myList);
}

int main()
{
    
    int nx = 200;
    int ny = 150;
    int ns = 10;
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    std::cout << "Generating image \n";
    
    std::ofstream outputImage;
    outputImage.open("myImage.ppm");
    outputImage << "P3\n" << nx << " " << ny << "\n255\n";
    vec3 lookFrom{ 13.0f,2.0f,3.0f };
    vec3 lookAt{ 0.0f,0.0f,0.0f };
    float distToFocus{ 10.0f };
    float aperture{ 0.1f };
    Camera myCamera{ lookFrom,lookAt, vec3{ 0.0f,1.0f,0.0f }, 20.0f, float(nx)/float(ny),aperture,distToFocus };

    std::shared_ptr<Hitable> world( new HitableList(randomScene()));
    std::vector<std::string> values{ size_t(ny*nx) };
    for (int j = ny-1; j >=0 ; j--) {
        std::cout << "Progress" << float(ny - j) / ny << "\n";
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
            std::ostringstream stream;
            stream << ir << " " << ig << " " << ib << "\n";
            values[(ny-1-j)*nx+i] = stream.str();
        }
    }
    for (auto str : values) {
        outputImage << str;
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Image took "
        << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
        << "ms.\n";
    outputImage.close();
    return 0;
}

