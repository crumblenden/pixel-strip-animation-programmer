//
//  ProgrammerGui.cpp
//  LEDAnimator
//
//  Created by Chris Lynden on 09/05/2018.
//
//


#include "ofApp.h"


void ofApp::makeProgrammerContentsPanelGui() {
    programmerContentsPanel = gui.addPanel(" Active Shapes", ofJson({{"width", 270}}));
    programmerContentsPanel->loadTheme("../../src/primaryTheme.json", true);
    programmerContentsPanel->setPosition(890, 510);
    
    
    
    
    visControlPanel->loadTheme("../../src/primaryTheme.json", true);
    visControlPanel->setPosition(visXPos, visYPos+visYSize);
    visControlPanel->setHidden(false);
    visControlPanel->setWidth(visXSize);
    visControlGroup = visControlPanel->addGroup("vis source", ofJson({
        {"flex", 1},
        {"border-width", 0},
        {"show-header", false},
        {"flex-direction", "row"},
        {"padding", 0},
        {"text-padding", 0},
        {"margin", 0},
        {"flex-wrap", "nowrap"}
    }));
    //
    visFromProgrammer.set("Show Programmer", true);
    visControlGroup->add(visFromProgrammer, ofJson({
        {"type", "fullsize"},
        {"text-align", "center"},
        {"width", (visXSize-20)/2}
    }));
    visFromOutput.set("Show Output", false);
    visControlGroup->add(visFromOutput, ofJson({
        {"type", "fullsize"},
        {"text-align", "center"},
        {"width", (visXSize-20)/2}
    }));
    visControlGroup->setExclusiveToggles(true);

}
