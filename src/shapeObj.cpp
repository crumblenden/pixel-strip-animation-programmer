//
//  shapeObj.cpp
//  emptyExample
//
//  Created by Chris Lynden on 14/02/2018.
//
//

#include "shapeObj.h"

void Shape::setup(int _numSteps) {
    numSteps = _numSteps;
    
    r = 255;
    g = 255;
    b = 255;
    a = 255;
    
    setSpread(8);
    setChunkSize(1);
    setSpeed(1.0);
    setWidth(0.5);
    setType(0);
    setRandom(0);
    setMin(0);
    setMax(255);
    setDir(0);
    
    osc.setup(type, speed, minVal, maxVal);
    osc.phase = 0;
    stepData.clear();
    
    for(int i = 0; i < numSteps; i++) {
        stepData.push_back(0);
    }
    updateShapeString();
}

void Shape::update(int _CurrentTimeMicros) {
    for(int i = 0; i < numSteps; i++) {
        int step = i;
        step -= i % chunkSize;
        stepData[i] = osc.peek(_CurrentTimeMicros, step, stepSpread);
        
    }
    updateShapeString();
}

void Shape::updateShapeString() {
    switch(type) {
        case SINE:
            typeString = "Sine";
            altTypeString = "SIN";
            break;
        case COSINE:
            typeString = "Cosine";
            altTypeString = "COS";
            break;
        case RAMPUP:
            typeString = "Ramp Up";
            altTypeString = "RUP";
            break;
        case RAMPDOWN:
            typeString = "Ramp Down";
            altTypeString = "RDN";
            break;
        case PULSE:
            typeString = "Pulse";
            altTypeString = "PUL";
            break;
        case TRIANGLE:
            typeString = "Triangle";
            altTypeString = "TRI";
            break;
        case RANDOM:
            typeString = "Random";
            altTypeString = "RAN";
            break;
        default:
            cout<<"error in updateShapeString()";
            break;
    }
    speedString = to_string(speed);
    speedString.erase(speedString.length() - 4);
    
    
//    shapeString = "yo";
    shapeString = " " + altTypeString + "  " + speedString + "s  Spread:" + to_string(stepSpread) + "|Chunk:" + to_string(chunkSize) + "";// + ", R:" + to_string(r) + " G:" + to_string(g) + " B:" + to_string(b);
}

void Shape::setSpeed(float _speed){
    speed = _speed;
    osc.period = osc.setPeriod(speed);
}
void Shape::setSpread(int _stepSpread){
    stepSpread = _stepSpread;
}
void Shape::setChunkSize(int _chunkSize){
    chunkSize = _chunkSize;
}
void Shape::setWidth(float _width){
    width = _width;
    osc.width = width;
}
void Shape::setOffset(float _offset) {
    offset = _offset;
    osc.offset = _offset;
}
void Shape::setType(int _type){
    type = _type;
    osc.type = type;
}
void Shape::setRandom(int _random){
    random = _random;
    osc.random = _random;
}
void Shape::setMin(float _min){
    minVal = _min;
    osc.minAmp = minVal;
}
void Shape::setMax(float _max){
    maxVal = _max;
    osc.maxAmp = _max;
}
void Shape::setDir(int _dir){
    direction = _dir;
    osc.direction = _dir;
}
void Shape::setRed(int _red){
    r = _red;
}
void Shape::setGreen(int _green){
    g = _green;
}
void Shape::setBlue(int _blue){
    b = _blue;
}
void Shape::setAlpha(int _alpha){
    a = _alpha;
}