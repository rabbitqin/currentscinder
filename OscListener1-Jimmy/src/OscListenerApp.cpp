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

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/System.h"
#include "cinder/Rand.h"
#include "OscSender.h"




using namespace ci;
using namespace ci::app;

#include "OscListener.h"

class OSCListenerApp : public App {
  public:
	void setup();
	void update();
	void draw();
    void keyDown(KeyEvent event);
    
  //listener..............................
	osc::Listener 	listener;
	float 			positionX;
   
    vec2  player1[6];
  
    vec2 star;
    
    vec2 player2[6];

    vec2 move2;
    vec2 move1;
    bool over = false;
    int score1;
    int score2;
    
    //Sender..............................
    int port2;
    std::string host;
    osc::Sender sender;
};

void OSCListenerApp::setup()
{
    //Sender..............................

    port2=2000;
    host=System::getIpAddress();
    sender.setup( "149.31.136.231", port2, true );
    
    //listener..............................
	listener.setup( 3000 );
    for (int i=0; i<5; i++) {
            player2[i]=getWindowCenter();
    }

    //player1=getWindowCenter();
    star=getWindowCenter();
    score1=0;
    score2=0;
}

void OSCListenerApp::update()
{
    
    if(score1==5||score2==5){
        over=true;
        
    }
    
    player2[0]=player2[0]+move2;

    
    
    
    //sender............................
    osc::Message message1;
    message1.setAddress("/cinder/osc/1");
    message1.addFloatArg(player2[0].x);
    message1.addFloatArg(player2[0].y);
    message1.addFloatArg(move2.x);
    message1.addFloatArg(move2.y);
    sender.sendMessage(message1);
    
    console() << score2 << std::endl;

    //score2
//    glm::vec2 diff = player2[0]- star;
//    float lengthDiff = length(diff);
//    if(lengthDiff<20){
//        score2++;
//    }
    //listener....................................
	while( listener.hasWaitingMessages() ) {
        
        osc::Message message;
		listener.getNextMessage( &message );
		
		console() << "New message received" << std::endl;
		console() << "Address: " << message.getAddress() << std::endl;
		console() << "Num Arg: " << message.getNumArgs() << std::endl;
		for (int i = 0; i < message.getNumArgs(); i++) {
//			sconsole() << "-- Argument " << i << std::endl;
//			console() << "---- type: " << message.getArgTypeName(i) << std::endl;
			if( message.getArgType(i) == osc::TYPE_INT32 ) {
				try {
//					console() << "------ value0: "<< message.getArgAsInt32(i) << std::endl;
				}
				catch (...) {
//					console() << "Exception reading argument as int32" << std::endl;
				}
			}
			else if( message.getArgType(i) == osc::TYPE_FLOAT ) {
				try {
//					console() << "------ value1: " << message.getArgAsFloat(i) << std::endl;
				}
				catch (...) {
//					console() << "Exception reading argument as float" << std::endl;
				}
			}
			else if( message.getArgType(i) == osc::TYPE_STRING) {
				try {
//					console() << "------ value2: " << message.getArgAsString(i).c_str() << std::endl;
				}
				catch (...) {
//					console() << "Exception reading argument as string" << std::endl;
				}
			}
		}
        
        if( message.getNumArgs() != 0 && message.getArgType( 0 ) == osc::TYPE_FLOAT ){
            
            star.x = message.getArgAsFloat(0);
            star.y = message.getArgAsFloat(1);
            //star=vec2(starx,stary);
            player1[0].x = message.getArgAsFloat(2);
            player1[0].y = message.getArgAsFloat(3);
            //player1[0]=vec2(player1x,player1y);
            score1=message.getArgAsFloat(4);
             score2=message.getArgAsFloat(5);
             move1.x=message.getArgAsFloat(6);
             move1.y=message.getArgAsFloat(7);
        }
        if(score2<6||score1<6){
        for (int i=0; i<score2; i++) {
            
            player2[i+1]=player2[i]-20.f*move2;
        }
        for (int i=0; i<score1; i++) {
                
                player1[i+1]=player1[i]-20.f*move1;
            }
        }
        
        }
  
}

void OSCListenerApp::keyDown(KeyEvent event){
    if(event.getChar()=='w'){
        move2 = vec2(0.f,-1.f);
    }
    else if (event.getChar()=='s'){
        move2 = vec2(0.f,1.f);
    }
    else if (event.getChar()=='a'){
        move2 = vec2(-1.f,0.f);
    }
    else if (event.getChar()=='d'){
        move2 = vec2(1.f,0.f);
    }
}

void OSCListenerApp::draw()
{
    
	gl::clear();
    if(over==true&&score1==5){
        ci::gl::drawString("player1 win", ci::app::getWindowCenter()-25.f);
    }
    else  if(over==true&&score2==5){
        ci::gl::drawString("player2 win", ci::app::getWindowCenter()-25.f);
    }
    else{
        gl::drawSolidCircle(star, 10.f);
        ci::gl::color(1.f,0.f,0.f);
        for (int i=0; i<score1+1; i++) {
         gl::drawSolidCircle(player1[i], 10.f);
        }
    
         ci::gl::color(0.f,1.f,0.f);
    
        
        for (int i=0; i<score2+1; i++) {
             gl::drawSolidCircle(player2[i], 10.f);
        }
        ci::gl::drawString("player1:" + std::to_string(score1) , vec2(10.f,10.f));
           ci::gl::drawString("player2:" + std::to_string(score2) , vec2(10.f,30.f));
        
        
    }
    
    
    
	gl::color( Color::white() );
//	gl::drawSolidRect( Rectf( vec2(0), vec2(positionX * getWindowWidth(), getWindowHeight())) );
}

CINDER_APP( OSCListenerApp, RendererGl )
