//
//  IntersectionTest.cpp
//  raytracer_demo
//
//  Created by Pavlo Liasota on 6/8/18.
//  Copyright © 2018 none. All rights reserved.
//

#include "IntersectionTest.hpp"

#include <iostream>
#include <glm/ext.hpp>
#include "Utils.hpp"


IntersectionInfo IntersectionTest::Test(Ray r, const Sphere &s) const
{
    IntersectionInfo answer;
    answer.hasIntesected = false;
    
    float a = glm::dot(r.p1, r.p1);
    float b = 2 * glm::dot(r.p1, r.p0 - s.c);
    float c = glm::dot(r.p0-s.c, r.p0-s.c) - s.r*s.r;
    float dSqr = DiscriminantSqr(a, b, c);
    if (dSqr >= 0.0f)
    {
        answer.hasIntesected = true;
        
        std::pair<float, float> roots = GetRoots(a, b, c);
        if (roots.first > roots.second) {
            std::swap(roots.first, roots.second);
        }
        if (roots.second < 0.0f) {
            // if larger number is negative - sphere is behind
            // the ray!
            answer.hasIntesected = false;
        }
        else {
            // pick positive number
            answer.point = r.GetPoint(roots.first < 0.0f ? roots.second : roots.first);
            answer.material = s.mat;
            answer.normal = s.GetNormal(answer.point);
        }
    }
    return answer;
}
IntersectionInfo IntersectionTest::Test(Ray r, const Triangle &t) const
{
    IntersectionInfo answer;
    answer.hasIntesected = false;
    
    glm::vec3 tN = t.GetNormal(t.a);
    float dotP1tN = glm::dot(r.p1, tN);
    if (approxEq(dotP1tN, 0.0f)) {
        return answer;
    }
    float T = (glm::dot(t.a, tN) - glm::dot(r.p0, tN)) / dotP1tN;
    if (T < 0.0f) {
        return answer;
    }
    glm::vec3 P = r.GetPoint(T);
    
    float ori1 = (glm::dot(glm::cross(glm::normalize(t.b-t.a), tN), P - t.a));
    float ori2 = (glm::dot(glm::cross(glm::normalize(t.c-t.b), tN), P - t.b));
    float ori3 = (glm::dot(glm::cross(glm::normalize(t.a-t.c), tN), P - t.c));
    
    if (sgn(ori1) == sgn(ori2) && sgn(ori2) == sgn(ori3) && sgn(ori3) == sgn(ori1))
    {
        answer.hasIntesected = true;
        answer.material = t.mat;
        answer.normal = tN;
        answer.point = P;
    }
    
    return answer;
}

float IntersectionTest::DiscriminantSqr(float a, float b, float c) const
{
    return b*b - 4 * a * c;
}

std::pair<float, float> IntersectionTest::GetRoots(float a, float b, float c) const
{
    float dSqr = DiscriminantSqr(a, b, c);
    if (dSqr < 0.0f) {
        return {-1, -1};
    }
    else if (approxEq(dSqr, 0.0f)) {
        float answer = -b / 2.0f / a;
        return {answer, answer};
    }
    else {
        float d = sqrt(dSqr);
        float r1 = (-b + d) / 2.0f / a;
        float r2 = (-b - d) / 2.0f / a;
        return {r1, r2};
    }
}
