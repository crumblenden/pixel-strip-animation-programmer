//
//  Playbacks.cpp
//  LEDAnimator
//
//  Created by Chris Lynden on 10/05/2018.
//
//

#include "ofApp.h"


void ofApp::playbackPanelUserInput() {
    if(recordButton) {
        for(int i = 0; i < 8; i++){
            if(playbackLabels[i]){
                playbacks[i] = programmer;
                recordButton = false;
            }
        }
    }
    
    if(deleteButton) {
        for(int i = 0; i < 8; i++){
            if(playbackLabels[i]){
                Memory empty;
                playbacks[i] = empty;
                deleteButton = false;
            }
        }
    }
    
    //    if(includeButton) {
    //        for(int i = 0; i < 8; i++){
    //            if(playbackLabels[i]){
    //                programmer = playbacks[i];
    //                includeButton = false;
    //            }
    //        }
    //    }
    
    for(int i = 0; i < 8; i++) {
        if(flashButtons[i]) {
            playbacks[i].memIntensity = 255;
        } else {
            playbacks[i].memIntensity = playbackSliders[i];
        }
        if(playbacks[i].memIntensity > 0) {
            playbacks[i].memActive = true;
        }
    }
}


