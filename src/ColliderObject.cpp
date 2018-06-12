//
//  ColliderObject.cpp
//  raytracer_demo
//
//  Created by Pavlo Liasota on 6/4/18.
//  Copyright © 2018 none. All rights reserved.
//

#include "ColliderObject.hpp"


CollisionObject::CollisionObject()
    : m_trans(1.0f), m_transInv(1.0f), m_transNorm(1.0f)
{}
CollisionObject::~CollisionObject()
{}

glm::mat4 CollisionObject::GetTransform() const {
    return this->m_trans;
}
glm::mat4 CollisionObject::GetInverseTransform() const {
    return this->m_transInv;
}
glm::mat4 CollisionObject::GetNormalTransform() const {
    return this->m_transNorm;
}

void CollisionObject::SetTransform(glm::mat4 trans) {
    m_trans = trans;
    m_transInv = glm::inverse(trans);
    m_transNorm = glm::transpose(glm::inverse(trans));
}

Ray Ray::FromTo(glm::vec3 from, glm::vec3 to)
{
    Ray answer = {
        from,
        glm::normalize(to - from),
    };
    return answer;
}
glm::vec3 Ray::GetPoint(float t) const {
    return p0 + p1*t;
}
Ray Ray::Transform(glm::mat4 trans) const {
    return {
        trans * glm::vec4(p0, 1.0f),
        trans * glm::vec4(p1, 0.0f)
    };
}

Sphere::Sphere(float radius, Material mat, glm::vec3 center)
    : c(center),
    r(radius)
{
    this->mat = mat;
}
glm::vec3 Sphere::GetNormal(glm::vec3 point) const
{
    return glm::normalize(point - this->c);
}

Triangle::Triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, Material mat)
    : a(a),
    b(b),
    c(c)
{
    this->mat = mat;
}
glm::vec3 Triangle::GetNormal(glm::vec3 ) const {
    return glm::normalize(glm::cross(c-a, b-a));
}
