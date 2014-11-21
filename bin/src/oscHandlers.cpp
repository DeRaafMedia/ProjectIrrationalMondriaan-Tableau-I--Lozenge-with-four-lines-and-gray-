//
//  oscHandler.cpp
//  ProjectIrrationalMondriaan
//
//  Created by Remco Platjes on 15-11-14.
//
//

#include "oscHandlers.h"

oscHandlers::oscHandlers(){
    receiver.setup(PORT);
    currentMessageString = 0;
    idValue = 0;
    xAxisValue = 0.0;
    yAxisValue = 0.0;
    redValue = 0;
    greenValue = 0;
    blueValue = 0;
    widthValue = 0.0;
    heightValue = 0.0;
    rotationValue = 0.0;
    listenForIdValue = "";
    listenForXAxisValue = "";
    listenForYAxisValue = "";
    listenForWidthValue = "";
    listenForHeightValue = "";
    listenForRedValue = "";
    listenForGreenValue = "";
    listenForBlueValue = "";
    listenForRotationValue = "";
}

void oscHandlers::listener(string squareId){
    
    for(int i = 0; i < NUM_MSG_STRINGS; i++){
        if(timers[i] < ofGetElapsedTimef()){
            messageStrings[i] = "";
        }
    }
    
    // check for waiting messages
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        listenForIdValue = "/irrationalMondriaan/" + squareId + "/id";
        listenForXAxisValue = "/irrationalMondriaan/" + squareId + "/x";
        listenForYAxisValue = "/irrationalMondriaan/" + squareId + "/y";
        listenForWidthValue = "/irrationalMondriaan/" + squareId + "/w";
        listenForHeightValue = "/irrationalMondriaan/" + squareId + "/h";
        listenForRedValue = "/irrationalMondriaan/" + squareId + "/r";
        listenForGreenValue = "/irrationalMondriaan/" + squareId + "/g";
        listenForBlueValue = "/irrationalMondriaan/" + squareId + "/b";
        listenForRotationValue = "/irrationalMondriaan/" + squareId + "/d";
        
        if(m.getAddress() == listenForIdValue){
            idValue = m.getArgAsInt32(0);
        }
        else if(m.getAddress() == listenForXAxisValue){
            xAxisValue = m.getArgAsFloat(0);
        }
        else if(m.getAddress() == listenForYAxisValue){
            yAxisValue = m.getArgAsFloat(0);
        }
        else if(m.getAddress() == listenForWidthValue){
            widthValue = m.getArgAsFloat(0);
        }
        else if(m.getAddress() == listenForHeightValue){
            heightValue = m.getArgAsFloat(0);
        }
        else if(m.getAddress() == listenForRedValue){
            redValue = m.getArgAsInt32(0);
        }
        else if(m.getAddress() == listenForGreenValue){
            greenValue = m.getArgAsInt32(0);
        }
        else if(m.getAddress() == listenForBlueValue){
            blueValue = m.getArgAsInt32(0);
        }
        else if(m.getAddress() == listenForRotationValue){
            rotationValue = m.getArgAsFloat(0);
        }
        else{
            textValue = m.getAddress();
            textValue += ": ";
            for(int i = 0; i < m.getNumArgs(); i++){
                // get the argument type
                textValue += m.getArgTypeName(i);
                textValue += ":";
                // display the argument - make sure we get the right type
                if(m.getArgType(i) == OFXOSC_TYPE_INT32){
                    textValue = ofToString(m.getArgAsInt32(i));
                }
                else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
                    textValue = ofToString(m.getArgAsFloat(i));
                }
                else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
                    textValue = m.getArgAsString(i);
                }
                else{
                    return "unknown";
                }
            }
            // add to the list of strings to display
            //messageStrings[currentMessageString] = messageString;
            //timers[currentMessageString] = ofGetElapsedTimef() + 5.0f;
            //currentMessageString = (currentMessageString + 1) % NUM_MSG_STRINGS;
            // clear the next line
            //messageStrings[currentMessageString] = "";
        }
    }
}