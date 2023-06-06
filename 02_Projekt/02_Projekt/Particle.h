#ifndef PARTICLE_H
#define PARTICLE_H
#include<vector>
#include "Vector3f.h"
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#pragma once
class Particle
{
private:
    Vector3f x, v, f;
    float m;
    float radius;
        
public:
    Particle() { m = 0.0f; }
    Particle(Vector3f x_, Vector3f v_, Vector3f f_, float m_, float r_) : x(x_), v(v_), f(f_), m(m_), radius(r_){ }
    std::vector<Vector3f> getState();
    Vector3f getPos() { return x; }
    Vector3f getV() { return v; }
    float getRadius() { return radius; }
    std::vector<Vector3f> update(float deltaT);
    void draw();
    void setState(Vector3f x_, Vector3f v_) { this->x = x_; this->v = v_; }
    std::vector<Vector3f> derivEval();
    ~Particle(){}
};
#endif // !PARTICLE_H
