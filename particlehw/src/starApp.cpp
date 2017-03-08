#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "cinder/Rand.h"
#include "cinder/Perlin.h"
#include "stella.hpp"


using namespace ci;
using namespace ci::app;
using namespace std;

class starApp : public App {
public:
    void setup() override;
    void mouseDown( MouseEvent event ) override;
    void update() override;
    void draw() override;
    
    const int	NUM_PARTICLES = 50;
    const float  RANDOM_RANGE = 10.f;
    // const float  RANDOM_FORCE_RANGE = 2.f;
    const float LIFE_SPAN = 3.f;
    
    std::vector<StellaRef> mParticles;
    // Perlin					 mPerlin;
    float                    mTime;
    float                    mFrequency = 1 / 200.0f;
};

void starApp::setup()
{
}

void starApp::mouseDown( MouseEvent event )
{
    for (int i = 0; i < NUM_PARTICLES; i++){
        mParticles.push_back(Stella::create((glm::vec2)event.getPos(), LIFE_SPAN, glm::vec2(0,1)));
    }
    
}

void starApp::update()
{
    mTime = ci::app::getElapsedSeconds() * 1.f;
    for (auto p = mParticles.begin(); p != mParticles.end();)
    {
        if ( (*p)->getTimerleft() < 0) {
            p = mParticles.erase(p);
        } else {
            ++p;
        }
        
    }
    
}

void starApp::draw()
{
    gl::clear( Color( 0, 0, 0 ) );
    
    gl::ScopedBlendAdditive blend;
    
   
    ci::gl::begin(GL_LINES);
    for (auto& p: mParticles){
        ci::gl::color(ci::ColorA(p->getTimerleft()/p->getLifespan() ,0.3f, 1.f - p->getTimerleft()/p->getLifespan(), p->getTimerleft()/p->getLifespan()));
    
        gl::vertex(p->getPosition());
        p->update();
        gl::vertex(p->getPosition());
    }
    ci::gl::end();
    gl::drawString( to_string( getAverageFps() ), ci::vec2( 20.f, 20.f ), ci::Color( 0.5f, 0.5f, 0.5f ) );
    gl::drawString( "particle count: " + std::to_string(mParticles.size()) , ci::vec2( 20.f, 30.f ), ci::Color( 0.5f, 0.5f, 0.5f ) );
}

CINDER_APP( starApp, RendererGl )
