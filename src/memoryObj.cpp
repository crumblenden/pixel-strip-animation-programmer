//
//  memoryObj.cpp
//  emptyExample
//
//  Created by Chris Lynden on 19/02/2018.
//
//

#include "memoryObj.h"


void Memory::update(int _time) {
//    if(memVideo.isLoaded()) {
//        memVideo.update();
//        pixels = memVideo.getPixels();
//        pixels.resize(vidX, vidY);
//    }
    memVideo.update();

    for(int i = 0; i < memShapes.size(); i++) {
        memShapes[i].update(_time);
    }
    
    if(memIntensity > 0) {
        memActive = true;
    } else {
        memActive = false;
    }
}

void Memory::clear() {
    memLedData.clear();
    memShapes.clear();
//    if(memVideo.isLoaded()) {
//        memVideo.closeMovie();
//    }
}

//void Memory::loadVideo(string _url, int _visXSize, int _visYSize) {
//    vidX = _visXSize;
//    vidY = _visYSize;
//    memVideo.load(_url);
//    memVideo.setLoopState(OF_LOOP_NORMAL);
//    memVideo.play();
//}

//int Memory::getDataFromVideoPixels(int _x, int _y, int _size) {
//    int intensity = 0;
//    if(memVideo.isLoaded()){
//        for(int i = 0; i < _size; i++) {
//            for(int j = 0; j < _size; j++) {
//                int index = pixels.getPixelIndex(_x + j, _y + i);
//                int alpha = 0;
//                for(int k = 0; k < 3; k++) {
//                    alpha += pixels[index+k];
//                }
//                alpha /= 3;
//                intensity += alpha;
//            }
//            intensity /= _size;
//        }
//    }
//    return intensity;
//}
