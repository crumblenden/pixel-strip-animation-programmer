//
//  ledStrip.h
//  emptyExample
//
//  Created by Chris Lynden on 31/01/2018.
//
//

#ifndef __emptyExample__ledStrip__
#define __emptyExample__ledStrip__

#include <stdio.h>
#include <ofMain.h>
#include <math.h>

class Strip {
    
public:
    void setupMe(int _numLeds, int _xPos, int _yPos, int _length);
    void drawMe();

    
    int numLeds;
    int xPos;
    int yPos;
    int length;
    int spacing;
    int size;
    int borderSize;
    
    vector<bool> selectionFlags;
    vector<int> ledData;
    
    struct Coordinate{
        int x;
        int y;
    };
    
    vector<Coordinate> positionData;
    void getPositionData();
    
    Strip(){};

};

#endif /* defined(__emptyExample__ledStrip__) */