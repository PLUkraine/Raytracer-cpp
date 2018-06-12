//
//  Tests.cpp
//  raytracer_demo
//
//  Created by Pavlo Liasota on 6/7/18.
//  Copyright © 2018 none. All rights reserved.
//

#include "Tests.hpp"

#include <iostream>
#include <assert.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Utils.hpp"
#include "IntersectionTest.hpp"
#include "Camera.hpp"

void testRayContructor1() {
    glm::vec3 from = glm::vec3(1, 1, 1);
    glm::vec3 to = glm::vec3(2, 0, 3.5);
    Ray r = Ray::FromTo(from, to);
    assert(r.p0 == glm::vec3(1, 1, 1));
    assert(r.p1 == glm::normalize(to-from));
}
void testRayCircle1() {
    Ray r = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
    };
    Sphere c = {
        0.5f,
        Material(),
    };
    c.SetTransform(glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.f)));
    
    IntersectionInfo answer = IntersectionTest().Test(r.Transform(c.GetInverseTransform()), c);
    assert(answer.hasIntesected);
    assert(transform(c.GetTransform(), answer.point) == glm::vec3(0.5f, 0.0f, 0.0f));
}
void testRayCircle2() {
    Ray r = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
    };
    Sphere c = {
        1.0f,
        Material(),
    };
    c.SetTransform(glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.f)));
    
    IntersectionInfo answer = IntersectionTest().Test(r.Transform(c.GetInverseTransform()), c);
    assert(answer.hasIntesected);
    assert(transform(c.GetTransform(), answer.point) == glm::vec3(0.0f, 0.0f, 0.0f));
}
void testRayCircle3() {
    Ray r = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),
    };
    Sphere c = {
        1.0f,
        Material(),
    };
    c.SetTransform(glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.f)));
    
    IntersectionInfo answer = IntersectionTest().Test(r.Transform(c.GetInverseTransform()), c);
    assert(answer.hasIntesected);
    assert(transform(c.GetTransform(), answer.point) == glm::vec3(0.0f, 0.0f, 0.0f));
}
void testRayCircle4() {
    Ray r = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),
    };
    Sphere c = {
        1.0f,
        Material(),
    };
    c.SetTransform(glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 0.0f, 0.f)));
    
    IntersectionInfo answer = IntersectionTest().Test(r.Transform(c.GetInverseTransform()), c);
    assert(!answer.hasIntesected);
}
void testRayCircle5() {
    Ray r = {
        glm::vec3(1.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
    };
    Sphere c = {
        1.0f,
        Material(),
    };
    c.SetTransform(glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 1.5f, 0.0f)));
    
    IntersectionInfo answer = IntersectionTest().Test(r.Transform(c.GetInverseTransform()), c);
    assert(answer.hasIntesected);
    assert(transform(c.GetTransform(), answer.point) == glm::vec3(1.0f, 2.5f, 0.0f));
}

void testRayTriangle1() {
    Ray r = {
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 0.0f, +1.0f),
    };
    Triangle t = {
        glm::vec3(-1.0f, -1.0f, 0.0f),
        glm::vec3(+1.0f, -1.0f, 0.0f),
        glm::vec3(+0.0f, +1.0f, 0.0f),
        Material(),
    };
    IntersectionInfo answer = IntersectionTest().Test(r, t);
    assert(answer.hasIntesected);
    assert(answer.point == glm::vec3(0.0f, 0.0f, 0.0f));
}
void testRayTriangle2() {
    Ray r = {
        glm::vec3(0.0f, -0.5f, -2.0f),
        glm::vec3(0.0f, +0.0f, +1.0f),
    };
    Triangle t = {
        glm::vec3(-1.0f, -1.0f, 0.0f),
        glm::vec3(+1.0f, -1.0f, 0.0f),
        glm::vec3(+0.0f, +1.0f, 0.0f),
        Material(),
    };
    IntersectionInfo answer = IntersectionTest().Test(r, t);
    assert(answer.hasIntesected);
    assert(answer.point == glm::vec3(0.0f, -0.5f, 0.0f));
}
void testRayTriangle3() {
    Ray r = {
        glm::vec3(-1.0f, -0.5f, -2.0f),
        glm::vec3(0.0f, +0.0f, +1.0f),
    };
    Triangle t = {
        glm::vec3(-1.0f, -1.0f, 0.0f),
        glm::vec3(+1.0f, -1.0f, 0.0f),
        glm::vec3(+0.0f, +1.0f, 0.0f),
        Material(),
    };
    IntersectionInfo answer = IntersectionTest().Test(r, t);
    assert(!answer.hasIntesected);
}
void testRayTriangle4() {
    Ray r = {
        glm::vec3(0.0f, +0.0f, +2.0f),
        glm::vec3(0.0f, +0.0f, +1.0f),
    };
    Triangle t = {
        glm::vec3(-1.0f, -1.0f, 0.0f),
        glm::vec3(+1.0f, -1.0f, 0.0f),
        glm::vec3(+0.0f, +1.0f, 0.0f),
        Material(),
    };
    IntersectionInfo answer = IntersectionTest().Test(r, t);
    assert(!answer.hasIntesected);
}

void runTests()
{
    testRayContructor1();
    
    testRayCircle1();
    testRayCircle2();
    testRayCircle3();
    testRayCircle4();
    testRayCircle5();

    testRayTriangle1();
    testRayTriangle2();
    testRayTriangle3();
    testRayTriangle4();
}
