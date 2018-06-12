//
//  InputParser.cpp
//  raytracer_demo
//
//  Created by Pavlo Liasota on 6/10/18.
//  Copyright © 2018 none. All rights reserved.
//

#include "InputParser.hpp"
#include <iostream>
#include <fstream>
#include <glm/gtc/matrix_transform.hpp>

ParsedInput InputParser::Parse(const char *filepath)
{
    this->Clear();
    
    std::fstream fin(filepath);
    if (!fin.is_open()) {
        std::cerr << "File \"" << filepath << "\" cannot be opened" << std::endl;
        return m_result;
    }
    
    std::vector<glm::mat4> matrixStack;
    matrixStack.push_back(glm::mat4(1.0f));
    while (fin.good()) {
        std::string line;
        std::getline(fin, line);
        if (line[0] == '#' || line.empty()) continue;
        
        std::stringstream commmandStream(line);
        std::string commandStr;
        commmandStream >> commandStr;
        
        ExecuteCommand(commandStr, commmandStream, matrixStack);
    }
    
    return m_result;
}

void InputParser::ExecuteCommand(std::string command, std::stringstream &args, std::vector<glm::mat4> &matrixStack) {
    if (command == "camera") {
        glm::vec3 eye;
        args >> eye.x >> eye.y >> eye.z;
        glm::vec3 center;
        args >> center.x >> center.y >> center.z;
        glm::vec3 up;
        args >> up.x >> up.y >> up.z;
        float fov;
        args >> fov;
        
        m_result.camera = Camera(eye, center, up, glm::radians(fov));
    }
    else if (command == "size") {
        args >> m_result.width >> m_result.height;
    }
    else if (command == "maxdepth") {
        args >> m_result.maxRayRecursion;
    }
    else if (command == "output") {
        args >> m_result.outputFilepath;
    }
    else if (command == "pushTransform") {
        matrixStack.push_back(matrixStack.back());
    }
    else if (command == "popTransform") {
        matrixStack.pop_back();
    }
    else if (command == "ambient") {
        args >> m_material.ambient.r >> m_material.ambient.g >> m_material.ambient.b;
        m_material.ambient.a = 1.0f;
    }
    else if (command == "diffuse") {
        args >> m_material.diffuse.r >> m_material.diffuse.g >> m_material.diffuse.b;
        m_material.diffuse.a = 1.0f;
    }
    else if (command == "specular") {
        args >> m_material.specular.r >> m_material.specular.g >> m_material.specular.b;
        m_material.diffuse.a = 1.0f;
    }
    else if (command == "emission") {
        args >> m_material.emmisive.r >> m_material.emmisive.g >> m_material.emmisive.b;
        m_material.emmisive.a = 1.0f;
    }
    else if (command == "shininess") {
        args >> m_material.shininess;
    }
    else if (command == "directional") {
        Light light;
        light.dir.w = 0.0f;
        args >> light.dir.x >> light.dir.y >> light.dir.z >> light.color.r >> light.color.g >> light.color.b;
        m_result.scene.lights.push_back(light);
    }
    else if (command == "point") {
        Light light;
        light.dir.w = 1.0f;
        args >> light.dir.x >> light.dir.y >> light.dir.z >> light.color.r >> light.color.g >> light.color.b;
        m_result.scene.lights.push_back(light);
    }
    else if (command == "vertex") {
        glm::vec3 vertex;
        args >> vertex.x >> vertex.y >> vertex.z;
        this->m_vertices.push_back(vertex);
    }
    else if (command == "tri") {
        int i1, i2, i3;
        args >> i1 >> i2 >> i3;
        m_result.scene.triangles.push_back(Triangle(m_vertices[i3], m_vertices[i2], m_vertices[i1], m_material));
        m_result.scene.triangles.back().SetTransform(matrixStack.back());
    }
    else if (command == "sphere") {
        glm::vec3 center;
        args >> center.x >> center.y >> center.z;
        float radius;
        args >> radius;
        this->m_result.scene.spheres.push_back(Sphere(radius, m_material, center));
        m_result.scene.spheres.back().SetTransform(matrixStack.back());
    }
    else if (command == "scale") {
        glm::vec3 magnitude;
        args >> magnitude.x >> magnitude.y >> magnitude.z;
        matrixStack.back() = glm::scale(matrixStack.back(), magnitude);
    }
    else if (command == "translate") {
        glm::vec3 magnitude;
        args >> magnitude.x >> magnitude.y >> magnitude.z;
        matrixStack.back() = glm::translate(matrixStack.back(), magnitude);
    }
    else if (command == "rotate") {
        glm::vec3 axis;
        args >> axis.x >> axis.y >> axis.z;
        float angle;
        args >> angle;
        matrixStack.back() = glm::rotate(matrixStack.back(), glm::radians(angle), axis);
    }
    else {
        std::cerr << "Unknown command: " << command << std::endl;
    }
    
}

void InputParser::Clear()
{
    m_material = Material(glm::vec4(0.1f),
                          glm::vec4(1.0f),
                          glm::vec4(0.0f),
                          glm::vec4(0.0f),
                          1.0f,
                          0.4f);
    this->m_vertices.clear();
    this->m_result = ParsedInput();
    
}
