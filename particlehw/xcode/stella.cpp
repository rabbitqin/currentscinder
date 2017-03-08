
#include "stella.hpp"
#include "cinder/Rand.h"

StellaRef Stella::create(glm::vec2 position, float lifespan, glm::vec2 acceleration)
{
    StellaRef ref = std::shared_ptr<Stella>(new Stella());
    ref->setup(position, lifespan, acceleration);
    return ref;
}

Stella::Stella()
:mFriction(0.98)
,mVelocity(glm::vec2(ci::randFloat(-20.f, 20.f), ci::randFloat(-20.f, 20.f)))
,mAcceleration(glm::vec2(0))
{
    
}
Stella::~Stella()
{
    mTimer.stop();
}

float Stella::getTimerleft()
{
    // calculating using the elapsed time and set limit
    return (mLifespan - mTimer.getSeconds());
}

void Stella::setup(glm::vec2 position, float lifespan, glm::vec2 acceleration)
{
    // init all the values
    mLifespan = lifespan;
    mPosition = position;
    mAcceleration  = acceleration;
    mTimer.start();
}

void Stella::update()
{
    mVelocity += mAcceleration;

    mPosition += mVelocity;
    
}

void Stella::applyForce(glm::vec2 force)
{
    mVelocity += mAcceleration;
    //mVelocity += force;
}
