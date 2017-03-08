//
//  Particles.hpp
//  Particles
//
//  Created by Qin on 2/9/17.
//
//

#ifndef Particle_hpp
#define Particle_hpp

#pragma once
#include "cinder/gl/gl.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Particle
{
public:
    Particle(glm::vec2 startPosition);
    ~Particle();
    void update();
    void draw();
    void applyForce(glm::vec2 force);
    void bounceForce(float damping, bool isVertical);
    glm::vec2 getPosition(){ return mPosition; }
private:
    
    float	  mFriction;
    glm::vec2 mPosition;
    glm::vec2 mVelocity;
    glm::vec2 mAcceleration;
    cinder::gl::TextureRef mTex;
    glm::vec2 size;
    
};


#endif /* Particle_hpp */
