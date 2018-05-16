//
//  SelectionGui.cpp
//  LEDAnimator
//
//  Created by Chris Lynden on 09/05/2018.
//
//


#include "ofApp.h"


void ofApp::makeSelectionPanelGui() {
    
    selectPanel = gui.addPanel(" Selection");
    selectPanel->loadTheme("../../src/primaryTheme.json", true);
    selectPanel->setPosition(20, 20);
    selectPanel->setHidden(false);
    selectPanel->setWidth(270.0);
    
    //
    
    selectPanel->addSpacer(0, 5);
    
    selectAll.set("Select All LED's", false);
    selectPanel->add<ofxGuiButton>(selectAll, ofJson({{"type", "fullsize"}, {"text-align", "center"}}));
    
    selectPanel->addSpacer(0, 5);
    
    //
    
    selectRangeGroup = selectPanel->addGroup("Range Selection");
    
    selectRange.set("Select Strip/Range", false);
    selectRangeGroup->add<ofxGuiButton>(selectRange, ofJson({{"type", "fullsize"}, {"text-align", "center"}}));
    
    rangeStart.set("Range", 0, 0, 30);
    rangeEnd.set(30);
    selectRangeGroup->add<ofxGuiIntRangeSlider>(rangeStart, rangeEnd);
    
    selectPanel->addSpacer(0, 5);
    
    //
    
    selectPatternGroup = selectPanel->addGroup("Pattern Selection");
    
    selectPattern.set("Select Pattern", false);
    selectPatternGroup->add<ofxGuiButton>(selectPattern, ofJson({{"type", "fullsize"}, {"text-align", "center"}}));
    
    groupSize.set("Groups of", 2, 1, 30);
    selectPatternGroup->add(groupSize);
    
    gapSize.set("at intervals of", 3, 0, 30);
    selectPatternGroup->add(gapSize);
    
    selectPanel->addSpacer(0, 5);
    
    //
    
    nudgeSelectionUp.set("Nudge Selection Up", false);
    selectPanel->add<ofxGuiButton>(nudgeSelectionUp, ofJson({{"type", "radio"}, {"text-align", "center"}}));
    
    nudgeSelectionDown.set("Nudge Selection Down", false);
    selectPanel->add<ofxGuiButton>(nudgeSelectionDown, ofJson({{"type", "radio"}, {"text-align", "center"}}));
    
    selectPanel->addSpacer(0, 5);
    
    invertSelection.set("Invert Selection", false);
    selectPanel->add<ofxGuiButton>(invertSelection, ofJson({{"type", "radio"}, {"text-align", "center"}}));
    
    selectPanel->addSpacer(0, 5);
    
    //
    
    clearSelection.set("Clear Selection", false);
    selectPanel->add<ofxGuiButton>(clearSelection, ofJson({{"type", "fullsize"}, {"text-align", "center"}}));
    
    ///////////////
    
    stripSelectionPanel = gui.addPanel(" Strip Selectors", ofJson({
        {"flex", 1},
        {"border-width", 0},
        {"show-header", false},
        {"flex-direction", "row"},
        {"padding", 0},
        {"text-padding", 0},
        {"margin", 0},
        {"flex-wrap", "nowrap"}
    }));
    stripSelectionPanel->loadTheme("../../src/primaryTheme.json", true);
    stripSelectionPanel->setPosition(visXPos, visYPos-25);
    stripSelectionPanel->setHidden(false);
    //stripSelectionPanel->showHeader(false);
    stripSelectionPanel->setWidth(visXSize);
    
    
    for(int i = 0; i < numStrips; i++) {
        ofParameter <bool> oneSelector;
        oneSelector.set(ofToString(i), true);
        stripSelectors.push_back(oneSelector);
        stripSelectionPanel->add<ofxGuiToggle>(oneSelector, ofJson({{"type", "fullsize"}, {"text-align", "center"}, {"width", ofToString((visXSize/numStrips)-8)}}));
    }
    
    for(int i = 0; i < numStrips; i++){
        stripSelectorLastStates.push_back(true);
    }
    
    stripSelectorChanged();
    
}
