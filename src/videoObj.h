//
//  videoObj.h
//  LEDAnimator
//
//  Created by Chris Lynden on 10/05/2018.
//
//

#ifndef __LEDAnimator__videoObj__
#define __LEDAnimator__videoObj__

#include <stdio.h>
#include <ofMain.h>

class Video {
public:
    int sourceXSize;
    int sourceYSize;
    
    int destinationXSize;
    int destinationYSize;
    
    int xPos;
    int yPos;
    
    int cropTopLeft;
    int cropTopRight;
    int cropBottomLeft;
    int cropBottomRight;
    
    float speed;
    
    float rotation;
    
    ofVideoPlayer video;
    ofPixels pixels;
    
    string videoString = "Video";
    
    void update();
    
    void loadVideo(string _url);
    void resizeVideo(int _x, int _y);
    int getAverageRGBDataFromPixelArea(int _x, int _y, int _size);
    void updateVideoString();
    
    void clear();
    
    
};






#endif /* defined(__LEDAnimator__videoObj__) */
