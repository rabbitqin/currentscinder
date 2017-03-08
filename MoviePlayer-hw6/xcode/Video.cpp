//
//  Video.cpp
//  MoviePlayer
//
//  Created by Qin on 3/4/17.
//
//
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "Video.hpp"

VideoRef Video::create(){
    VideoRef ref = std::shared_ptr<Video>(new Video());
    ref->setup();
    return ref;
}

Video::Video()
{
}

void Video::setup()
{
    
}
void Video::setPath()
{
    try {
        cinder::fs::path moviePath = cinder::app::getOpenFilePath();
        if( ! moviePath.empty() )
            loadVideo( moviePath );
        //mMoviePath = ci::app::getAssetPath("1.m4v");
    } catch (std::exception& e) {
        ci::app::console() << e.what() << std::endl;
    }
}

void Video::jump(cinder::vec2 pos){
 mMovie->seekToTime( mMovie->getDuration()*pos.x/cinder::app::getWindowWidth());
}

void Video::loadVideo(const cinder::fs::path &moviePath )
{
    //setPath(videoPath);
    try {
        mMovie = ci::qtime::MovieGl::create( moviePath );
        mMovie->setLoop();
        //mMovie->play();
        mMovie->getEndedSignal().connect(std::bind(&Video::onVideoEnded, this));
    }
    catch( std::exception& e ) {
        ci::app::console() << e.what() << std::endl;
        mMovie.reset();
    }
    mFrameTexture.reset();
}

void Video::update()
{
    if(mMovie){
        mFrameTexture = mMovie->getTexture();
    }
}

void Video::play()
{
    if(mMovie){
        mMovie->play();
    }
}

void Video::stop()
{
    if(mMovie){
        mMovie->stop();
    }
}

void Video::setLoop(bool bIsLoop)
{
    if(mMovie){
        mMovie->setLoop(bIsLoop);
    }
}

float Video::duration(){
    return mMovie->getDuration();
}
void Video::onVideoEnded()
{
    mVideoEndedSignal.emit();
    mEnd = true;
}

bool Video::end(){
    return mEnd;
}

void Video::draw()
{
    if(mFrameTexture&&(mEnd==false)){
        ci::Rectf centeredRect = ci::Rectf( mFrameTexture->getBounds() ).getCenteredFit(ci::app::getWindowBounds(), true );
        ci::gl::draw( mFrameTexture, centeredRect );
    }
    if(mEnd){
        mMovie->stop();
        ci::gl::drawString("end",cinder::app::getWindowCenter());
    }
    //mEnd=false;
    
}


