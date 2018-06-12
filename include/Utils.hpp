//
//  Utils.hpp
//  raytracer_demo
//
//  Created by Pavlo Liasota on 6/4/18.
//  Copyright © 2018 none. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp

#define _USE_MATH_DEFINES
#include <math.h>
#include <glm/glm.hpp>

template <typename T>
bool inB(T a, T b, T v) {
    return a<=v && v<b;
}

bool approxEq(float a, float b);
int sgn(float x);
glm::vec3 transform(const glm::mat4 &mat, const glm::vec3 &v, bool isPoint=true);
glm::vec3 transformNormal(const glm::mat4 &trans, const glm::vec3 &normal);

#endif /* Utils_hpp */
