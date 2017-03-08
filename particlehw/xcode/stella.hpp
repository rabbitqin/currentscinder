

#pragma once

//#include <memory>

class Stella;

typedef std::shared_ptr<Stella> StellaRef;

class Stella {
public:
    static StellaRef create(glm::vec2 position, float lifespan, glm::vec2 acceleration);
    glm::vec2 getPosition(){return mPosition;}
        float getTimerleft();
    float getLifespan(){return mLifespan;};
    void update();
    void applyForce(glm::vec2 force);
    ~Stella();
private:
    Stella();
    void setup(glm::vec2 position, float lifespan, glm::vec2 acceleration);
    
    glm::vec2 mPosition;
    float     mFriction;
    float     mLifespan;
    glm::vec2 mVelocity;
    glm::vec2 mAcceleration;
    
    ci::Timer mTimer;
};
