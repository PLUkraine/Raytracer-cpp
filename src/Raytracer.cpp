//
//  Raytracer.cpp
//  raytracer_demo
//
//  Created by Pavlo Liasota on 6/8/18.
//  Copyright © 2018 none. All rights reserved.
//

#include "Raytracer.hpp"
#include <iostream>
#include <thread>
#include <vector>
#include <glm/ext.hpp>
#include "Utils.hpp"


void Raytracer::RenderScene(const Camera &camera, const WorldScene &scene, Framebuffer *framebuffer, int recursiveLevel)
{
    for (int y=0; y<framebuffer->height(); ++y) {
        for (int x=0; x<framebuffer->width(); ++x) {
            Ray cameraRay = camera.GetRay(x, y, framebuffer->width(), framebuffer->height());
            glm::vec4 color = RecursiveShading(cameraRay, scene, recursiveLevel);
            framebuffer->SetPixelRGB(x, y,
                                     0xff * color.r,
                                     0xff * color.g,
                                     0xff * color.b);
        }
    }
}

// Derevo would be proud!
void Raytracer::RenderSceneParallel(const Camera &camera, const WorldScene &scene, Framebuffer *framebuffer, int recursiveLevel, int numberOfThreads, bool verbose)
{
    // draw only some horizontal stripes
    auto threadFunc = [&](int fromY, int toY) {
        for (int y=fromY; y<toY; ++y) {
            for (int x=0; x<framebuffer->width(); ++x) {
                Ray cameraRay = camera.GetRay(x, y, framebuffer->width(), framebuffer->height());
                glm::vec4 color = RecursiveShading(cameraRay, scene, recursiveLevel);
                framebuffer->SetPixelRGB(x, y,
                                         0xff * color.r,
                                         0xff * color.g,
                                         0xff * color.b);
            }
            if (verbose) {
                std::cout << "Row " << y << " finished!" << std::endl;
            }
        }
    };
    
    int partition = framebuffer->height() / numberOfThreads;
    std::vector<std::thread> threads;
    for (int i=0; i<numberOfThreads; ++i) {
        int from = partition * i;
        int to = partition * (i+1);
        threads.push_back(std::thread(threadFunc, from, to));
    }
    
    std::for_each(threads.begin(), threads.end(), [](std::thread &t) {
        t.join();
    });
}

// test ray-object collisions and return the closest intersection
IntersectionInfo Raytracer::FindClosestIntersection(Ray cameraRay, const WorldScene &scene) const
{
    IntersectionInfo answer;
    answer.hasIntesected = false;
    
    for (const Sphere &sphere : scene.spheres) {
        // instead of transforming the sphere to the world coordinates,
        // we transform the ray to the model coodinates
        Ray TransformedRay = cameraRay.Transform(sphere.GetInverseTransform());
        IntersectionInfo collision = PerformCollisionTest<Sphere>(TransformedRay, sphere);
        
        // get collision point in the world coordinates
        collision.point = transform(sphere.GetTransform(), collision.point);
        if (IsCandidateCloser(answer, collision, cameraRay.p0)) {
            // get normal in the world coordinates
            collision.normal = transformNormal(sphere.GetNormalTransform(), collision.normal);
            answer = collision;
        }
    }
    // same applies to the triangle
    for (const Triangle &triangle : scene.triangles) {
        Ray transformedRay = cameraRay.Transform(triangle.GetInverseTransform());
        IntersectionInfo collision = PerformCollisionTest<Triangle>(transformedRay, triangle);
        
        collision.point = transform(triangle.GetTransform(), collision.point);
        if (IsCandidateCloser(answer, collision, cameraRay.p0)) {
            collision.normal = transformNormal(triangle.GetNormalTransform(), collision.normal);
            answer = collision;
        }
    }
    return answer;
}
// check if ray intersects any object in the scene
bool Raytracer::CollidesWithObject(Ray ray, const WorldScene &scene) const
{
    for (Sphere sphere : scene.spheres) {
        Ray transformedRay = ray.Transform(sphere.GetInverseTransform());
        IntersectionInfo collision = PerformCollisionTest<Sphere>(transformedRay, sphere);
        
        if (collision.hasIntesected) return true;
    }
    for (Triangle triangle : scene.triangles) {
        Ray transformedRay = ray.Transform(triangle.GetInverseTransform());
        IntersectionInfo collision = PerformCollisionTest(transformedRay, triangle);
        
        if (collision.hasIntesected) return true;
    }
    return false;
}
// check if candidate is the new answer
bool Raytracer::IsCandidateCloser(IntersectionInfo answer, IntersectionInfo candidate, glm::vec3 eye) const
{
    if (!candidate.hasIntesected) return false;
    if (!answer.hasIntesected) return true;
    
    return glm::length2(answer.point - eye) > glm::length2(candidate.point - eye);
}
// determine the color of this pixel
glm::vec4 Raytracer::Shade(const WorldScene &scene, IntersectionInfo info, glm::vec3 eye) const
{
    glm::vec4 result = info.material.ambient + info.material.emmisive;
    
    // TODO caclulate diffuse and specular components...
    for (Light light : scene.lights) {
        glm::vec3 direction0 = CalculateLightDirection(light, info.point);
        glm::vec3 eyedir = glm::normalize(eye - info.point);
        if (IsInShadow(scene, light, info.point, eyedir)) continue;
        
        glm::vec3 half0 = glm::normalize(direction0 + eyedir);
        glm::vec4 col = ComputeLight(direction0, light.color, info.normal, half0, info.material.diffuse, info.material.specular, info.material.shininess);
        result += col;
    }
    
    result = glm::clamp(result, 0.0f, 1.0f);
    return result;
}

