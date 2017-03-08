#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/gl.h"
#include "cinder/Text.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/TextureFont.h"
#include "cinder/Utilities.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class clockApp : public App {
  public:
	void setup() override;
		void draw() override;
    Font				mFont;
    vec2				center;
    void render();
    gl::TextureRef		mTextTexture;

    
};

void clockApp::setup()
{
    ci::app::setWindowSize(300.f,300.f);
    mFont = Font( "Times New Roman", 50 );
  //  mSize = vec2( 100, 100 );
    center = ci::vec2(0.f,0.4f) * vec2(ci::app::getWindowSize());
}

void clockApp::render()
{
    auto t = std::time(nullptr);
    auto d = std::localtime(&t);
    int clockhr = d->tm_hour;
    int clockmin = d->tm_min;
    int clocksec = d->tm_sec;
    std::string txt("" +std::to_string(clockhr)+":"+std::to_string(clockmin)+":"+std::to_string(clocksec));
    
    TextBox tbox = TextBox().alignment( TextBox::CENTER ).font( mFont ).size( ivec2( 300.f, TextBox::GROW ) ).text(txt);
    tbox.setColor( Color( 1,1,1) );
 
    mTextTexture = gl::Texture2d::create( tbox.render() );
}


void clockApp::draw()
{
 	gl::clear( Color( 0, 0, 0 ) );
    render();
    gl::pushModelView();
    gl::translate(center);
    gl::draw( mTextTexture );
    gl::popModelView();
}


CINDER_APP( clockApp, RendererGl )
