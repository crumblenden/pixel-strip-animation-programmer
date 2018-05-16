//
//  Programmer.cpp
//  LEDAnimator
//
//  Created by Chris Lynden on 09/05/2018.
//
//


#include "ofApp.h"


//////////////////////////////////////////////////////////

void ofApp::programmerContentsPanelUserInput() {
    for(int i = 0; i < programmer.memShapes.size(); i ++) {
        if(!shapeRemoveButtons[i]) {removeShapeBlock = false; removeShapeHappened = false;}
        if(shapeRemoveButtons[i] && !removeShapeBlock) {
            removeShapeFromProgrammer(i);
            updateProgrammerContentsPanel();
            removeShapeHappened = true;
        }
        if(shapeRemoveButtons[i] && removeShapeHappened) {removeShapeBlock = true;}
        
        if(shapeEditButtons[i]) {
            activeShapeIndex = i;
            updateShapeParameters(activeShapeIndex);
            
        }
    }
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

void ofApp::addToProgrammerContentsPanel(int _type) {
    if(_type == SHAPE) {
        programmerContentsPanel->addSpacer(0, 5);
        ofParameter<string> tempLabel;
        shapeLabels.push_back(tempLabel);
        shapeLabels[shapeLabels.size()-1] = programmer.memShapes[programmer.memShapes.size()-1].shapeString;
        programmerContentsPanel->add(shapeLabels[shapeLabels.size()-1], ofJson({{"width", 100}}));
        
        ofParameter<bool> tempEditButton;
        shapeEditButtons.push_back(tempEditButton);
        shapeEditButtons[shapeEditButtons.size()-1].set("Edit", false);
        programmerContentsPanel->add<ofxGuiButton>(shapeEditButtons[shapeEditButtons.size()-1], ofJson({{"type", "fullsize"}, {"text-align", "center"}, {"height", 15}}));
        
        ofParameter<bool> tempRemoveButton;
        shapeRemoveButtons.push_back(tempRemoveButton);
        shapeRemoveButtons[shapeRemoveButtons.size()-1].set("Remove", false);
        programmerContentsPanel->add<ofxGuiButton>(shapeRemoveButtons[shapeRemoveButtons.size()-1], ofJson({{"type", "fullsize"}, {"text-align", "center"}, {"height", 15}}));
    }
    if(_type == VIDEO) {
//        programmerContentsPanel->addSpacer(0, 5);
//        ofParameter<string> tempLabel;
//        shapeLabels.push_back(tempLabel);
//        shapeLabels[shapeLabels.size()-1] = programmer.memVideo.videoString;
//        programmerContentsPanel->add(shapeLabels[shapeLabels.size()-1], ofJson({{"width", 100}}));
//        
//        
//        ofParameter<bool> tempEditButton;
//        shapeEditButtons.push_back(tempEditButton);
//        shapeEditButtons[shapeEditButtons.size()-1].set("Edit", false);
//        programmerContentsPanel->add<ofxGuiButton>(shapeEditButtons[shapeEditButtons.size()-1], ofJson({{"type", "fullsize"}, {"text-align", "center"}, {"height", 15}}));
//        
//        ofParameter<bool> tempRemoveButton;
//        shapeRemoveButtons.push_back(tempRemoveButton);
//        shapeRemoveButtons[shapeRemoveButtons.size()-1].set("Remove", false);
//        programmerContentsPanel->add<ofxGuiButton>(shapeRemoveButtons[shapeRemoveButtons.size()-1], ofJson({{"type", "fullsize"}, {"text-align", "center"}, {"height", 15}}));
        
        
    }
}

//////////////////////////////////////////////////////////

void ofApp::updateProgrammerContentsPanel() {
    
    programmerContentsPanel->clear();
    
    for(int i = 0; i < programmer.memShapes.size(); i++) {
        shapeLabels.clear();
        shapeEditButtons.clear();
        shapeRemoveButtons.clear();
        //        shapeEditButtonsLastState.clear();
    }
    for(int i = 0; i < programmer.memShapes.size(); i++) {
        programmerContentsPanel->addSpacer(0, 5);
        ofParameter<string> tempLabel;
        shapeLabels.push_back(tempLabel);
        shapeLabels[i] = programmer.memShapes[i].shapeString;
        programmerContentsPanel->add(shapeLabels[i], ofJson({{"width", 100}}));
        
        ofParameter<bool> tempEditButton;
        shapeEditButtons.push_back(tempEditButton);
        shapeEditButtons[i].set("Edit", false);
        programmerContentsPanel->add<ofxGuiButton>(shapeEditButtons[i], ofJson({{"type", "fullsize"}, {"text-align", "center"}, {"height", 15}}));
        
        ofParameter<bool> tempRemoveButton;
        shapeRemoveButtons.push_back(tempRemoveButton);
        shapeRemoveButtons[i].set("Remove", false);
        programmerContentsPanel->add<ofxGuiButton>(shapeRemoveButtons[i], ofJson({{"type", "fullsize"}, {"text-align", "center"}, {"height", 15}}));
    }
    
}

//////////////////////////////////////////////////////////

void ofApp::removeShapeFromProgrammer(int _index) {
    shapeLabels.erase(shapeLabels.begin() + _index);
    shapeEditButtons.erase(shapeEditButtons.begin() + _index);
    shapeRemoveButtons.erase(shapeRemoveButtons.begin() + _index);
    programmer.memShapes.erase(programmer.memShapes.begin() + _index);
    //    shapeEditButtonsLastState.erase(shapeEditButtonsLastState.begin() + _index);
    if(activeShapeIndex > programmer.memShapes.size() - 1) {
        activeShapeIndex = programmer.memShapes.size() - 1;
    }
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

void ofApp::cleanUpMemLedData(Memory *_mem) {
    vector<Selection> references;
    for(int i = _mem->memLedData.size()-1; i > -1; i --) {
        int tStrip = _mem->memLedData[i].strip;
        int tIndex = _mem->memLedData[i].index;
        
        bool alreadyExists = false;
        for(int j = 0; j < references.size(); j++) {
            if(tStrip == references[j].strip && tIndex == references[j].index) {
                alreadyExists = true;
            }
        }
        
        Selection tSelection;
        tSelection.strip = tStrip;
        tSelection.index = tIndex;
        references.push_back(tSelection);
        
        if(alreadyExists) {
            _mem->memLedData.erase(_mem->memLedData.begin() + i);
        }
    }
}

