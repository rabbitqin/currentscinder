#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class imagehwApp : public App {
  public:
	void setup() override;
    void deform (Surface8u *surface, Area area, float maxAngle);
    void mouseMove (MouseEvent event) override;
	void draw() override;
    
    gl::TextureRef mTex;
    float mWidth,mHeight;
    ci::Surface8u mSurface;
};

void imagehwApp::setup()
{
    ci::app::setWindowSize(700,500);
    mWidth = 700.f;
    mHeight = 500.f;
        try{
        mSurface = loadImage(ci::app::loadAsset("1.jpeg"));
          }catch(exception& e){
        ci::app::console()<<e.what()<<std::endl;
    }
}

void imagehwApp::mouseMove (MouseEvent event) {

 deform(&mSurface, mSurface.getBounds(),event.getPos().y);
}


void imagehwApp::deform(Surface8u *surface, Area area, float maxAngle){

    ci::Surface8u inputSurface = surface->clone();
    ci::Surface::Iter inputIter(inputSurface.getIter());
    ci::Surface::Iter outputIter(surface->getIter(area));
    
    float maxDistance = ci::length((glm::vec2)area.getSize());
    
    glm::vec2 mid = (area.getUL() + area.getLR()) / 2;
    
    
    while( inputIter.line() && outputIter.line() ) {
        while( inputIter.pixel() && outputIter.pixel() ) {
                        glm::vec2 current = (glm::vec2)inputIter.getPos() - mid;
            float r = length(current);
            
            float twirlAngle = r / maxDistance * maxAngle;
            float angle = atan2(current.x, current.y);
            glm::vec2 outSameple(r * cos( angle + twirlAngle  ), r * sin( angle + twirlAngle ));
            glm::vec2 out = outSameple - current;
            outputIter.r() = inputIter.rClamped( out.x, out.y );
            outputIter.g() = inputIter.gClamped( out.x, out.y );
            outputIter.b() = inputIter.bClamped( out.x, out.y );
            
        }
    }




}

void imagehwApp::draw()
{
    gl::clear( Color( 0, 0, 0 ) );
    mTex = gl::Texture2d::create( mSurface );
    gl::draw(mTex,Rectf( 0.f,0.f,mWidth,mHeight));
 
}
CINDER_APP(imagehwApp, RendererGl )
