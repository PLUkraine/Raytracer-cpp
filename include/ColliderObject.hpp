//
//  ColliderObject.hpp
//  raytracer_demo
//
//  Created by Pavlo Liasota on 6/4/18.
//  Copyright © 2018 none. All rights reserved.
//

#ifndef ColliderObject_hpp
#define ColliderObject_hpp

#include <utility>
#include <glm/glm.hpp>

#include "Material.hpp"

class Ray
{
public:
    static Ray FromTo(glm::vec3 from, glm::vec3 to);
    
    glm::vec3 p0, p1;
    
    glm::vec3 GetPoint(float t) const;
    Ray Transform(glm::mat4 trans) const;
};


class CollisionObject
{
private:
    glm::mat4 m_trans;
    glm::mat4 m_transInv;
    glm::mat4 m_transNorm;
public:
    CollisionObject();
    virtual ~CollisionObject();
    Material mat;
    
    
    virtual glm::vec3 GetNormal(glm::vec3 point) const=0;
    glm::mat4 GetTransform() const;
    glm::mat4 GetInverseTransform() const;
    glm::mat4 GetNormalTransform() const;
    
    void SetTransform(glm::mat4 trans);
};

class Sphere : public CollisionObject
{
public:
    glm::vec3 c;
    float r;

    Sphere(float radius, Material mat, glm::vec3 center=glm::vec3(0.0f));
    glm::vec3 GetNormal(glm::vec3 point) const;
};

class Triangle : public CollisionObject
{
public:
    glm::vec3 a;
    glm::vec3 b;
    glm::vec3 c;

    Triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, Material mat);
    glm::vec3 GetNormal(glm::vec3 point) const;
};

#endif /* ColliderObject_hpp */
