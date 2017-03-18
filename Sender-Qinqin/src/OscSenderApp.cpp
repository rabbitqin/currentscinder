/*
 Copyright (c) 2010, Hector Sanchez-Pajares
 Aer Studio http://www.aerstudio.com
 All rights reserved.
 
 
 This is a block for OSC Integration for Cinder framework developed by The Barbarian Group, 2010
 
 Redistribution and use in source and binary forms, with or without modification, are permitted provided that
 the following conditions are met:
 
 * Redistributions of source code must retain the above copyright notice, this list of conditions and
 the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
 the following disclaimer in the documentation and/or other materials provided with the distribution.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.
 */

/*
 Based on addon ofxOsc for openFrameworks
 by Damian Stewart
 http://addons.openframeworks.cc/projects/show/ofxosc
 http://frey.co.nz/old/projects/ofxosc/
 
 */

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/System.h"
#include "OscSender.h"
#include "cinder/Rand.h"
#include "cinder/Vector.h"
#include  "math.h"
#include "OscListener.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class OSCSenderApp : public App {
  public:
	void setup();
	void update();
	void draw();
    void keyDown(KeyEvent event);

    
    osc::Listener 	listener;
	osc::Sender sender;
	float 		positionX;
	std::string host;
	int 		port;
    vec2        star;
    vec2 player1 [6];
    vec2 player2 [6];
    vec2        move;
    vec2        move2;
    int        over;
    int        over2;
    int         score1;
    int         score2;
    vec2        pos;
  //  bool        win1;

};

void OSCSenderApp::setup()
{
    star = vec2(ci::randFloat(50.f, getWindowWidth()-50.f),ci::randFloat(50.f, getWindowWidth()-50.f));
    
    for(int i=0;i<5;i++){
    player1[i]=getWindowCenter();
    player2[i]=getWindowCenter();
    }
    
    over = 0;
    
    over2=0;
    
    score1 = 0;
    
    score2 = 0;
    
    //win1 = false;
    
    //pos = vec2(0.f,0.f);
    
    move = vec2(0.f,0.f);
    
     move2 = vec2(0.f,0.f);
    
	port = 3000;
    
    listener.setup( 2000 );
    
    host = System::getIpAddress();
	if( host.rfind( '.' ) != string::npos )
		host.replace( host.rfind( '.' ) + 1, 3, "255" );
	sender.setup( "149.31.137.185", port, true );
    
}

void OSCSenderApp::keyDown(KeyEvent event){
if(event.getChar() == 'w')
{
    move = vec2(0.f,-1.f);
}
    else if(event.getChar() == 's')
    {
        move = vec2(0.f,1.f);
    }
    else if(event.getChar() == 'a')
    {
        move = vec2(-1.f,0.f);
    }
    else if(event.getChar() == 'd')
    {
      move = vec2(1.f,0.f);
    }

}


void OSCSenderApp::update()
{
    //listen to player2
    while( listener.hasWaitingMessages() ) {
        osc::Message message;
        listener.getNextMessage( &message );
        
        console() << "New message received" << std::endl;
        console() << "Address: " << message.getAddress() << std::endl;
        console() << "Num Arg: " << message.getNumArgs() << std::endl;
        for (int i = 0; i < message.getNumArgs(); i++) {
            console() << "-- Argument " << i << std::endl;
            console() << "---- type: " << message.getArgTypeName(i) << std::endl;
            if( message.getArgType(i) == osc::TYPE_INT32 ) {
                try {
                    console() << "------ value: "<< message.getArgAsInt32(i) << std::endl;
                }
                catch (...) {
                    console() << "Exception reading argument as int32" << std::endl;
                }
            }
            else if( message.getArgType(i) == osc::TYPE_FLOAT ) {
                try {
                    console() << "------ value: " << message.getArgAsFloat(i) << std::endl;
                }
                catch (...) {
                    console() << "Exception reading argument as float" << std::endl;
                }
            }
            else if( message.getArgType(i) == osc::TYPE_STRING) {
                try {
                    console() << "------ value: " << message.getArgAsString(i).c_str() << std::endl;
                }
                catch (...) {
                    console() << "Exception reading argument as string" << std::endl;
                }
            }
        }
        
        if( message.getNumArgs() != 0 && message.getArgType( 0 ) == osc::TYPE_FLOAT )
            player2[0].x = message.getArgAsFloat(0);
            player2[0].y = message.getArgAsFloat(1);
            move2.x = message.getArgAsFloat(2);
            move2.y = message.getArgAsFloat(3);
    }
    
 
    if(score1<6){
    for(int i=0;i<score1+1;i++){
        player1[i]=player1[i]+move;
        player1[i+1]=player1[i]-move*20.f;
    }
        

        for(int i=0;i<score2+1;i++){
            player2[i]=player2[i]+move2;
            player2[i+1]=player2[i]-move2*20.f;
        }
    
    
    float d = ci::length(player1[0]-star);
    if(d<20.f){
        score1++;
        player1[score1]=player1[score1-1]-move*20.f;
        star = vec2(ci::randFloat(50.f, getWindowWidth()-50.f),ci::randFloat(50.f, getWindowHeight()-50.f));
    }
        
        
    float d2 = ci::length(player2[0]-star);
    if(d2<20.f){
            score2++;
            player2[score2]=player2[score2-1]-move2*20.f;
        star = vec2(ci::randFloat(50.f, getWindowWidth()-50.f),ci::randFloat(50.f, getWindowHeight()-50.f));
    }
        
        
    
    if(player1[0].x<10.f||player1[0].x>getWindowWidth()-10.f||player1[0].y<10.f||player1[0].y>getWindowHeight()-10.f)
    {
        over = 1;
    }
        if(player2[0].x<10.f||player2[0].x>getWindowWidth()-10.f||player2[0].y<10.f||player2[0].y>getWindowHeight()-10.f)
        {
            over2 = 1;
        }

   
    }
   

    osc::Message p1;
    p1.setAddress("/cinder/osc/1");
    p1.addFloatArg(star.x);
    p1.addFloatArg(star.y);
    p1.addFloatArg(player1[0].x);
    p1.addFloatArg(player1[0].y);
    p1.addFloatArg(score1);
    p1.addFloatArg(score2);
    p1.addFloatArg(move.x);
    p1.addFloatArg(move.y);
    sender.sendMessage(p1);
}



void OSCSenderApp::draw()
{
	gl::clear();
    if(over==1||score2==5){
     ci::gl::drawString("Player2 wins!",cinder::app::getWindowCenter()-25.f);
    }
    else if(score1==5||over2==1){
    ci::gl::drawString("Player1 wins!",cinder::app::getWindowCenter()-25.f);
    }
    else{
        gl::color( 0.f,0.f,1.f );
     gl::drawSolidCircle(star,10.f);
        gl::color( 1.f,0.f,0.f );
        for(int i=0;i<score1+1;i++){
       gl::drawSolidCircle(player1[i], 10.f);
        }
        //draw player2
        gl::color( 0.f,1.f,0.f );
        for(int i=0;i<score2+1;i++){
            gl::drawSolidCircle(player2[i], 10.f);
        }
        ci::gl::drawString("The first one to get score 5 will win and if you hit the wall you die",vec2(10.f,10.f));
        ci::gl::drawString("Player1: "+to_string(score1),vec2(10.f,30.f));
        ci::gl::drawString("Player2: "+to_string(score2),vec2(10.f,50.f));
    }
//	gl::color( Color::gray( 0.5f ) );

}

CINDER_APP( OSCSenderApp, RendererGl )
