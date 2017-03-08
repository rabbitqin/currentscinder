//
//  ParticleSystem.hpp
//  Particles
//
//  Created by Qin on 2/9/17.
//
//

#ifndef ParticleSystem_hpp
#define ParticleSystem_hpp

#pragma once
#include "cinder/gl/gl.h"
#include "cinder/app/App.h"
#include "Particle.hpp"

class ParticleSystem
{
public:
    ParticleSystem();
    ~ParticleSystem();
    
    void update();
    void draw();
    void repulseFrom(glm::vec2 position);
    
private:
    void bounceFromeEdge();
    
    int                     mParticleNum;
    std::vector<Particle>   mParticles;
    float			mRange;
    float			mRepulsionFactor;
};



#endif /* ParticleSystem_hpp */
