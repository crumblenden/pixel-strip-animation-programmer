//
//  ColourGui.cpp
//  LEDAnimator
//
//  Created by Chris Lynden on 09/05/2018.
//
//


#include "ofApp.h"


void ofApp::makeColorPanelGui() {
    
    colorPanel = gui.addPanel(" Colours");
    colorPanel->loadTheme("../../src/primaryTheme.json", true);
    colorPanel->setPosition(20, 532);
    colorPanel->setHidden(false);
    colorPanel->setWidth(270.0);
    //    colorPanel->setBackgroundColor(ofColor(255, 0, 0, 100));
    
    colorPanel->addSpacer(0, 5);
    
    //
    
    RGBSlidersGroup = colorPanel->addGroup("RGBA");
    
    
    
    redSlider.set("Red", 128, 0, 255);
    RGBSlidersGroup->add(redSlider);
    redSlider.addListener(this, &ofApp::setSelectionColorRGBA);
    
    
    greenSlider.set("Green", 128, 0, 255);
    RGBSlidersGroup->add(greenSlider);
    greenSlider.addListener(this, &ofApp::setSelectionColorRGBA);
    
    blueSlider.set("Blue", 128, 0, 255);
    RGBSlidersGroup->add(blueSlider);
    blueSlider.addListener(this, &ofApp::setSelectionColorRGBA);
    
    alphaSlider.set("Alpha", 255, 0, 255);
    RGBSlidersGroup->add(alphaSlider);
    alphaSlider.addListener(this, &ofApp::setSelectionColorRGBA);
    
    saveRGBColor.set("Save Colour", false);
    RGBSlidersGroup->add<ofxGuiButton>(saveRGBColor, ofJson({{"type", "fullsize"}, {"text-align", "center"}}));
    
    colorPanel->addSpacer(0, 5);
    
    RGBSlidersGroup->minimize();
    
    //
    
    HSBSlidersGroup = colorPanel->addGroup("HSB");
    
    hueSlider.set("Hue", 0, 0, 255);
    HSBSlidersGroup->add(hueSlider);
    hueSlider.addListener(this, &ofApp::setSelectionColorHSB);
    
    saturationSlider.set("Saturation", 255, 0, 255);
    HSBSlidersGroup->add(saturationSlider);
    saturationSlider.addListener(this, &ofApp::setSelectionColorHSB);
    
    brightnessSlider.set("Brightness", 255, 0, 255);
    HSBSlidersGroup->add(brightnessSlider);
    brightnessSlider.addListener(this, &ofApp::setSelectionColorHSB);
    
    saveHSBColor.set("Save Colour", false);
    HSBSlidersGroup->add<ofxGuiButton>(saveHSBColor, ofJson({{"type", "fullsize"}, {"text-align", "center"}}));
    
    
    colorPanel->addSpacer(0, 5);
    
    HSBSlidersGroup->minimize();
    
    //
    
    colorSelectionGroup = colorPanel->addGroup("Select Color");
    for(int i = 0; i < 4; i++){
        colorSelectionRow[i] = colorSelectionGroup->addGroup("", ofJson({
            {"flex", 1},
            {"border-width", 0},
            {"show-header", false},
            {"flex-direction", "row"},
            {"padding", 1},
            {"margin", 0},
            {"flex-wrap", "nowrap"}
        }));
        for(int j = (i*8); j < ((i+1)*8); j++) {
            storedColorButtons[j] = colorSelectionRow[i]->add<ofxGuiButton>(ofToString(j));
            storedColorButtons[j]->setShowName(false);
            storedColorButtons[j]->setSize(21, 21);
            storedColorButtons[j]->setBorderWidth(0);
        }
        //colorSelectionButtons[i]->addListener(this, ofApp::setSelectionColorFromStored);
    }
    
    
    storedColorButtons[0]->setBackgroundColor(ofColor(255, 255, 255, 255));
    storedColorFlags[0] = true;
    storedColorButtons[1]->setBackgroundColor(ofColor(0, 0, 0, 255));
    storedColorFlags[1] = true;
    storedColorButtons[2]->setBackgroundColor(ofColor(255, 0, 0, 255));
    storedColorFlags[2] = true;
    storedColorButtons[3]->setBackgroundColor(ofColor(0, 255, 0, 255));
    storedColorFlags[3] = true;
    storedColorButtons[4]->setBackgroundColor(ofColor(0, 0, 255, 255));
    storedColorFlags[4] = true;
    storedColorButtons[5]->setBackgroundColor(ofColor(0, 255, 255, 255));
    storedColorFlags[5] = true;
    storedColorButtons[6]->setBackgroundColor(ofColor(255, 0, 255, 255));
    storedColorFlags[6] = true;
    storedColorButtons[7]->setBackgroundColor(ofColor(255, 255, 0, 255));
    storedColorFlags[7] = true;
    
}
