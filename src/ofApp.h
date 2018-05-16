#pragma once

#include "ofMain.h"
#include "ofxGuiExtended.h"
#include "ledStrip.h"
#include "Osc.h"
#include "shapeObj.h"
#include "memoryObj.h"
#include <math.h>
#include <string>
#include <stdio.h>

class ofApp : public ofBaseApp{
    
public:
    
    ///////////////////////////////////////////////////////
    //OF
    ///////////////////////////////////////////////////////
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ///////////////////////////////////////////////////////
    //MAIN CONTROL LOOP
    ///////////////////////////////////////////////////////
    void userInput();
    void selectionPanelUserInput();
    void colourPanelUserInput();
    void shapePanelUserInput();
    void programmerContentsPanelUserInput();
    void videoPanelUserInput();
    void playbackPanelUserInput();
    

    ///////////////////////////////////////////////////////
    //SERIAL COMMUNICATION
    ///////////////////////////////////////////////////////
    ofSerial serial;
    vector<u_int8_t> message;
    void createMessage();
    void testSerial();
    void transmitMessage();
    int successCount;
    bool started;
    int startUpTime;
    
    ///////////////////////////////////////////////////////
    //DATA SCALE
    ///////////////////////////////////////////////////////
    int numStrips;
    int numLedsPerStrip;
    int totalLeds;
    
    ///////////////////////////////////////////////////////
    //DATA STORAGE
    ///////////////////////////////////////////////////////
    vector<Strip> strips;
    Memory programmer;
    Memory playbacks[8];
    void updateStripsFromMemory(Memory _mem);
    void zeroLedData();
    void cleanUpMemLedData(Memory *_mem);
    
    ///////////////////////////////////////////////////////
    //SELECTION
    ///////////////////////////////////////////////////////
    int numSelected;
    struct Selection {
        int strip;
        int index; };
    vector<Selection> currentSelection;
    void getCurrentSelection();
    void stripSelectorChanged();
    bool selectAllStripsLastState;
    vector<bool> stripSelectorLastStates;
    
    ///////////////////////////////////////////////////////
    //COLOUR
    ///////////////////////////////////////////////////////
    void setSelectionColorRGBA(int & param);
    void setSelectionColorHSB(int & param);
    void setSelectionColorFromStored(int _index);
    void applyColorData(int _r, int _g, int _b, int _a);
    ofColor storedColors[32];
    bool storedColorFlags[32];
    bool preventStoringRGBA = false;
    bool preventStoringHSB = false;
    
    ///////////////////////////////////////////////////////
    //WAVE GENERATOR & PROGRAMMER
    ///////////////////////////////////////////////////////
    int time;
    void updateShapeParameters(int _index);
    void addToProgrammerContentsPanel(int _type);
    void updateProgrammerContentsPanel();
    void removeShapeFromProgrammer(int _index);
    int activeShapeIndex;
    enum programmerContentType {SHAPE, VIDEO};
    
    ///////////////////////////////////////////////////////
    //VISUALISER
    ///////////////////////////////////////////////////////
    ofColor visBackground;
    int visXPos;
    int visYPos;
    int visXSize;
    int visYSize;
    
    ///////////////////////////////////////////////////////
    //MOUSE
    ///////////////////////////////////////////////////////
    bool clickedInVis;
    bool dragSelectActive = false;
    int initialMouseXPos;
    int initialMouseYPos;
    int currentMouseXPos;
    int currentMouseYPos;
    
    ///////////////////////////////////////////////////////
    //STOP REPEAT INPUT
    ///////////////////////////////////////////////////////
    bool selectRangeHappened;
    bool selectRangeBlock;
    bool selectPatternHappened;
    bool selectPatternBlock;
    bool nudgeDownHappened;
    bool nudgeDownBlock;
    bool nudgeUpHappened;
    bool nudgeUpBlock;
    bool invertHappened;
    bool invertBlock;
    bool createShapeHappened;
    bool createShapeBlock;
    bool saveColourHappened;
    bool saveColourBlock;
    bool loadVideoHappened;
    bool loadVideoBlock;
    bool removeShapeHappened;
    bool removeShapeBlock;
    bool recordHappened;
    bool recordBlock;
    
    
    //////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////
    
    ///////////////////////////////////////////////////////
    //GUI
    ///////////////////////////////////////////////////////
    void makeGui();
    void makeSelectionPanelGui();
    void makeColorPanelGui();
    void makeShapePanelGui();
    void makeVideoPanelGui();
    void makePlaybackPanelGui();
    void makeProgrammerContentsPanelGui();
    ofxGui gui;
    
