//
//  ofApp.cpp
//  ProjectIrrationalMondriaan
//
//  Created by Remco Platjes on 19-11-14.
//
//
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetDataPathRoot("../Resources/data/");
    
    showInfo = false;
    showDot = false;
    showSquaresId = false;
    oscEnabled = false;
    
    displayResolutionWidth = 1280;
    displayResolutionHeight = 800;
    
    midlineWidth = displayResolutionWidth * 0.5;
    midlineHeight = displayResolutionHeight * 0.5;
    
    captureWidth = 320;
    captureHeight = 240;
    
    ofSetVerticalSync(true);
    ofSetCircleResolution(100);
    
    ofBackground(10, 10, 10);
    
    vidGrabber.setVerbose(true);
    vidGrabber.setup(captureWidth, captureHeight);
   
    colorImage.allocate(captureWidth, captureHeight);
    grayImage.allocate(captureWidth, captureHeight);
    grayBackground.allocate(captureWidth, captureHeight);
    grayDifference.allocate(captureWidth, captureHeight);
    
    blobMinimalArea = 1000;
    blobMaximumArea = captureWidth * captureHeight / 3;
    blobMaximumNumber = 1;
    blobFindHoles = false;
    
    blobManager.normalizePercentage = 0.7;
    blobManager.giveLowestPossibleIDs = true;
    blobManager.maxUndetectedTime = 200;
    blobManager.minDetectedTime = 500;
    blobManager.debugDrawCandidates = true;
    blobManager.enableUndetectedBlobs = true;
    
    learnBackground = true;
    threshold = 50;
    
    xAxisDisplacementRoom = 100.0;
    yAxisDisplacementRoom = 100.0;
    xAxisDisplacement = 1.0;
    yAxisDisplacement = 1.0;
}

//--------------------------------------------------------------
void ofApp::update(){
    fullscreenWidthOffset = (ofGetWindowWidth() * 0.5);
    fullscreenHeightOffset = (ofGetWindowHeight() * 0.5);
    
    bool newFrame = false;
    
    vidGrabber.update();
    newFrame = vidGrabber.isFrameNew();
    
    if(newFrame){
        colorImage.setFromPixels(vidGrabber.getPixels());
        colorImage.mirror(false, true);
        grayImage = colorImage;
        
        
        if (learnBackground == true){
            grayBackground = grayImage;
            learnBackground = false;
        }
        
        grayDifference.absDiff(grayBackground, grayImage);
        grayDifference.threshold(threshold);
        
        contourFinder.findContours(grayDifference, blobMinimalArea, blobMaximumArea, blobMaximumNumber, blobFindHoles);
    }
    
    blobManager.update(contourFinder.blobs);
    Tweener.update();
    
    
    if(blobManager.blobs.size() > 0){
        for(int i = 0; i < blobManager.blobs.size() ; i++)
        {
            ofxCvBlob blob = blobManager.blobs.at(i);
        
            Tweener.addTween(xAxisDisplacement, (blob.centroid.x / (captureWidth * 0.01)) * 0.01, 10);
            Tweener.addTween(yAxisDisplacement, (blob.centroid.y / (captureHeight * 0.01)) * 0.01, 10);
        }
    }else{
        for(float i = xAxisDisplacement; i < 1.0; i = i + 0.01){
                Tweener.addTween(xAxisDisplacement, i, 10);
        }
        for(float i = yAxisDisplacement; i < 1.0; i = i + 0.01){
            Tweener.addTween(yAxisDisplacement, i, 10);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofPushMatrix();
        ofTranslate(fullscreenWidthOffset, 0);
        // Calculate background square size
        float backGroundSquare = sqrt(pow(displayResolutionHeight, 2.0) + pow(displayResolutionHeight, 2.0)) * 0.5;
        rectangle_1.draw("background", 0, 0, backGroundSquare, backGroundSquare, 255, 255, 255, 45, false, false);
    ofPopMatrix();
    
    ofPushMatrix();
        ofTranslate(xAxisDisplacementRoom * xAxisDisplacement, yAxisDisplacementRoom * yAxisDisplacement);
        if(showDot == true){
            ofSetColor(128, 128, 128);
            ofDrawCircle(0, 0, 20);
        }
    
        ofSetColor(0, 0, 0);
    
        ofDrawRectangle(-(displayResolutionWidth * 0.5),
                        midlineHeight * (1.0 - 0.433) - xAxisDisplacementRoom,
                        displayResolutionWidth * 2,
                        displayResolutionHeight * 0.027);
    
        ofDrawRectangle(-(displayResolutionWidth * 0.5),
                        (midlineHeight * 1.68) - xAxisDisplacementRoom,
                        displayResolutionWidth * 2,
                        displayResolutionHeight * 0.027);
    
        ofDrawRectangle((midlineWidth  - yAxisDisplacementRoom) - (midlineWidth * 0.34),
                        -(displayResolutionHeight * 0.5),
                        displayResolutionHeight * 0.027,
                        displayResolutionHeight * 2);
    
        ofDrawRectangle((midlineWidth - yAxisDisplacementRoom) + (midlineWidth * (1.0 - 0.605)),
                        -(displayResolutionHeight * 0.5),
                        displayResolutionHeight * 0.034,
                        displayResolutionHeight * 2);
    
    ofPopMatrix();
    
    if(showInfo == true){
        ofPushMatrix();
            ofTranslate(ofGetWindowWidth() * 0.25, 0);
            ofSetColor(0, 0, 0);
            ofDrawRectangle(-(ofGetWindowWidth() * 0.25), 0, ofGetWindowWidth(), ofGetWindowHeight());
            ofSetColor(255, 255, 255);
            grayBackground.draw(20, 20);
            grayDifference.draw(captureWidth + 20, 20);
        
            stringstream coordinates;
            coordinates << "[x-axis : " << xAxisDisplacement << " ]"
            << " <--> [y-axis : "<< yAxisDisplacement << " ] \n"
            << "[learn background] --> Press spacebar \n"
            << "[Threshhold : " << threshold << " ] --> Press + / -\n"
            << "[Toggel info] --> Press i \n"
            << "[Toggel dot] --> Press d";
            ofDrawBitmapString(coordinates.str(), 50, 330);
        
        ofPopMatrix();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == 'i'){
        showInfo = !showInfo;
    }
    if(key == 'd'){
        showDot = !showDot;
    }
    switch (key){
        case ' ':
            learnBackground = true;
            break;
        case '+':
            threshold ++;
            if (threshold > 255) threshold = 255;
            break;
        case '-':
            threshold --;
            if (threshold < 0) threshold = 0;
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}