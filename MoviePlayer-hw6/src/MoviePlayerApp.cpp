#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Timeline.h"

#include "Video.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;

class MoviePlayerApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
    void keyDown ( KeyEvent event) override;
	void update() override;
	void draw() override;
    
    void onVideoEnded();
    
    VideoRef mPlayer;
    int      mPlayCount;
    ci::Anim<ci::vec2> seek;

    gl::TextureRef mTex;
    ci::Surface8u mSurface;
    
};

void MoviePlayerApp::setup()
{
    mPlayCount = 0;
    seek = vec2(0.f,10.f);
    mPlayer = Video::create();
    mPlayer->setPath();
    mPlayer->getVideoEndedSignal().connect(std::bind(&MoviePlayerApp::onVideoEnded, this));
    mSurface = loadImage(ci::app::loadAsset("b.png"));
}

void MoviePlayerApp::mouseDown( MouseEvent event )
{
    vec2 location = event.getPos();
    mPlayer->jump(location);
    timeline().clear();
    seek = vec2(location.x,10.f);
}

void MoviePlayerApp::onVideoEnded(){
    ci::app::console() << "video has ended" << std::endl;
    mPlayCount += 1;
}
void MoviePlayerApp::keyDown( KeyEvent event){
    if(event.getChar() == 'p'){
        mSurface = loadImage(ci::app::loadAsset("b.png"));
      
        mPlayer->play();
        timeline().apply(&seek,vec2(getWindowWidth(),10.f),mPlayer->duration()*(1-seek.value().x/getWindowWidth()));}
    if(event.getChar() == 's'){
          mSurface = loadImage(ci::app::loadAsset("b1.png"));
 mPlayer->stop();
        timeline().clear();}
}

void MoviePlayerApp::update()
{
    mPlayer->update();

}

void MoviePlayerApp::draw()
{
	gl::clear( Color( 0.2, 0.7, 0.1 ) );
    mTex = gl::Texture::create(mSurface);
    mPlayer->draw();
    if(!mPlayer->end()){
    gl::draw(mTex, Rectf(getWindowWidth()-40.f, 25.f, getWindowWidth()-10, 55.f));
    gl::drawSolidRect( Rectf(0.f,0.f, seek.value().x,seek.value().y));
    gl::drawString("press 'p' to play 's' to pause and click mouse to move the seekbar", glm::vec2(30.f, 20.f));
    }
}

CINDER_APP( MoviePlayerApp, RendererGl )