    ///////////////////////////////////////////////////////
    //SELECTION PANEL GUI
    ///////////////////////////////////////////////////////
    ofxGuiPanel* selectPanel;
    ofParameter <bool> selectAll;
    ofParameter <bool> selectAllStrips;
    ofxGuiGroup* selectRangeGroup;
    ofParameter <bool> selectRange;
    ofParameter <int> rangeStart;
    ofParameter <int> rangeEnd;
    ofxGuiGroup* selectPatternGroup;
    ofParameter <bool> selectPattern;
    ofParameter <int> groupSize;
    ofParameter <int> gapSize;
    ofParameter <bool> nudgeSelectionUp;
    ofParameter <bool> nudgeSelectionDown;
    ofParameter <bool> invertSelection;
    ofParameter <bool> clearSelection;
    
    ///////////////////////////////////////////////////////
    //STRIP TOGGLES PANEL GUI
    ///////////////////////////////////////////////////////
    ofxGuiPanel* stripSelectionPanel;
    vector<ofParameter<bool>> stripSelectors;
    
    ///////////////////////////////////////////////////////
    //COLOR PANEL GUI
    ///////////////////////////////////////////////////////
    ofxGuiPanel* colorPanel;
    ofxGuiGroup* RGBSlidersGroup;
    ofParameter <int> redSlider;
    ofParameter <int> greenSlider;
    ofParameter <int> blueSlider;
    ofParameter <int> alphaSlider;
    ofParameter <bool> saveRGBColor;
    ofxGuiGroup* HSBSlidersGroup;
    ofParameter <int> hueSlider;
    ofParameter <int> saturationSlider;
    ofParameter <int> brightnessSlider;
    ofParameter <bool> saveHSBColor;
    ofxGuiGroup* colorSelectionGroup;
    ofxGuiButton* storedColorButtons[32];
    ofxGuiGroup* colorSelectionRow[4];
    
    ///////////////////////////////////////////////////////
    //WAVE GENERATOR GUI
    ///////////////////////////////////////////////////////
    ofxGuiPanel* shapePanel;
    ofParameter <bool> createShape;
    ofxGuiGroup* shapeTypeGroup;
    ofParameter <bool> sinShapeType;
    ofParameter <bool> cosShapeType;
    ofParameter <bool> rampUpShapeType;
    ofParameter <bool> rampDownShapeType;
    ofParameter <bool> pulseShapeType;
    ofParameter <bool> triShapeType;
    ofParameter <float> speedSlider;
    ofParameter <int> stepSpreadSlider;
    ofParameter <int> chunkSizeSlider;
    ofParameter <float> widthSlider;
    ofParameter <float> offsetSlider;
    ofParameter <int> shapeMin;
    ofParameter <int> shapeMax;
    ofParameter <bool> shapeDirection;
    ofParameter <float> currentShapePreview;
    ofParameter <bool> editShapeColor;
    
    ///////////////////////////////////////////////////////
    //PROGRAMMER CONTENTS PANEL GUI
    ///////////////////////////////////////////////////////
    ofxGuiPanel* programmerContentsPanel;
    vector<ofParameter<string>> shapeLabels;
    vector<ofParameter<bool>> shapeRemoveButtons;
    vector<ofParameter<bool>> shapeEditButtons;
    ofParameter<string> ledDataLabel;
    vector<ofParameter<string>> videoLabels;
    vector<ofParameter<bool>> videoRemoveButtons;
    vector<ofParameter<bool>> videoEditButtons;

    ///////////////////////////////////////////////////////
    //VIDEO PANEL GUI
    ///////////////////////////////////////////////////////
    ofxGuiPanel* videoPanel;
    ofParameter <bool> loadVideo;
    
    ///////////////////////////////////////////////////////
    //PLAYBACK PANEL GUI
    ///////////////////////////////////////////////////////
    ofxGuiPanel* playbackPanel;
    ofxGuiGroup* playbackGroup;
    ofxGuiGroup* playbackParameterGroups[8];
    ofParameter<bool> playbackLabels[8];
    ofParameter<int> playbackSliders[8];
    ofParameter<bool> flashButtons[8];
    ofParameter<bool> playbackEditButtons[8];
    
    ///////////////////////////////////////////////////////
    //PLAYBACK CONTROL PANEL GUI
    ///////////////////////////////////////////////////////
    ofxGuiPanel* playbackControlPanel;
    ofParameter<bool> recordButton;
    ofParameter<bool> includeButton;
    ofParameter<bool> deleteButton;
    ofParameter<bool> optionsButton;
    
