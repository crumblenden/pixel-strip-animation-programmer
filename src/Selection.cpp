//
//  Selection.cpp
//  LEDAnimator
//
//  Created by Chris Lynden on 10/05/2018.
//
//


#include "ofApp.h"


void ofApp::selectionPanelUserInput() {
    
    if(selectAllStrips != selectAllStripsLastState) {
        stripSelectorChanged();
    }
    for(int i = 0; i < numStrips; i++) {
        if(stripSelectors[i] != stripSelectorLastStates[i]) {
            stripSelectorChanged();
        }
    }
    selectAllStripsLastState = selectAllStrips;
    for(int i = 0; i < numStrips; i++) {
        stripSelectorLastStates[i] = stripSelectors[i];
    }
    
    ////_________________________________________________\\\\
    
    if(selectAll) {
        numSelected = 0;
        for(int i = 0; i < numStrips; i++) {
            stripSelectors[i] = true;
            for(int j = 0; j < strips[i].numLeds; j++) {
                strips[i].selectionFlags[j] = true;
                numSelected++;
            }
        }
    }
    
    ////_________________________________________________\\\\
    
    
    if(!selectRange) {selectRangeBlock = false; selectRangeHappened = false;}
    if(selectRange && !selectRangeBlock) {
        numSelected = 0;
        int count = 0;
        for(int i = 0; i < numStrips; i++) {
            if(stripSelectors[i]) {
                for(int j = 0; j < strips[i].numLeds; j++) {
                    if(count >= rangeStart && count <= rangeEnd) {
                        strips[i].selectionFlags[j] = true;
                        numSelected++;
                    }
                    count++;
                }
            }
        }
        selectRangeHappened = true;
    }
    if(selectRange && selectRangeHappened) {selectRangeBlock = true;}
    
    ////_________________________________________________\\\\
    
    if(!selectPattern) {selectPatternBlock = false; selectPatternHappened = false;}
    if(selectPattern && !selectPatternBlock) {
        numSelected = 0;
        int count = 0;
        for(int i = 0; i < numStrips; i++) {
            if(stripSelectors[i]) {
                for(int j = 0; j < strips[i].numLeds; j++) {
                    if(count >= rangeStart && count <= rangeEnd) {
                        if((count % (groupSize + gapSize)) < groupSize) {
                            strips[i].selectionFlags[j] = true;
                            numSelected++;
                        } else {
                            strips[i].selectionFlags[j] = false;
                        }
                    }
                    count++;
                }
            }
        }
        selectPatternHappened = true;
    }
    if(selectPattern && selectPatternHappened) {selectPatternBlock = true;}
    
    ////_________________________________________________\\\\
    
    if(!nudgeSelectionDown) {nudgeDownBlock = false; nudgeDownHappened = false;}
    if(nudgeSelectionDown && !nudgeDownBlock) {
        if(nudgeSelectionDown){
            vector<bool>allFlags;
            for(int i = 0; i < numStrips; i++) {
                if(stripSelectors[i]) {
                    for(int j = 0; j < strips[i].numLeds; j++) {
                        allFlags.push_back(strips[i].selectionFlags[j]);
                    }
                }
            }
            int numLedsSoFar = 0;
            for(int i = 0; i < numStrips; i++) {
                
                if(stripSelectors[i]) {
                    for(int j = 0; j < strips[i].numLeds; j++) {
                        strips[i].selectionFlags[j] = allFlags[((j+1) + numLedsSoFar) % allFlags.size()];
                    }
                    numLedsSoFar += strips[i].numLeds;
                }
            }
            nudgeDownHappened = true;
        }
    }
    if(nudgeSelectionDown && nudgeDownHappened) {nudgeDownBlock = true;}
    
    ////_________________________________________________\\\\
    
    if(!nudgeSelectionUp) {nudgeUpBlock = false; nudgeUpHappened = false;}
    if(nudgeSelectionUp && !nudgeUpBlock) {
        vector<bool>allFlags;
        for(int i = 0; i < numStrips; i++) {
            if(stripSelectors[i]) {
                for(int j = 0; j < strips[i].numLeds; j++) {
                    allFlags.push_back(strips[i].selectionFlags[j]);
                }
            }
        }
        int numLedsSoFar = 0;
        bool firstCount = false;
        for(int i = 0; i < numStrips; i++) {
            
            if(stripSelectors[i]) {
                for(int j = 0; j < strips[i].numLeds; j++) {
                    if(!firstCount) {
                        strips[i].selectionFlags[j] = allFlags[allFlags.size()-1];
                        firstCount = true;
                    } else {
                        strips[i].selectionFlags[j] = allFlags[((j-1) + numLedsSoFar) % allFlags.size()];
                    }
                }
                numLedsSoFar += strips[i].numLeds;
            }
        }
        nudgeUpHappened = true;
    }
    if(nudgeSelectionUp && nudgeUpHappened) {nudgeUpBlock = true;}
    
    ////_________________________________________________\\\\
    
    if(!invertSelection) {invertBlock = false; invertHappened = false;}
    if(invertSelection && !invertBlock) {
        for(int i = 0; i < numStrips; i++) {
            for(int j = 0; j < strips[i].numLeds; j++) {
                if(stripSelectors[i]) {
                    strips[i].selectionFlags[j] = !strips[i].selectionFlags[j];
                }
            }
        }
        int temp = totalLeds - numSelected;
        numSelected = temp;
        invertHappened = true;
    }
    if(invertSelection && invertHappened) {invertBlock = true;}
    
    cout<<"numSelected: "<<numSelected<<endl;
    
    ////_________________________________________________\\\\
    
    if(clearSelection) {
        for(int i = 0; i < numStrips; i++) {
            for(int j = 0; j < strips[i].numLeds; j++) {
                strips[i].selectionFlags[j] = false;
            }
        }
        numSelected = 0;
        currentSelection.clear();
    }
    
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

void ofApp::getCurrentSelection() {
    currentSelection.clear();
    int count = 0;
    for(int i = 0; i < numStrips; i++) {
        for(int j = 0; j < strips[i].numLeds; j++) {
            if(strips[i].selectionFlags[j]) {
                currentSelection.push_back(Selection());
                currentSelection[count].strip = i;
                currentSelection[count].index = j;
                count++;
            }
        }
    }
}

//////////////////////////////////////////////////////////

void ofApp::stripSelectorChanged() {
    int numLedsSelectable = 0;
    for(int i = 0; i < numStrips; i++) {
        if(stripSelectors[i]) {numLedsSelectable += strips[i].numLeds;}
    }
    rangeEnd.setMax(numLedsSelectable -1);
    rangeEnd = numLedsSelectable -1;
    gapSize.setMax(numLedsSelectable -1);
}