//
//  videoObj.cpp
//  LEDAnimator
//
//  Created by Chris Lynden on 10/05/2018.
//
//

#include "videoObj.h"

void Video::update() {
    if(video.isLoaded()) {
        video.update();
        pixels = video.getPixels();
        //pixels.resize(destinationXSize, destinationYSize);
    }
}

void Video::clear() {
    if(video.isLoaded()) {
        video.closeMovie();
    }
}

void Video::loadVideo(string _url) {
    video.load(_url);
    video.setLoopState(OF_LOOP_NORMAL);
    video.play();
}

int Video::getAverageRGBDataFromPixelArea(int _x, int _y, int _size) {
    int intensity = 0;
    if(video.isLoaded()){
        for(int i = 0; i < _size; i++) {
            for(int j = 0; j < _size; j++) {
                int index = pixels.getPixelIndex(_x + j, _y + i);
                int alpha = 0;
                for(int k = 0; k < 3; k++) {
                    alpha += pixels[index+k];
                }
                alpha /= 3;
                intensity += alpha;
            }
            intensity /= _size;
        }
    }
    return intensity;
}

void Video::resizeVideo(int _x, int _y) {
    destinationXSize = _x;
    destinationYSize = _y;
    pixels.resize(destinationXSize, destinationYSize);
}

void Video::updateVideoString() {
    
}


