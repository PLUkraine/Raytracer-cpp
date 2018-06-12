//
//  Raytracer.hpp
//  raytracer_demo
//
//  Created by Pavlo Liasota on 6/8/18.
//  Copyright © 2018 none. All rights reserved.
//

#ifndef Raytracer_hpp
#define Raytracer_hpp

#include <vector>

#include "Camera.hpp"
#include "IntersectionTest.hpp"
#include "Framebuffer.hpp"
#include "Light.hpp"

struct WorldScene {
public:
    std::vector<Sphere> spheres;
    std::vector<Triangle> triangles;
    std::vector<Light> lights;
};

class Raytracer
{
public:
    void RenderScene(const Camera &camera, const WorldScene &scene, Framebuffer *framebuffer, int recursiveLevel=2);
    void RenderSceneParallel(const Camera &camera, const WorldScene &scene, Framebuffer *framebuffer, int recursiveLevel=2, int numberOfTheads=128);
    
private:
    template <typename T>
    IntersectionInfo PerformCollisionTest(Ray r, const T& obj) const
    {
        IntersectionInfo answer = IntersectionTest().Test(r, obj);
        return answer;
    }
    
    IntersectionInfo FindClosestIntersection(Ray cameraRay, const WorldScene &scene) const;
    bool IsCandidateCloser(IntersectionInfo answer, IntersectionInfo candidate, glm::vec3 eye) const;
    glm::vec4 Shade(const WorldScene &scene, IntersectionInfo info, glm::vec3 eye) const;
    
    glm::vec3 CalculateLightDirection(const Light &light, glm::vec3 objectPoint) const;
    glm::vec4 ComputeLight(glm::vec3 direction, glm::vec4 lightcolorn, glm::vec3 normal, glm::vec3 halfvec, glm::vec4 mydiffuse, glm::vec4 myspecular, float myshininess) const;
    bool IsInShadow(const WorldScene& scene, const Light& light, glm::vec3 point, glm::vec3 towardObject) const;
    bool CollidesWithObject(Ray ray, const WorldScene &scene) const;
    
    glm::vec4 RecursiveShading(Ray ray, const WorldScene &scene, int recurseLevel) const;
    glm::vec4 ReflectionShade(const Ray &originalRay, const WorldScene &scene, IntersectionInfo collision, int recurseLevel) const;
};

#endif /* Raytracer_hpp */
