#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

#include <list>
using std::list;

//static const bool PREMULT = false;

class meterApp : public App {
public:
    void setup() override;
    void keyDown( KeyEvent event ) override;
     void keyUp( KeyEvent event ) override;
    void update() override;
    void draw() override;
    int hold;
    Font				mFont;
    gl::TextureRef	mTextTexture,m1;
    
};

void meterApp::setup()
{
    ci::app::setWindowSize(300.f,120.f);
    hold = 0;
    mFont = Font( "Times New Roman", 20 );
}

void meterApp::keyDown( KeyEvent event )
{
    hold++;
}

void meterApp::keyUp( KeyEvent event )
{
    hold=0;
}


void meterApp::update()
{
}

void meterApp::draw()
{
   
    gl::clear( ci::Color::black() );
    ci::vec2 center = ci::vec2(0.5f,1.f) * vec2(ci::app::getWindowSize());

    gl::color(Color::white());
    
    std::string txt1("press any key");
    TextBox t = TextBox().alignment( TextBox::CENTER ).font( mFont ).size( ivec2( 150.f, TextBox::GROW ) ).text(txt1);

    
    m1 = gl::Texture2d::create( t.render() );
    
    gl::draw(  m1);


    for(int h = 0; h<12; h++){
        gl::pushModelView();
        gl::translate(center);
      
        gl::rotate(h*glm::radians(30.f));
        std::string txt("" +std::to_string(h-6));
        
        TextBox tbox = TextBox().alignment( TextBox::CENTER ).font( mFont ).size( ivec2( 150.f, TextBox::GROW ) ).text(txt);
        tbox.setColor( Color( 1,1,1) );
        
        mTextTexture = gl::Texture2d::create( tbox.render() );
        
        gl::draw(  mTextTexture);
        gl::drawSolidRect(Rectf(-3,-110,3,-90));
        gl::popModelView();
        
        
        
    }
    
    gl::color(ci::Color(1.f,0.f,0.f));


    gl::pushModelView();
    gl::translate(center);

    gl::rotate(10*hold*glm::radians(360.f/3600.f));
    gl::drawSolidRect(Rectf(-100,2,-2,-2));
    gl::popModelView();
    
}



CINDER_APP( meterApp, RendererGl )