// get direction to the light
glm::vec3 Raytracer::CalculateLightDirection(const Light &light, glm::vec3 objectPoint) const
{
    return light.IsPoint()
        ? glm::normalize(light.GetPosition() - objectPoint)
        : light.GetDirection();
}

// Blinn-Phong model
glm::vec4 Raytracer::ComputeLight(glm::vec3 direction, glm::vec4 lightcolorn, glm::vec3 normal, glm::vec3 halfvec, glm::vec4 mydiffuse, glm::vec4 myspecular, float myshininess) const
{
    float nDotL = dot(normal, direction)  ;
    glm::vec4 lambert = mydiffuse * lightcolorn * glm::max(nDotL, 0.0f);
    
    float nDotH = dot(normal, halfvec) ;
    glm::vec4 phong = myspecular * lightcolorn * glm::pow(glm::max(nDotH, 0.0f), myshininess);
    
    glm::vec4 retval = lambert + phong ;
    return retval;
}
// check if point is in the shadow
bool Raytracer::IsInShadow(const WorldScene& scene, const Light& light, glm::vec3 point, glm::vec3 towardObject) const
{
    glm::vec3 correctedPoint = point + towardObject/100.f;
    Ray lightRay = {
        correctedPoint,
        CalculateLightDirection(light, correctedPoint)
    };
    return CollidesWithObject(lightRay, scene);
}

// get color with reflections
glm::vec4 Raytracer::RecursiveShading(Ray ray, const WorldScene &scene, int recurseLevel) const
{
    if (recurseLevel == 0) return glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    
    IntersectionInfo collision = FindClosestIntersection(ray, scene);
    if (collision.hasIntesected) {
        glm::vec4 color = Shade(scene, collision, ray.p0);
        glm::vec4 reflectionColor = ReflectionShade(ray, scene, collision, recurseLevel) * collision.material.specular;
        
        return glm::clamp(color + reflectionColor, 0.0f, 1.0f);
    } else {
        return glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }
}

// get reflective component
glm::vec4 Raytracer::ReflectionShade(const Ray &originalRay, const WorldScene &scene, IntersectionInfo collision, int recurseLevel) const
{
    if (approxEq(0.0f, collision.material.reflectiveness)) return glm::vec4(0.0f);
    
    glm::vec3 reflectionDir = glm::reflect(originalRay.p1, collision.normal);
    Ray reflectionRay = {
        collision.point + reflectionDir/100.0f,
        reflectionDir
    };
    glm::vec4 reflectionColor = collision.material.reflectiveness * RecursiveShading(reflectionRay, scene, recurseLevel - 1);
    return reflectionColor;
}

