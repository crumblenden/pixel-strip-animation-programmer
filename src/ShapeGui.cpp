//
//  ShapeGui.cpp
//  LEDAnimator
//
//  Created by Chris Lynden on 09/05/2018.
//
//


#include "ofApp.h"


void ofApp::makeShapePanelGui() {
    
    shapePanel = gui.addPanel(" Wave Generator");
    shapePanel->loadTheme("../../src/primaryTheme.json", true);
    shapePanel->setPosition(890, 125);
    shapePanel->setHidden(false);
    shapePanel->setWidth(270.0);
    
    shapePanel->addSpacer(0, 5);
    
    //
    
    createShape.set("Generate Wave", false);
    shapePanel->add<ofxGuiButton>(createShape, ofJson({{"type", "fullsize"}, {"text-align", "center"}}));
    
    //
    
    shapeTypeGroup = shapePanel->addGroup("Wave Type");
    
    sinShapeType.set("Sine", true);
    shapeTypeGroup->add(sinShapeType, ofJson({{"type", "radio"}, {"text-align", "center"}}));
    //sinShapeType.addListener(this, &ofApp::shapeTypeChanged);
    
    cosShapeType.set("Cosine", false);
    shapeTypeGroup->add(cosShapeType, ofJson({{"type", "radio"}, {"text-align", "center"}}));
    //cosShapeType.addListener(this, &ofApp::shapeTypeChanged);
    
    rampUpShapeType.set("Ramp Up", false);
    shapeTypeGroup->add(rampUpShapeType, ofJson({{"type", "radio"}, {"text-align", "center"}}));
    //rampUpShapeType.addListener(this, &ofApp::shapeTypeChanged);
    
    rampDownShapeType.set("Ramp Down", false);
    shapeTypeGroup->add(rampDownShapeType, ofJson({{"type", "radio"}, {"text-align", "center"}}));
    //rampDownShapeType.addListener(this, &ofApp::shapeTypeChanged);
    
    pulseShapeType.set("Pulse", false);
    shapeTypeGroup->add(pulseShapeType, ofJson({{"type", "radio"}, {"text-align", "center"}}));
    //pulseShapeType.addListener(this, &ofApp::shapeTypeChanged);
    
    triShapeType.set("Triangle", false);
    shapeTypeGroup->add(triShapeType, ofJson({{"type", "radio"}, {"text-align", "center"}}));
    //triShapeType.addListener(this, &ofApp::shapeTypeChanged);
    
    shapeTypeGroup->setExclusiveToggles(true);
    
    shapeTypeGroup->minimize();
    
    shapeTypeGroup->getActiveToggleIndex().addListener(this, &ofApp::shapeTypeChanged);
    
    //
    
    speedSlider.set("Period", 2.0, 0.05, 8.0);
    shapePanel->add(speedSlider);
    speedSlider.addListener(this, &ofApp::shapeSpeedChanged);
    
    stepSpreadSlider.set("Spread", 10, 1, 30);
    shapePanel->add(stepSpreadSlider);
    stepSpreadSlider.addListener(this, &ofApp::shapeSpreadChanged);
    
    chunkSizeSlider.set("Chunk Size", 1, 1, 30);
    shapePanel->add(chunkSizeSlider);
    chunkSizeSlider.addListener(this, &ofApp::chunkSizeChanged);
    
    widthSlider.set("Width", 0.5, 0.0, 1.0);
    shapePanel->add(widthSlider);
    widthSlider.addListener(this, &ofApp::shapeWidthChanged);
    
    offsetSlider.set("Offset", 0.0, 0.0, 1.0);
    shapePanel->add(offsetSlider);
    offsetSlider.addListener(this, &ofApp::shapeOffsetChanged);
    
    shapeMin.set("Range", 0, 0, 255);
    shapeMax.set(255);
    shapePanel->add<ofxGuiIntRangeSlider>(shapeMin, shapeMax);
    shapeMin.addListener(this, &ofApp::shapeMinChanged);
    shapeMax.addListener(this, &ofApp::shapeMaxChanged);
    
    shapeDirection.set("Direction", true);
    shapePanel->add(shapeDirection, ofJson({{"type", "checkbox"}, {"text-align", "center"}}));
    shapeDirection.addListener(this, &ofApp::shapeDirChanged);
    
    shapePanel->add<ofxGuiValuePlotter>(currentShapePreview.set("Wave Preview", 0, 0, 255), ofJson({{"precision", 0}, {"text-color", "transparent"}}));
    
    
    editShapeColor.set("Edit Wave Colour", false);
    shapePanel->add(editShapeColor, ofJson({{"type", "fullsize"}, {"text-align", "center"}, {"fill-color", "rgba(255, 0, 0, 100)"}}));

}