//
//  VideoGui.cpp
//  LEDAnimator
//
//  Created by Chris Lynden on 09/05/2018.
//
//


#include "ofApp.h"


void ofApp::makeVideoPanelGui() {
    videoPanel = gui.addPanel(" Video Mapper");
    videoPanel->loadTheme("../../src/primaryTheme.json", true);
    videoPanel->setPosition(890, 20);
    videoPanel->setHidden(false);
    videoPanel->setWidth(270.0);
    
    videoPanel->addSpacer(0, 5);
    
    loadVideo.set("Load Video File", false);
    videoPanel->add<ofxGuiButton>(loadVideo, ofJson({{"type", "fullsize"}, {"text-align", "center"}}));
}
