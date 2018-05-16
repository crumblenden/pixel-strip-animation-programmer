//
//  memoryObj.h
//  emptyExample
//
//  Created by Chris Lynden on 19/02/2018.
//
//

#ifndef __emptyExample__memoryObj__
#define __emptyExample__memoryObj__

#include <stdio.h>
#include "shapeObj.h"
#include "ledStrip.h"
#include "videoObj.h"

class Memory {
public:
    
    void update(int _time);
    
    string memName;
    
    struct singleLed {
        int strip;
        int index;
        int r, g, b, a;
    };
    
    vector<singleLed> memLedData;
    
    vector<Shape> memShapes;
    
    int memIntensity;
    
    bool memActive;
    
    void clear();
    
    vector<string> shapeStringList;
    
    Video memVideo;
    
//    ofVideoPlayer memVideo;
//    ofPixels pixels;
//    int vidX, vidY;
//    void loadVideo(string _url, int _visXSize, int _visYSize);
//    int getDataFromVideoPixels(int _x, int _y, int _size);

    
};













#endif /* defined(__emptyExample__memoryObj__) */
