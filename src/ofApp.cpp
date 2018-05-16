#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofBackground(0);
    ofSetColor(255);
    
    serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    int baud = 115200;
    serial.setup(0, baud); //open the first device
    serial.drain();
    
    numStrips = 12;
    numLedsPerStrip = 30;
    totalLeds = 0;
    numSelected = 0;
    
    visXPos = 400;
    visYPos = 50;
    visXSize = 400;
    visYSize = 600;
    visBackground = ofColor(40, 40, 40);
    
    for(int i = 0; i < numStrips; i++){
        strips.push_back(Strip());
        strips[i].setupMe(30, 100, 100, 500);
        strips[i].length = visYSize - 10;
        strips[i].xPos = visXPos + ((visXSize/numStrips) * i) + ((visXSize/numStrips)/2) - (strips[i].size/2);
        strips[i].yPos = visYPos + 10;
        totalLeds += strips[i].numLeds;
        strips[i].getPositionData();
    }
    
    //makeGui();
    gui.setupFlexBoxLayout();
    makeSelectionPanelGui();
    makeColorPanelGui();
    makeShapePanelGui();
    makeVideoPanelGui();
    makePlaybackPanelGui();
    makeProgrammerContentsPanelGui();
    
    programmer.memIntensity = 255;
    
    successCount = 0;
    started = false;
    
//    programmer.loadVideo("/Users/Chris/dev/of_v0.9.3_osx_release/apps/myApps/LEDAnimator/video/coolhexes.mp4", visXSize, visYSize);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    time = ofGetElapsedTimeMicros();
    
//    userInput();
    selectionPanelUserInput();
    colourPanelUserInput();
    shapePanelUserInput();
    programmerContentsPanelUserInput();
    videoPanelUserInput();
    playbackPanelUserInput();
    
    
    if(programmer.memLedData.size() > totalLeds) {cleanUpMemLedData(&programmer);}
    
    zeroLedData();
    if(visFromOutput) {
        for(int i = 0; i < 8; i++){
            if(playbacks[i].memActive) {
                playbacks[i].update(time);
                updateStripsFromMemory(playbacks[i]);
            }
        }
    }
    if(visFromProgrammer) {
        programmer.update(time);
        updateStripsFromMemory(programmer);
    }
    
    if(programmer.memShapes.size() > 0) {
        currentShapePreview.set(programmer.memShapes[activeShapeIndex].stepData[0]);
    }
    
    //testSerial();
    createMessage();
    transmitMessage();
    
}



//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackgroundGradient(ofColor::lightGrey, ofColor::darkGrey);
    
    ofSetColor(visBackground);
    ofDrawRectangle(visXPos, visYPos, visXSize, visYSize);
    ofSetColor(255);
    
    
    if(programmer.memShapes.size() > 0) {
        int programmerContentsPosX = programmerContentsPanel->getPosition().x;
        int programmerContentsPosY = programmerContentsPanel->getPosition().y;
        programmerContentsPosX += 2;
        programmerContentsPosY += 36;
        programmerContentsPosY += activeShapeIndex * 79;
        ofFill();
        ofSetColor(programmer.memShapes[activeShapeIndex].r, programmer.memShapes[activeShapeIndex].g, programmer.memShapes[activeShapeIndex].b, 150);
        ofDrawRectangle(programmerContentsPosX, programmerContentsPosY, 266, 79);
        ofSetColor(255);
    }
    
    if(dragSelectActive) {
        ofNoFill();
        ofSetColor(255, 255, 255, 50);
        ofDrawRectangle(initialMouseXPos, initialMouseYPos, currentMouseXPos - initialMouseXPos, currentMouseYPos - initialMouseYPos);
        ofFill();
        ofSetColor(255, 255, 255, 15);
        ofDrawRectangle(initialMouseXPos, initialMouseYPos, currentMouseXPos - initialMouseXPos, currentMouseYPos - initialMouseYPos);
    }
    
    for(int i = 0; i < numStrips; i++) {
        strips[i].drawMe();
    }

    
    for(int i = 0; i < programmer.memShapes.size(); i ++ ) {
        programmer.memShapes[i].updateShapeString();
        shapeLabels[i] = programmer.memShapes[i].shapeString;
    }
    
    programmer.memVideo.updateVideoString();
    
}

void ofApp::zeroLedData() {
    for(int i = 0; i < numStrips; i++) {
        for(int j = 0; j < strips[i].numLeds; j++) {
            for(int k = 0; k < 3; k++) {
                strips[i].ledData[(j*3)+k] = 0;
            }
        }
    }
}




