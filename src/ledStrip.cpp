//
//  ledStrip.cpp
//  emptyExample
//
//  Created by Chris Lynden on 31/01/2018.
//
//

#include "ledStrip.h"


void Strip::setupMe(int _numLeds, int _xPos, int _yPos, int _length) {
    numLeds = _numLeds;
    xPos = _xPos;
    yPos = _yPos;
    length = _length;
    spacing = length/numLeds;
    size = spacing*0.5;
    borderSize = 0;
    for(int i = 0; i < numLeds*3; i++) {
        ledData.push_back(0);
    }
    for(int i = 0; i < numLeds; i++) {
        selectionFlags.push_back(false);
    }
}

void Strip::getPositionData(){
    spacing = length/numLeds;
    size = spacing*0.5;
    for(int i = 0; i < numLeds; i++) {
        Coordinate temp;
        temp.x = xPos;
        temp.y = (yPos + (i * spacing));
        positionData.push_back(temp);
    }
}

void Strip::drawMe(){
    spacing = length/numLeds;
    size = spacing*0.5;
    for(int i = 0; i < numLeds; i++) {
        int r = ledData[i*3];
        int g = ledData[(i*3) + 1];
        int b = ledData[(i*3) + 2];
        int LEDyPos = yPos + (i * spacing);
        ofSetColor(100, 100, 100);
        if(selectionFlags[i]) {borderSize = 1;} else {borderSize = 0;}
        ofDrawRectangle(xPos - borderSize, LEDyPos - borderSize, size + (borderSize*2), size + (borderSize*2));
        ofSetColor(r, g, b);
        ofDrawRectangle(xPos, LEDyPos, size, size);
    }
}
