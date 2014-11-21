//
//  oscHandler.h
//  ProjectIrrationalMondriaan
//
//  Created by Remco Platjes on 15-11-14.
//
//

#ifndef __ProjectIrrationalMondriaan__oscHandler__
#define __ProjectIrrationalMondriaan__oscHandler__

#include <stdio.h>
#include "ofMain.h"
#include "ofxOsc.h"

#define PORT 12345
#define NUM_MSG_STRINGS 20

class oscHandlers{
    public:
        oscHandlers();
        void listener(string squareId);
    
        ofxOscReceiver receiver;
    
        int currentMessageString;
        string messageStrings[NUM_MSG_STRINGS];
        float timers[NUM_MSG_STRINGS];
    
        int idValue;
        int xAxisValue;
        int yAxisValue;
        int redValue;
        int greenValue;
        int blueValue;
        int widthValue;
        int heightValue;
        int rotationValue;
        string textValue;
    
        string listenForIdValue;
        string listenForXAxisValue;
        string listenForYAxisValue;
        string listenForWidthValue;
        string listenForHeightValue;
        string listenForRedValue;
        string listenForGreenValue;
        string listenForBlueValue;
        string listenForRotationValue;

    private:
};


#endif /* defined(__ProjectIrrationalMondriaan__oscHandler__) */