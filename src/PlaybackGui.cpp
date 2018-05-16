//
//  PlaybackGui.cpp
//  LEDAnimator
//
//  Created by Chris Lynden on 09/05/2018.
//
//


#include "ofApp.h"


void ofApp::makePlaybackPanelGui() {
    playbackPanel = gui.addPanel("Playbacks", ofJson({
        {"show-header", true}
    }));
    playbackPanel->loadTheme("../../src/primaryTheme.json", true);
    playbackPanel->setPosition(324, 693);
    playbackPanel->setHidden(false);
    playbackPanel->setWidth(560);
    playbackPanel->setHeight(150);
    
    playbackGroup = playbackPanel->addGroup("", ofJson({
        {"flex", 1},
        {"show-header", false},
        {"flex-direction", "row"},
        {"flex-wrap", "nowrap"}
    }));
    
    
    for(int i = 0; i < 8; i++){
        playbackParameterGroups[i] = playbackGroup->addGroup("", ofJson({
            {"flex", 1},
            {"show-header", false},
            {"margin", 2},
            {"flex-direction", "column"},
            {"flex-wrap", "nowrap"}
        }));
        playbackParameterGroups[i]->add<ofxGuiButton>(playbackLabels[i].set(ofToString(i+1), false), ofJson({
            {"width", 15},
            {"height", 15},
            {"text-align", "center"},
            {"type", "fullsize"}
        }));
        playbackParameterGroups[i]->add(playbackSliders[i].set("", 0, 0, 255), ofJson({
            {"width", 15},
            {"height", 60},
            {"text-align", "center"}
        }));
        playbackParameterGroups[i]->add(playbackEditButtons[i].set("Edit", 0, 0, 255), ofJson({
            {"width", 15},
            {"height", 15},
            {"text-align", "center"},
            {"type", "fullsize"}
        }));
        playbackParameterGroups[i]->add<ofxGuiButton>(flashButtons[i].set("Flash", 0, 0, 255), ofJson({
            {"width", 15},
            {"height", 15},
            {"text-align", "center"},
            {"type", "fullsize"}
        }));
    }
    
    playbackControlPanel = gui.addPanel("Playback Control", ofJson({
        {"show-header", false}
    }));
    playbackControlPanel->loadTheme("../../src/primaryTheme.json", true);
    playbackControlPanel->setPosition(884, 693);
    playbackControlPanel->setHidden(false);
    playbackControlPanel->setWidth(100);
    playbackControlPanel->setHeight(206);
    
    playbackControlPanel->add(recordButton.set("Record", false), ofJson({
        {"type", "fullsize"},
        {"text-align", "center"},
        {"fill-color", "rgba(255, 0, 0, 100)"}
    }));
    
    playbackControlPanel->add(includeButton.set("Include", false), ofJson({
        {"type", "fullsize"},
        {"text-align", "center"},
        {"fill-color", "rgba(255, 0, 0, 100)"}
    }));
    
    playbackControlPanel->add(deleteButton.set("Delete", false), ofJson({
        {"type", "fullsize"},
        {"text-align", "center"},
        {"fill-color", "rgba(255, 0, 0, 100)"}
    }));
    
    
    playbackControlPanel->add(optionsButton.set("Options", false), ofJson({
        {"type", "fullsize"},
        {"text-align", "center"},
        {"fill-color", "rgba(255, 0, 0, 100)"}
    }));
    
    visControlPanel = gui.addPanel("vis control", ofJson({
        {"flex", 1},
        {"border-width", 0},
        {"show-header", false},
        {"flex-direction", "row"},
        {"padding", 0},
        {"text-padding", 0},
        {"margin", 0},
        {"flex-wrap", "nowrap"}
    }));
    
    
}
