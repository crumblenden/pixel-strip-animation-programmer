//
//  VideoMapper.cpp
//  LEDAnimator
//
//  Created by Chris Lynden on 10/05/2018.
//
//


#include "ofApp.h"



void ofApp::videoPanelUserInput() {
    if(!loadVideo) {loadVideoBlock = false; loadVideoHappened = false;}
    if(loadVideo && !loadVideoBlock) {
        
                ofFileDialogResult openFileResult = ofSystemLoadDialog("Open a video.");
                if(openFileResult.bSuccess){
                    programmer.memVideo.loadVideo(openFileResult.getPath()  );//, visXSize, visYSize);
                    programmer.memVideo.resizeVideo(visXSize, visYSize);
                }
        
        loadVideoHappened = true;
    }
    if(loadVideo && loadVideoHappened) {loadVideoBlock = true;}
}