//--------------------------------------------------------------
void ofApp::updateStripsFromMemory(Memory _memory) {
    
    //_memory.update(time);
    
//    for(int i = 0; i < numStrips; i++) {
//        for(int j = 0; j < strips[i].numLeds; j++) {
//            for(int k = 0; k < 3; k++) {
//                strips[i].ledData[(j*3)+k] = 0;
//            }
//        }
//    }
    
//    for(int i = 0; i < _memory.memLedData.size(); i++) {
//        strips[_memory.memLedData[i].strip].ledData[(_memory.memLedData[i].index * 3) + 0] = 0;
//        strips[_memory.memLedData[i].strip].ledData[(_memory.memLedData[i].index * 3) + 1] = 0;
//        strips[_memory.memLedData[i].strip].ledData[(_memory.memLedData[i].index * 3) + 2] = 0;
//    }
//    for(int i = 0; i < _memory.memShapes.size(); i++) {
//        for(int j = 0; j < _memory.memShapes[i].targetLeds.size(); j++) {
//            strips[_memory.memShapes[i].targetLeds[j].strip].ledData[(_memory.memShapes[i].targetLeds[j].index * 3) + 0] = 0;
//            strips[_memory.memShapes[i].targetLeds[j].strip].ledData[(_memory.memShapes[i].targetLeds[j].index * 3) + 1] = 0;
//            strips[_memory.memShapes[i].targetLeds[j].strip].ledData[(_memory.memShapes[i].targetLeds[j].index * 3) + 2] = 0;
//        }
//    }
    
    for(int i = 0; i < _memory.memLedData.size(); i++) {
        strips[_memory.memLedData[i].strip].ledData[(_memory.memLedData[i].index * 3) + 0] += (_memory.memLedData[i].r) * (_memory.memLedData[i].a/255.0) * (_memory.memIntensity/255.0);
        strips[_memory.memLedData[i].strip].ledData[(_memory.memLedData[i].index * 3) + 1] += (_memory.memLedData[i].g) * (_memory.memLedData[i].a/255.0) * (_memory.memIntensity/255.0);
        strips[_memory.memLedData[i].strip].ledData[(_memory.memLedData[i].index * 3) + 2] += (_memory.memLedData[i].b) * (_memory.memLedData[i].a/255.0) * (_memory.memIntensity/255.0);
    }
    for(int i = 0; i < _memory.memShapes.size(); i++) {
        for(int j = 0; j < _memory.memShapes[i].targetLeds.size(); j++) {
            strips[_memory.memShapes[i].targetLeds[j].strip].ledData[(_memory.memShapes[i].targetLeds[j].index * 3) + 0] += ((_memory.memShapes[i].stepData[j]/255.0) * _memory.memShapes[i].r) * (_memory.memShapes[i].a/255.0) * (_memory.memIntensity/255.0);
            strips[_memory.memShapes[i].targetLeds[j].strip].ledData[(_memory.memShapes[i].targetLeds[j].index * 3) + 1] += ((_memory.memShapes[i].stepData[j]/255.0) * _memory.memShapes[i].g) * (_memory.memShapes[i].a/255.0) * (_memory.memIntensity/255.0);
            strips[_memory.memShapes[i].targetLeds[j].strip].ledData[(_memory.memShapes[i].targetLeds[j].index * 3) + 2] += ((_memory.memShapes[i].stepData[j]/255.0) * _memory.memShapes[i].b) * (_memory.memShapes[i].a/255.0) * (_memory.memIntensity/255.0);
            for(int k = 0; k < 3; k++){
                if(strips[_memory.memShapes[i].targetLeds[j].strip].ledData[(_memory.memShapes[i].targetLeds[j].index * 3) + k] > 255) {
                    strips[_memory.memShapes[i].targetLeds[j].strip].ledData[(_memory.memShapes[i].targetLeds[j].index * 3) + k] = 255; }
                if(strips[_memory.memShapes[i].targetLeds[j].strip].ledData[(_memory.memShapes[i].targetLeds[j].index * 3) + k] < 0) {
                    strips[_memory.memShapes[i].targetLeds[j].strip].ledData[(_memory.memShapes[i].targetLeds[j].index * 3) + k] = 0; }
            }
        }
    }
    
    for(int i = 0; i < numStrips; i++) {
        for(int j = 0; j < strips[i].numLeds; j++) {
            int intensity = _memory.memVideo.getAverageRGBDataFromPixelArea(strips[i].positionData[j].x - visXPos, strips[i].positionData[j].y - visYPos, strips[i].size);
            for(int n = 0; n < 3; n++) {
                strips[i].ledData[(j*3)+n] += (intensity * (_memory.memIntensity/255.0));
            }
        }
    }

    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if(button == 0) {
        cout<<button<<endl;
        cout<<"x: "<<x<<endl;
        cout<<"y: "<<y<<endl;
    }
    if(clickedInVis) {
        dragSelectActive = true;
        if(x > initialMouseXPos && y > initialMouseYPos) {
            for(int i = 0; i < numStrips; i++) {
                for(int j = 0; j < strips[i].numLeds; j++) {
                    if((x >= strips[i].positionData[j].x && y >= strips[i].positionData[j].y) && (initialMouseXPos <= strips[i].positionData[j].x + strips[i].size && initialMouseYPos <= strips[i].positionData[j].y + strips[i].size)) {
                        if(button == 0) {
                            if(strips[i].selectionFlags[j] != true) {
                                numSelected++;
                                strips[i].selectionFlags[j] = true;
                            }
                        }
                        if(button == 2) {
                            if(strips[i].selectionFlags[j] == true) {
                                numSelected--;
                                strips[i].selectionFlags[j] = false;
                            }
                        }
                    }
                }
            }
        }
        
        if(x < initialMouseXPos && y < initialMouseYPos) {
            for(int i = 0; i < numStrips; i++) {
                for(int j = 0; j < strips[i].numLeds; j++) {
                    if((x <= strips[i].positionData[j].x + strips[i].size && y <= strips[i].positionData[j].y + strips[i].size) && (initialMouseXPos >= strips[i].positionData[j].x && initialMouseYPos >= strips[i].positionData[j].y)) {
                        if(button == 0) {
                            if(strips[i].selectionFlags[j] != true) {
                                numSelected++;
                                strips[i].selectionFlags[j] = true;
                            }
                        }
                        if(button == 2) {
                            if(strips[i].selectionFlags[j] == true) {
                                numSelected--;
                                strips[i].selectionFlags[j] = false;
                            }
                        }
                    }
                }
            }
        }
        
        if(x > initialMouseXPos && y < initialMouseYPos) {
            for(int i = 0; i < numStrips; i++) {
                for(int j = 0; j < strips[i].numLeds; j++) {
                    if((x >= strips[i].positionData[j].x && y <= strips[i].positionData[j].y + strips[i].size) && (initialMouseXPos <= strips[i].positionData[j].x + strips[i].size && initialMouseYPos >= strips[i].positionData[j].y)) {
                        if(button == 0) {
                            if(strips[i].selectionFlags[j] != true) {
                                numSelected++;
                                strips[i].selectionFlags[j] = true;
                            }
                        }
                        if(button == 2) {
                            if(strips[i].selectionFlags[j] == true) {
                                numSelected--;
                                strips[i].selectionFlags[j] = false;
                            }
                        }
                    }
                }
            }
        }
        
        if(x < initialMouseXPos && y > initialMouseYPos) {
            for(int i = 0; i < numStrips; i++) {
                for(int j = 0; j < strips[i].numLeds; j++) {
                    if((x <= strips[i].positionData[j].x + strips[i].size && y >= strips[i].positionData[j].y) && (initialMouseXPos >= strips[i].positionData[j].x && initialMouseYPos <= strips[i].positionData[j].y + strips[i].size)) {
                        if(button == 0) {
                            if(strips[i].selectionFlags[j] != true) {
                                numSelected++;
                                strips[i].selectionFlags[j] = true;
                            }
                        }
                        if(button == 2) {
                            if(strips[i].selectionFlags[j] == true) {
                                numSelected--;
                                strips[i].selectionFlags[j] = false;
                            }
                        }
                    }
                }
            }
        }
        currentMouseXPos = x;
        currentMouseYPos = y;
        
    }
    
    
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if(button == 0) {
        cout<<button<<endl;
        cout<<"Cx: "<<x<<endl;
        cout<<"Cy: "<<y<<endl;
    }
    if((x >= visXPos && y <= visXPos + visXSize) && (y >= visYPos && y <= visYPos + visYSize)) {
        clickedInVis = true;
        initialMouseXPos = x;
        initialMouseYPos = y;
        for(int i = 0; i < numStrips; i++) {
            for(int j = 0; j < strips[i].numLeds; j++) {
                if((x >= strips[i].positionData[j].x && x <= strips[i].positionData[j].x + strips[i].size) && (y >= strips[i].positionData[j].y && y <= strips[i].positionData[j].y + strips[i].size)) {
                    if(button == 0) {
                        if(strips[i].selectionFlags[j] != true) {
                            numSelected++;
                            strips[i].selectionFlags[j] = true;
                        }
                    }
                    if(button == 2) {
                        if(strips[i].selectionFlags[j] == true) {
                            numSelected--;
                            strips[i].selectionFlags[j] = false;
                        }
                    }
                }
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    clickedInVis = false;
    dragSelectActive = false;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}


