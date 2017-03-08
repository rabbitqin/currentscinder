//
//  Particles.cpp
//  Particles
//
//  Created by Qin on 2/9/17.
//
//

#include "Particle.hpp"
#include "cinder/Rand.h"

Particle::Particle(glm::vec2 startPosition)
{
    // initialize variables
    mPosition = startPosition;
    mVelocity = glm::vec2(0.f, 0.f);
    mAcceleration = glm::vec2(0.f, 0.f);
    mFriction = 0.95f;
    mTex = gl::Texture::create(loadImage(ci::app::loadAsset("snow.png")));
    
}

Particle::~Particle()
{
}

void Particle::update()
{
    
    // add acc to vel
    mVelocity += glm::vec2(ci::randFloat(-0.1f, 0.1f), 0.02f)+mAcceleration;
    // apply mFriction
    mVelocity *= mFriction;
    // apply to mPositions
    mPosition += mVelocity;
    // reset accelration
    mAcceleration *= 0.f;
}

void Particle::bounceForce(float damping, bool isVertical){
    // damping when hit corner
    if (isVertical){
        mVelocity.y = -mVelocity.y * damping;
    }
    else{
        mVelocity.x = -mVelocity.x * damping;
    }
}

void Particle::applyForce(glm::vec2 force)
{
    // apply force to mAcceleration
    mAcceleration += force;
}

void Particle::draw()
{
    gl::draw(mTex,Rectf(mPosition.x-10.f,mPosition.y-20.f,mPosition.x+10.f,mPosition.y));
}
