#pragma once

//
//  ofApp.h
//  ProjectIrrationalMondriaan
//
//  Created by Remco Platjes on 19-11-14.
//
//
#include "ofMain.h"
#include "rectangles.h"
#include "ofxOpenCv.h"
#include "ofxBlobsManager.h"
#include "ofxTweener.h"

#define _USE_LIVE_VIDEO

class ofApp : public ofBaseApp {
    public:
    
        void setup();
        void update();
        void draw();
    
        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y);
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
        void drawSoundReactiveBar(int initWidth, int initHeight, int initThickness, int initRed, int initGreen, int initBlue, int initBufferSize, float initSensitivity);
    
    bool showInfo;
    bool showDot;
    bool showSquaresId;
    bool oscEnabled;
    
    int displayResolutionWidth, displayResolutionHeight;
    float midlineWidth, midlineHeight;
    float fullscreenWidthOffset, fullscreenHeightOffset;
    int captureWidth, captureHeight;
    
    ofVideoGrabber vidGrabber;
    
    ofxCvGrayscaleImage grayImage, grayBackground, grayDifference;
    ofxCvColorImage	colorImage;
    
    ofxCvContourFinder contourFinder;
    
    int blobMinimalArea, blobMaximumArea, blobMaximumNumber;
    bool blobFindHoles;
    
    int threshold;
    bool learnBackground;
    
    float xAxisDisplacementRoom, yAxisDisplacementRoom;
    float xAxisDisplacement, yAxisDisplacement;
    
    ofxBlobsManager blobManager;
    
    rectangles rectangle_1;
};