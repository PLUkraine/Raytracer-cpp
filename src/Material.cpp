//
//  Material.cpp
//  raytracer_demo
//
//  Created by Pavlo Liasota on 6/8/18.
//  Copyright © 2018 none. All rights reserved.
//

#include "Material.hpp"

Material::Material()
    : ambient(glm::vec4(0.1f)),
    diffuse(glm::vec4(1.0f)),
    specular(glm::vec4(0.0f)),
    emmisive(glm::vec4(0.0f)),
    shininess(0.0f),
    reflectiveness(0.0f)
{
}

Material::Material(glm::vec4 ambient,
                   glm::vec4 diffuse,
                   glm::vec4 specular,
                   glm::vec4 emmisive,
                   float shininess,
                   float reflectiveness)
    : ambient(ambient),
    diffuse(diffuse),
    specular(specular),
    emmisive(emmisive),
    shininess(shininess),
    reflectiveness(reflectiveness)
{
}
