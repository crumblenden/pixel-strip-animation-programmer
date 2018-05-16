//
//  shapeObj.h
//  emptyExample
//
//  Created by Chris Lynden on 14/02/2018.
//
//

#ifndef __emptyExample__shapeObj__
#define __emptyExample__shapeObj__

#include <stdio.h>
#include <ofMain.h>
#include "osc.h"

class Shape {
public:
    int numSteps;
    int stepSpread;
    int chunkSize;
    float speed;
    float width;
    float offset;
    int direction;
    enum Type {SINE, COSINE, RAMPUP, RAMPDOWN, PULSE, TRIANGLE, RANDOM};
    int random;
    int type;
    float minVal;
    float maxVal;
    int r;
    int g;
    int b;
    int a;
    
    string typeString;
    string altTypeString;
    string speedString;
    
    
    void setup(int _numSteps);
    void update(int _CurrentTimeMicros);
    
    void setSpeed(float _speed);
    void setSpread(int _stepSpread);
    void setChunkSize(int _chunkSize);
    void setWidth(float _width);
    void setOffset(float _offset);
    void setType(int _type);
    void setRandom(int _random);
    void setMin(float _min);
    void setMax(float _max);
    void setDir(int _dir);
    void setRed(int _red);
    void setGreen(int _green);
    void setBlue(int _blue);
    void setAlpha(int _alpha);

    vector<int> stepData;
    Oscillator osc;
    
    struct Selection {
        int strip;
        int index;
    };
    vector<Selection> targetLeds;
    
    string shapeString;
    void updateShapeString();
};

#endif /* defined(__emptyExample__shapeObj__) */
