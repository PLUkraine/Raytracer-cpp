//
//  IntersectionTest.hpp
//  raytracer_demo
//
//  Created by Pavlo Liasota on 6/8/18.
//  Copyright © 2018 none. All rights reserved.
//

#ifndef IntersectionTest_hpp
#define IntersectionTest_hpp

#include "ColliderObject.hpp"

struct IntersectionInfo
{
    bool hasIntesected;
    glm::vec3 point;
    glm::vec3 normal;
    Material material;
};

class IntersectionTest
{
public:
    
    IntersectionInfo Test(Ray r, Sphere s) const;
    IntersectionInfo Test(Ray r, Triangle t) const;
    
private:
    float DiscriminantSqr(float a, float b, float c) const;
    std::pair<float, float> GetRoots(float a, float b, float c) const;
};

#endif /* IntersectionTest_hpp */
