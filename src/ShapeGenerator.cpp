//
//  ShapeGenerator.cpp
//  LEDAnimator
//
//  Created by Chris Lynden on 10/05/2018.
//
//


#include "ofApp.h"


//////////////////////////////////////////////////////////

void ofApp::shapePanelUserInput() {
    
    if(!createShape) {createShapeBlock = false; createShapeHappened = false;}
    if(createShape && !createShapeBlock) {
        if(numSelected > 0) {
            cout<<"Creating Shape"<<endl;
            getCurrentSelection();
            
            Shape newShape;
            newShape.setup(numSelected);
            
            for(int i = 0; i < currentSelection.size(); i++) {
                newShape.targetLeds.push_back(Shape::Selection());
                newShape.targetLeds[i].strip = currentSelection[i].strip;
                newShape.targetLeds[i].index = currentSelection[i].index;
            }
            programmer.memShapes.push_back(newShape);
            
            addToProgrammerContentsPanel(SHAPE);
            activeShapeIndex = programmer.memShapes.size() - 1;
            updateShapeParameters(activeShapeIndex);
            
        }
        createShapeHappened = true;
    }
    if(createShape && createShapeHappened) {createShapeBlock = true;}
    
    
    if(editShapeColor && programmer.memShapes.size() > 0) {
        colorPanel->setBackgroundColor(ofColor(255, 0, 0, 100));
    }
    else {
        colorPanel->setBackgroundColor(ofColor(80, 80, 80, 80));
    }
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

void ofApp::updateShapeParameters(int _index) {
    switch(programmer.memShapes[activeShapeIndex].type) {
        case 0:
            sinShapeType = true;
            cosShapeType = false;
            rampUpShapeType = false;
            rampDownShapeType = false;
            pulseShapeType = false;
            triShapeType = false;
            break;
        case 1:
            sinShapeType = false;
            cosShapeType = true;
            rampUpShapeType = false;
            rampDownShapeType = false;
            pulseShapeType = false;
            triShapeType = false;
            break;
        case 2:
            sinShapeType = false;
            cosShapeType = false;
            rampUpShapeType = true;
            rampDownShapeType = false;
            pulseShapeType = false;
            triShapeType = false;
            break;
        case 3:
            sinShapeType = false;
            cosShapeType = false;
            rampUpShapeType = false;
            rampDownShapeType = true;
            pulseShapeType = false;
            triShapeType = false;
            break;
        case 4:
            sinShapeType = false;
            cosShapeType = false;
            rampUpShapeType = false;
            rampDownShapeType = false;
            pulseShapeType = true;
            triShapeType = false;
            break;
        case 5:
            sinShapeType = false;
            cosShapeType = false;
            rampUpShapeType = false;
            rampDownShapeType = false;
            pulseShapeType = false;
            triShapeType = true;
            break;
    }
    speedSlider = programmer.memShapes[activeShapeIndex].speed;
    stepSpreadSlider = programmer.memShapes[activeShapeIndex].stepSpread;
    chunkSizeSlider = programmer.memShapes[activeShapeIndex].chunkSize;
    widthSlider = programmer.memShapes[activeShapeIndex].width;
    offsetSlider = programmer.memShapes[activeShapeIndex].offset;
    shapeMin = programmer.memShapes[activeShapeIndex].minVal;
    shapeMax = programmer.memShapes[activeShapeIndex].maxVal;
    shapeDirection = programmer.memShapes[activeShapeIndex].direction;
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////


void ofApp::shapeTypeChanged(int &_index) {
    if(programmer.memShapes.size() > 0) {
        programmer.memShapes[activeShapeIndex].setType(_index);
    }
}
void ofApp::shapeSpeedChanged(float &speedSlider) {
    if(programmer.memShapes.size() > 0) {
        programmer.memShapes[activeShapeIndex].setSpeed(speedSlider);
    }
}
void ofApp::shapeSpreadChanged(int &stepSpreadSlider) {
    if(programmer.memShapes.size() > 0) {
        programmer.memShapes[activeShapeIndex].setSpread(stepSpreadSlider);
    }
}
void ofApp::chunkSizeChanged(int &chunkSizeSlider) {
    if(programmer.memShapes.size() > 0) {
        programmer.memShapes[activeShapeIndex].setChunkSize(chunkSizeSlider);
    }
}
void ofApp::shapeWidthChanged(float &widthSlider) {
    if(programmer.memShapes.size() > 0) {
        programmer.memShapes[activeShapeIndex].setWidth(widthSlider);
    }
}
void ofApp::shapeOffsetChanged(float &offsetSlider) {
    if(programmer.memShapes.size() > 0) {
        programmer.memShapes[activeShapeIndex].setOffset(offsetSlider);
    }
}
void ofApp::shapeMinChanged(int &minValSlider) {
    if(programmer.memShapes.size() > 0) {
        programmer.memShapes[activeShapeIndex].setMin(shapeMin);
    }
}
void ofApp::shapeMaxChanged(int &maxValSlider) {
    if(programmer.memShapes.size() > 0) {
        programmer.memShapes[activeShapeIndex].setMax(shapeMax);
    }
}
void ofApp::shapeDirChanged(bool &shapeDirection) {
    if(programmer.memShapes.size() > 0) {
        programmer.memShapes[activeShapeIndex].setDir(shapeDirection);
    }
}