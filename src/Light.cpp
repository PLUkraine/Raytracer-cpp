//
//  Light.cpp
//  raytracer_demo
//
//  Created by Pavlo Liasota on 6/8/18.
//  Copyright © 2018 none. All rights reserved.
//

#include "Light.hpp"

Light::Light()
    : dir(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)),
    color(glm::vec4(1.0f))
{
}

Light::Light(glm::vec4 dir, glm::vec4 color)
    : dir(dir),
    color(color)
{
}

bool Light::IsPoint() const
{
    return dir.w > 0.0f;
}
glm::vec3 Light::GetPosition() const
{
    return dir;
}
glm::vec3 Light::GetDirection() const
{
    return glm::normalize(glm::vec3(dir.x, dir.y, dir.z));
}
