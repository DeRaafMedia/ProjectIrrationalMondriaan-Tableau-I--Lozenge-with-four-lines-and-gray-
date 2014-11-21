//
//  soundReactiveBars.cpp
//  ProjectIrrationalMondriaan
//
//  Created by Remco Platjes on 19-11-14.
//
//

#include "soundReactiveBars.h"

void soundReactiveBars::setup(){
    
    
}

void soundReactiveBars::update(){
    
}

void soundReactiveBars::draw(int initWidth, int initHeight, int initThickness, int initRed, int initGreen, int initBlue, int initBufferSize, float initSensitivity){
    
    ofSetVerticalSync(true);
    ofSetCircleResolution(80);
    ofBackground(54, 54, 54);
    
    // 0 output channels,
    // 2 input channels
    // 44100 samples per second
    // 256 samples per buffer
    // 4 num buffers (latency)
    
    
    //if you want to set a different device id
    //soundStream.setDeviceID(0); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.
    
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    volHistory.assign(lineWidth, 0.0);
    
    bufferCounter	= 0;
    drawCounter		= 0;
    smoothedVol     = 0.0;
    scaledVol		= 0.0;
    
    //lets scale the vol up to a 0-1 range
    scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
    
    //lets record the volume into an array
    volHistory.push_back( scaledVol );
    
    //if we are bigger the the size we want to record - lets drop the oldest value
    if( volHistory.size() >= lineWidth ){
        volHistory.erase(volHistory.begin(), volHistory.begin()+1);
    }
    
    lineWidth = initWidth;
    lineHeight = initHeight;
    lineThickness = initThickness;
    red = initRed;
    green = initGreen;
    blue = initBlue;
    bufferSize = initBufferSize;
    sensitivity = initSensitivity;
    
    scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
    volHistory.push_back( scaledVol );
    
    ofSetColor(initRed, initGreen, initBlue);
    
    ofPushMatrix();
        ofDrawRectangle(0, 0, lineWidth, lineHeight);
    ofPopMatrix();
    
    ofPushMatrix();
        ofTranslate(0, lineHeight);
        //lets draw the volume history as a graph
        ofBeginShape();
            for (unsigned int i = 0; i < volHistory.size(); i++){
                if( i == 0 ) ofVertex(i, 400);
                ofVertex(i, 400 - volHistory[i] * 70);
                if( i == volHistory.size() -1 ) ofVertex(i, 400);
            }
        ofEndShape(false);
    ofPopMatrix();
   
    ofSetColor(225);
    ofDrawBitmapString("Scaled average vol (0-100): " + ofToString(scaledVol * 100.0, 0), 4, 18);
    
    //ofPushMatrix();
        //ofTranslate(0, lineHeight + lineThickness);
        //ofBeginShape();
        //for (unsigned int i = 0; i < volHistory.size(); i++){
            //if(i == 0) ofVertex(i, 0);
            //ofVertex(i, volHistory[i] * sensitivity);
            //if(i == volHistory.size() -1) ofVertex(i, 0);
        //}
        //ofEndShape(false);
    //ofPopMatrix();
    
    //ofPushMatrix();
        //ofRotate(180);
        //ofTranslate(-(lineWidth), -(lineHeight));
        //ofBeginShape();
        //for (unsigned int i = 0; i < volHistory.size(); i++){
            //if(i == 0) ofVertex(i, 0);
            //ofVertex(i, volHistory[i] * sensitivity);
            //if(i == volHistory.size() -1) ofVertex(i, 0);
        //}
        //ofEndShape(false);
        //ofPopMatrix();
}

void soundReactiveBars::audioIn(float * input, int bufferSize, int nChannels){
    
    float curVol = 0.0;
    int numCounted = 0;
    for (int i = 0; i < bufferSize; i++){
        left[i]		= input[i * 2] * 0.5;
        right[i]	= input[i * 2 + 1] * 0.5;
        
        curVol += left[i] * left[i];
        curVol += right[i] * right[i];
        
        numCounted += 2;
    }
    curVol /= (float)numCounted;
    curVol = sqrt( curVol );
    
    smoothedVol *= 0.93;
    smoothedVol += 0.07 * curVol;
    
    bufferCounter++;
}