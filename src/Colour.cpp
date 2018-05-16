//
//  Colour.cpp
//  LEDAnimator
//
//  Created by Chris Lynden on 09/05/2018.
//
//


#include "ofApp.h"


/////////////////////////////////////////////////////////////
void ofApp::colourPanelUserInput() {
    if(!saveRGBColor && !saveHSBColor) {saveColourBlock = false; saveColourHappened = false;}
    if((saveRGBColor || saveHSBColor) && !saveColourBlock) {
        ofColor c ;
        c.set(redSlider, greenSlider, blueSlider, alphaSlider);
        for(int i = 0; i < 32; i++) {
            if(!storedColorFlags[i]) {
                storedColorButtons[i]->setBackgroundColor(c);
                storedColorFlags[i] = true;
                break;
            }
        }
        saveColourHappened = true;
    }
    if((saveRGBColor || saveHSBColor) && saveColourHappened) {saveColourBlock = true;}
    
    
    for(int i = 0; i < 32; i++) {
        if(*storedColorButtons[i]) {
            setSelectionColorFromStored(i);
        }
    }
}

/////////////////////////////////////////////////////////////
void ofApp::setSelectionColorRGBA(int & param) {
    if(!preventStoringRGBA) {
        int _r = redSlider;
        int _g = greenSlider;
        int _b = blueSlider;
        int _a = alphaSlider;
        
        ofColor tempColor(_r, _g, _b, _a);
        float hue;
        float sat;
        float bri;
        tempColor.getHsb(hue, sat, bri);
        
        preventStoringHSB = true;
        hueSlider = hue;
        saturationSlider = sat;
        brightnessSlider = bri;
        preventStoringHSB = false;
        
        applyColorData(_r, _g, _b, _a);
        HSBSlidersGroup->setBackgroundColor(tempColor);
        RGBSlidersGroup->setBackgroundColor(tempColor);
    }
}

/////////////////////////////////////////////////////////////
void ofApp::setSelectionColorHSB(int & param) {
    if(!preventStoringHSB) {
        ofColor tempColor = ofColor::fromHsb(hueSlider, saturationSlider, brightnessSlider);
        
        int _r = tempColor.r;
        int _g = tempColor.g;
        int _b = tempColor.b;
        int _a = tempColor.a;
        
        preventStoringRGBA = true;
        redSlider = _r;
        greenSlider = _g;
        blueSlider = _b;
        alphaSlider = _a;
        preventStoringRGBA = false;
        
        applyColorData(_r, _g, _b, _a);
        
        HSBSlidersGroup->setBackgroundColor(tempColor);
        RGBSlidersGroup->setBackgroundColor(tempColor);
    }
}

/////////////////////////////////////////////////////////////
void ofApp::setSelectionColorFromStored(int _index) {
    
    for(int i = 0; i < 32; i++) {
        bool param = *storedColorButtons[i];
        if(param) {
            _index = i;
            break;
        }
    }
    cout<<_index<<endl;
    
    ofColor tempColor = storedColorButtons[_index]->getBackgroundColor();
    
    int _r = tempColor.r;
    int _g = tempColor.g;
    int _b = tempColor.b;
    int _a = tempColor.a;
    float hue;
    float sat;
    float bri;
    tempColor.getHsb(hue, sat, bri);
    
    applyColorData(_r, _g, _b, _a);
    
    preventStoringHSB = true;
    hueSlider = hue;
    saturationSlider = sat;
    brightnessSlider = bri;
    preventStoringHSB = false;
    
    preventStoringRGBA = true;
    redSlider = _r;
    greenSlider = _g;
    blueSlider = _b;
    alphaSlider = _a;
    preventStoringRGBA = false;
    
    HSBSlidersGroup->setBackgroundColor(tempColor);
    RGBSlidersGroup->setBackgroundColor(tempColor);
}

/////////////////////////////////////////////////////////////
void ofApp::applyColorData(int _r, int _g, int _b, int _a) {
    if(!editShapeColor) {
        getCurrentSelection();
        int existingMemorySize = programmer.memLedData.size();
        for(int i = 0; i < currentSelection.size(); i++) {
            int s = currentSelection[i].strip;
            int l = currentSelection[i].index;
            programmer.memLedData.push_back(Memory::singleLed());
            programmer.memLedData[existingMemorySize + i].strip = s;
            programmer.memLedData[existingMemorySize + i].index = l;
            programmer.memLedData[existingMemorySize + i].r = _r;
            programmer.memLedData[existingMemorySize + i].g = _g;
            programmer.memLedData[existingMemorySize + i].b = _b;
            programmer.memLedData[existingMemorySize + i].a = _a;
        }
    }
    else {
        programmer.memShapes[activeShapeIndex].r = _r;
        programmer.memShapes[activeShapeIndex].g = _g;
        programmer.memShapes[activeShapeIndex].b = _b;
        programmer.memShapes[activeShapeIndex].a = _a;
    }
}

/////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////