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
#include "HitableVector.h"
#include "Camera.h"
#include "Material.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"
#include <chrono>
#include <sstream>
#include <thread>
using std::make_shared;

vec3 color(const ray& r, const std::shared_ptr<Hitable> world, int depth) {
    HitRecord rec;
    if (world->hit(r, 0.001f, FLT_MAX, rec)) {
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
        vec3 direction{ unitVector(r.direction) };
        float t = (1.0f + direction.y())*0.5f;
        return vec3{ (1.0f - t)*vec3 { 1.0f,1.0f,1.0f } +t * vec3{ 0.5f,0.7f,1.0f } };
    }
}

std::vector<std::shared_ptr<Hitable>> randomScene() {
    std::vector<std::shared_ptr<Hitable>> myList;
    myList.push_back(make_shared<Sphere>(vec3{ 0.0f, -1000.0f,0.0f }, 1000.0f, make_shared<Lambertian>(vec3{ 0.5f,0.5f, 0.5f })));
    
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            float chooseMat = randomDouble();
            vec3 center{a+0.9f* randomDouble(),0.2f,b + 0.9f* randomDouble() };

            if (chooseMat < 0.80f) {
                myList.push_back(make_shared<Sphere>(center, 0.2f, make_shared<Lambertian>(vec3{ randomDouble(),randomDouble(), randomDouble() })));

            }
            else if (chooseMat < 0.95f) {
                myList.push_back(make_shared<Sphere>(center, 0.2f, make_shared<Metal>(vec3{ randomDouble(), randomDouble(), randomDouble() }, randomDouble())));

            }
            else {
                myList.push_back(make_shared<Sphere>(center, 0.2f, make_shared<Dielectric>(1.5f)));
            }

        }
    }
    myList.push_back(make_shared<Sphere>(vec3(0, 1, 0), 1.0f, make_shared<Dielectric>(1.5f)));
    myList.push_back(make_shared<Sphere>(vec3(-4.0, 1, 0),1.0f, make_shared<Lambertian>(vec3(0.4f, 0.2f, 0.1f))));
    myList.push_back(make_shared<Sphere>(vec3(4.0f, 1, 0), 1.0f, make_shared<Metal>(vec3(0.7f, 0.6f, 0.5f), 0.0f)));

    return std::move(myList);
}

void calculatePixel(int ns, int j, int i, int nx, int ny, Camera& myCamera, std::shared_ptr<Hitable> world, std::string& value) {
    vec3 c{ 0.0f,0.0f,0.0f };
    for (int k = 0; k < ns; k++) {
        float random = randomDouble();
        float v = float(j + random) / float(ny);
        float u = float(i + random) / float(nx);
        ray r{ myCamera.getRay(u, v) };
        c += color(r, world, 0);
    }
    c /= float(ns);
    c = vec3(sqrtf(c.r()), sqrtf(c.g()), sqrtf(c.b()));
    int ir = int(255.99 * c.r());
    int ig = int(255.99 * c.g());
    int ib = int(255.99 * c.b());
    std::ostringstream stream;
    stream << ir << " " << ig << " " << ib << "\n";
    value = stream.str();
}

void calculatePixels(int index, int numOfThreads, int numOfSamples, int nx, int ny, Camera& myCamera, std::shared_ptr<Hitable> world, std::vector<std::string>& values) {
    int pixelsToCalculate = nx * ny;
    for (int currentIndex = index; currentIndex < pixelsToCalculate; currentIndex+=numOfThreads) {
        int i = currentIndex % nx;
        int j = ny - (currentIndex / nx);
        calculatePixel(numOfSamples, j, i, nx, ny, std::ref(myCamera), std::ref(world), std::ref(values[currentIndex]));
    }
}


int main(int argc, char* argv[])
{
    
    int nx = 1920;
    int ny = 1080;
    int ns = 100;
    int numOfThreads = 8;
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
    std::vector<std::thread> threads = std::vector<std::thread>(numOfThreads);
    std::shared_ptr<Hitable> world( new HitableVector(randomScene()));
    std::vector<std::string> values{ size_t(ny*nx) };
    int pixelsToCalculate = nx * ny;
    int pixelsToCalculatePerThread = pixelsToCalculate / numOfThreads;
    for (int i = 0; i < numOfThreads; i++) {
        threads[i] = std::thread(calculatePixels, i , numOfThreads, ns, nx, ny, std::ref(myCamera), std::ref(world), std::ref(values));
    }

    for (int i = 0; i < numOfThreads; i++) {
        threads[i].join();
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

