//
//  InputParser.hpp
//  raytracer_demo
//
//  Created by Pavlo Liasota on 6/10/18.
//  Copyright © 2018 none. All rights reserved.
//

#ifndef InputParser_hpp
#define InputParser_hpp

#include <string>
#include <sstream>
#include <vector>

#include "Camera.hpp"
#include "Raytracer.hpp"

struct ParsedInput
{
    Camera camera;
    WorldScene scene;
    int maxRayRecursion = 5;
    int width = 640;
    int height = 480;
    std::string outputFilepath = "raytrace.png";
};

class InputParser
{
private:
    Material m_material;
    std::vector<glm::vec3> m_vertices;
    ParsedInput m_result;
    
public:
    ParsedInput Parse(const char *filepath);
private:
    void Clear();
    void ExecuteCommand(std::string command, std::stringstream &args, std::vector<glm::mat4> &matrixStack);
};

#endif /* InputParser_hpp */
