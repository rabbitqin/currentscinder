//
//  Video.hpp
//  MoviePlayer
//
//  Created by Qin on 3/4/17.
//
//

#pragma once

#include "cinder/app/App.h"
#include "cinder/Surface.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/gl.h"
#include "cinder/qtime/QuickTimeGl.h"

class Video;

typedef std::shared_ptr<Video> VideoRef;
typedef ci::signals::Signal<void()> VideoEndedSignal;

class Video{
public:
    static VideoRef create();
    void setPath();
    void loadVideo(const cinder::fs::path &path );
    void update();
    void draw();
    void stop();
    void play();
    void setLoop(bool bIsLoop);
    void onVideoEnded();
    void jump(cinder::vec2 pos);
    bool end();
    float duration();
    
    VideoEndedSignal& getVideoEndedSignal(){return mVideoEndedSignal;}
private:
    Video();
    void setup();
    //void setPath(std::string path);
    
    VideoEndedSignal        mVideoEndedSignal;
    
    ci::gl::TextureRef      mFrameTexture;
    ci::qtime::MovieGlRef   mMovie;
    ci::fs::path            mMoviePath;
    bool     mEnd;
    
};
