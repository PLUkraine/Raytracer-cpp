//
//  main.cpp
//  raytracer_demo
//
//  Created by Pavlo Liasota on 6/3/18.
//  Copyright © 2018 Pavlo Liasota. All rights reserved.
//

// STD LIB
#include <iostream>
#include <chrono>
// IMAGING
#include <FreeImage.h>
// GLM
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
// CUSTOM
#include "Raytracer.hpp"
#include "InputParser.hpp"
// TESTING
#include "Tests.hpp"

const int WIDTH = 640;
const int HEIGHT = 480;
const int MAX_RECURSION_LEVEL = 5;
const int THREADS_COUNT = 30;

void GlobalInit()
{
    std::cout << "Global Initialization..." << std::endl;
    FreeImage_Initialise();
}
void GlobalDispose()
{
    std::cout << "Global Disposing..." << std::endl;
    FreeImage_DeInitialise();
}
WorldScene CreateScene();

int main(int argc, const char * argv[]) {
    runTests();
    
    GlobalInit();
    
    ParsedInput input;
    input = DefaultParameters(input)
    
    Raytracer raytracer;
    Framebuffer colorBuffer(input.width, input.height);
    
    colorBuffer.Clear();
    auto timeStart = std::chrono::system_clock::now();
//        raytracer.RenderScene(input.camera, input.scene, &colorBuffer, input.maxRayRecursion);
    raytracer.RenderSceneParallel(input.camera, input.scene, &colorBuffer, input.maxRayRecursion, THREADS_COUNT);
    auto timeEnd = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart);
    std::cout << "Time: " << elapsed.count()/1000.f << std::endl;
    
    colorBuffer.SaveImage(input.outputFilepath.c_str());

    GlobalDispose();
    return 0;
}

void DefaultParameters(ParsedInput &input)
{
    input.camera = Camera(glm::vec3(0.0f, 5.0f, -10.0f),
                          glm::vec3(0.0f, 0.0f, 0.0f),
                          glm::vec3(0.0f, 1.0f, 0.0f),
                          glm::radians(60.0));
    input.height = HEIGHT;
    input.width = WIDTH;
    input.maxRayRecursion = MAX_RECURSION_LEVEL;
    input.outputFilepath = "out.png";
    input.scene = CreateScene();
}

WorldScene CreateScene()
{
    std::vector<Sphere> spheres = {
        Sphere(
               // radius
               1.0f,
               // material
               Material(glm::vec4(0.1f, 0.0f, 0.0f, 1.0f),
                        glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
                        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
                        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
                        128.0f,
                        0.1f),
               glm::vec3(-2.0f, 0.0f, 0.0f)
               ),
        Sphere(
               // radius
               1.0f,
               // material
               Material(glm::vec4(0.0f, 0.1f, 0.0f, 1.0f),
                        glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
                        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
                        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
                        128.0f,
                        0.5f)
               ),
        Sphere(
               // radius
               1.0f,
               // material
               Material(glm::vec4(0.0f, 0.0f, 0.1f, 1.0f),
                        glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
                        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
                        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
                        128.0f,
                        1.0f),
               glm::vec3(2.0f, 0.0f, 0.0f)
               ),
    };
    
    Material cubeMatrial(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f),
                         glm::vec4(0.7f, 0.5f, 0.2f, 1.0f),
                         glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
                         glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
                         4.0f,
                         0.0f);
    std::vector<Triangle> triangles = {
        Triangle(glm::vec3(-50.0f, -5.0f, -50.0f),
                 glm::vec3(+50.0f, -5.0f, -50.0f),
                 glm::vec3(0.0f, -5.0f, 50.0f),
                 cubeMatrial)
    };
    
    
    std::vector<Light> lights = {
        Light(glm::vec4(0.0f, 10.0f, 0.0f, 1.0f),
              glm::vec4(0.8f, 0.8f, 0.8f, 1.0f)),
//        Light(glm::vec4(0.0f, 2.0f, -10.0f, 0.0f),
//              glm::vec4(1.0f, 1.0f, 0.1f, 1.0f))
    };
    
    WorldScene scene = {
        spheres,
        triangles,
        lights,
    };
    return scene;
}


