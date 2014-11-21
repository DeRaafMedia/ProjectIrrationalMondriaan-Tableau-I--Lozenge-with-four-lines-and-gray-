//
//  soundReactiveBars.h
//  ProjectIrrationalMondriaan
//
//  Created by Remco Platjes on 19-11-14.
//
//

#ifndef __ProjectIrrationalMondriaan__soundReactiveBars__
#define __ProjectIrrationalMondriaan__soundReactiveBars__

#include <stdio.h>
#include "ofMain.h"

class soundReactiveBars: public ofSoundStream{
    public:
        void setup();
        void update();
        void draw(int initWidth, int initHeight, int initThickness, int initRed, int initGreen, int initBlue, int initBufferSize, float initSensitivity);
        void audioIn(float * input, int bufferSize, int nChannels);
    
    int lineWidth, lineHeight, lineThickness, red, green, blue, bufferSize;
    float sensitivity;
    
    vector <float> left;
    vector <float> right;
    vector <float> volHistory;
    
    int bufferCounter;
    int drawCounter;
    
    float smoothedVol;
    float scaledVol;
};

#endif /* defined(__ProjectIrrationalMondriaan__soundReactiveBars__) */