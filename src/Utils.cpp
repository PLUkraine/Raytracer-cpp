//
//  Utils.cpp
//  raytracer_demo
//
//  Created by Pavlo Liasota on 6/4/18.
//  Copyright © 2018 none. All rights reserved.
//

#include "Utils.hpp"

static const float EPS = 1e-5f;

bool approxEq(float a, float b) {
    return fabsf(a-b) < EPS;
}

int sgn(float x)
{
    if (approxEq(x, 0.0f)) return 0;
    return x > 0 ? 1 : -1;
}

glm::vec3 transform(const glm::mat4 &mat, const glm::vec3 &v, bool isPoint)
{
    return mat * glm::vec4(v, isPoint ? 1.0f : 0.0f);
}

glm::vec3 transformNormal(const glm::mat4 &trans, const glm::vec3 &normal) {
    glm::vec3 answer = trans * glm::vec4(normal, 0.0f);
    return glm::normalize(answer);
}