    ///////////////////////////////////////////////////////
    //VISUALISER CONTROL PANEL
    ///////////////////////////////////////////////////////
    ofxGuiPanel* visControlPanel;
    ofxGuiGroup* visControlGroup;
    ofParameter<bool> visFromProgrammer;
    ofParameter<bool> visFromOutput;
    
    ///////////////////////////////////////////////////////
    //WAVE GENERATOR SLIDER LISTENERS
    ///////////////////////////////////////////////////////
    void shapeTypeChanged(int &_param);
    void shapeSpeedChanged(float &speedSlider);
    void shapeSpreadChanged(int &stepSpreadSlider);
    void chunkSizeChanged(int &chunkSizeSlider);
    void shapeWidthChanged(float &widthSlider);
    void shapeOffsetChanged(float &offsetSlider);
    void shapeMinChanged(int &shapeMin);
    void shapeMaxChanged(int &shapeMax);
    void shapeDirChanged(bool &shapeDirection);
    
};










//        ofxGuiPanel gui;
//        ofxGuiButton but1;
//                bool but1Happened;
//                bool but1Block;
//
//        vector<ofxGuiToggle> stripSelectors;
//        ofxGuiToggle selectAllStrips;
//        void stripSelectorChanged();
//        bool selectAllStripsLastState;
//        vector<bool> stripSelectorLastStates;
//
//        ofxGuiIntInputField selectFrom;
//        ofxGuiIntInputField selectTo;
//        ofxGuiButton selectAll;
//        ofxGuiButton selectPattern;
//        ofxGuiIntInputField groupSize;
//        ofxGuiIntInputField gapSize;
//        ofxGuiButton nudgeDown;
//                bool nudgeDownHappened;
//                bool nudgeDownBlock;
//        ofxGuiButton nudgeUp;
//                bool nudgeUpHappened;
//                bool nudgeUpBlock;
//        ofxGuiButton invertSelection;
//                bool invertHappened;
//                bool invertBlock;
//        ofxGuiButton clearSelection;
//
//        void setSelectionColor(int _r, int _g, int _b);
//        ofxGuiButton white;
//        ofxGuiButton black;
//        ofxGuiButton red;
//        ofxGuiButton green;
//        ofxGuiButton blue;
//        ofxGuiButton applyAndSaveColor;
//        ofxGuiButton applyColor;
//        ofxGuiIntSlider ledRedSlider;
//            void ledRedChanged(int &ledRedSlider);
//        ofxGuiIntSlider ledGreenSlider;
//            void ledGreenChanged(int &ledGreenSlider);
//        ofxGuiIntSlider ledBlueSlider;
//            void ledeBlueChanged(int &ledBlueSlider);
//        ofxGuiIntSlider ledAlphaSlider;
//            void ledAlphaChanged(int &ledAlphaSlider);
//
//        ofxGuiButton clearProgrammer;
//
//        ofxGuiPanel shapePanel;
//        ofxGuiButton createShape;
//            bool createShapeHappened;
//            bool createShapeBlock;
//        ofxGuiIntSlider typeSlider;
//            void shapeTypeChanged(int &typeSlider);
//        ofxGuiFloatSlider speedSlider;
//            void shapeSpeedChanged(float &speedSlider);
//        ofxGuiIntSlider stepSpreadSlider;
//            void shapeSpreadChanged(int &stepSpreadSlider);
//        ofxGuiIntSlider chunkSizeSlider;
//            void chunkSizeChanged(int &chunkSizeSlider);
//        ofxGuiFloatSlider widthSlider;
//            void shapeWidthChanged(float &widthSlider);
//        ofxGuiIntSlider minValSlider;
//            void shapeMinChanged(int &minValSlider);
//        ofxGuiIntSlider maxValSlider;
//            void shapeMaxChanged(int &maxValSlider);
//        ofxGuiToggle directionToggle;
//            void shapeDirChanged(bool &directionToggle);
//        ofxGuiToggle randomToggle;
//            void shapeRandomChanged(bool &randomToggle);
//        ofxGuiIntSlider redSlider;
//            void shapeRedChanged(int &redSlider);
//        ofxGuiIntSlider greenSlider;
//            void shapeGreenChanged(int &greenSlider);
//        ofxGuiIntSlider blueSlider;
//            void shapeBlueChanged(int &blueSlider);
//        ofxGuiIntSlider alphaSlider;
//            void shapeAlphaChanged(int &alphaSlider);
//
//        ofxGuiPanel videoPanel;
//        ofxGuiButton loadVideoButton;
//            bool loadVideoButtonHappened;
//            bool loadVideoButtonBlock;





