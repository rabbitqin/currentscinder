#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Timeline.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class uiApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
   
	void update() override;
	void draw() override;
    
    ci::Anim<ci::vec2> pos1;
    ci::Anim<float> mFactor = 1.f;


};

void uiApp::setup()
{
    pos1=vec2(0.f,0.f);
    gl::enableAlphaBlending();
}



void uiApp::mouseDown(MouseEvent event){

    auto myFavoriteLambdaFunction = [&](){
        timeline().apply(&mFactor,1.f, 1.2f,0.1f,ci::EaseInExpo());
        cout<<mFactor<<endl;
    };
    
    auto myFavoriteLambdaFunction1 = [&](){
        timeline().apply(&mFactor,1.2f, 1.4f,0.1f,ci::EaseInExpo());
        cout<<mFactor<<endl;
    };
    
    auto myFavoriteLambdaFunction2 = [&](){
        timeline().apply(&mFactor,1.4f, 1.6f,0.01f,ci::EaseInExpo());
        cout<<mFactor<<endl;
    };
    
    auto myFavoriteLambdaFunction3 = [&](){
        timeline().apply(&mFactor,1.6f, 1.8f,0.01f,ci::EaseInExpo());
        cout<<mFactor<<endl;
    };
    
    auto myFavoriteLambdaFunction4 = [&](){
        timeline().apply(&mFactor,1.8f, 2.0f,0.01f,ci::EaseInExpo());
        cout<<mFactor<<endl;
    };
    
    auto myFavoriteLambdaFunction5 = [&](){
        timeline().apply(&mFactor,2.0f, 2.2f,0.01f,ci::EaseInExpo());
        cout<<mFactor<<endl;
    };
    
    auto myFavoriteLambdaFunction6 = [&](){
        timeline().apply(&mFactor,2.2f, 2.4f,0.01f,ci::EaseInExpo());
        cout<<mFactor<<endl;
    };
    
    auto myFavoriteLambdaFunction7 = [&](){
        timeline().apply(&mFactor,2.4f, 2.6f,0.01f,ci::EaseInExpo());
        cout<<mFactor<<endl;
    };
    
    timeline().apply(&pos1,vec2(150.f,230.f),0.1f,ci::EaseInBack()).finishFn(myFavoriteLambdaFunction);
    timeline().appendTo( &pos1, vec2(200.f,180.f), 0.12f,ci::EaseInBack()).finishFn(myFavoriteLambdaFunction1);
    timeline().appendTo( &pos1, vec2(250.f,280.f), 0.14f,ci::EaseInBack()).finishFn(myFavoriteLambdaFunction2);
    timeline().appendTo( &pos1, vec2(300.f,150.f), 0.16f,ci::EaseInBack()).finishFn(myFavoriteLambdaFunction3);
    timeline().appendTo( &pos1, vec2(360.f,300.f), 0.18f,ci::EaseInBack()).finishFn(myFavoriteLambdaFunction4);
    timeline().appendTo( &pos1, vec2(420.f,130.f), 0.2f,ci::EaseInBack()).finishFn(myFavoriteLambdaFunction5);
    timeline().appendTo( &pos1, vec2(490.f,320.f), 0.22f,ci::EaseInBack()).finishFn(myFavoriteLambdaFunction6);
    timeline().appendTo( &pos1, vec2(560.f,100.f), 0.24f,ci::EaseInBack()).finishFn(myFavoriteLambdaFunction7);
   
}

void uiApp::update()
{
   
}

void uiApp::draw()
{
    gl::clear(Color( 0, 0, 0 ) );
    ci::gl::color(ci::ColorA(randFloat(0.f,1.f) ,0.3f, 1.f - randFloat(0.5f,0.7f), 0.9f));
    gl::drawSolidCircle(pos1, 10.f*mFactor);

}

CINDER_APP( uiApp, RendererGl )
