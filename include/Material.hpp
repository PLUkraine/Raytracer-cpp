//
//  Material.hpp
//  raytracer_demo
//
//  Created by Pavlo Liasota on 6/8/18.
//  Copyright © 2018 none. All rights reserved.
//

#ifndef Material_hpp
#define Material_hpp

#include <glm/glm.hpp>

class Material
{
public:
    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 specular;
    glm::vec4 emmisive;
    float shininess;
    float reflectiveness;
    
    Material();
    Material(glm::vec4 ambient,
             glm::vec4 diffuse,
             glm::vec4 specular,
             glm::vec4 emmisive,
             float shininess,
             float reflectiveness);
};

#endif /* Material_hpp */
