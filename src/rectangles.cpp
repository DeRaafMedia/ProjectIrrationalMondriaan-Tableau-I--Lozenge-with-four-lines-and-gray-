//
//  rectangels.cpp
//  ProjectIrrationalMondriaan
//
//  Created by Remco Platjes on 16-11-14.
//
//

#include "rectangles.h"
#include "ofApp.h"

void rectangles::draw(string squareId,
                      int initXAxis,
                      int initYAxis,
                      int initWidth,
                      int initHeight,
                      int initRed,
                      int initGeen,
                      int initBlue,
                      int initRotation,
                      bool showSquaresId,
                      bool oscEnabled){
    
    if(oscEnabled == true){
        
        red = listener.redValue;
        green = listener.greenValue;
        blue = listener.blueValue;
        xAxis = listener.xAxisValue;
        yAxis = listener.yAxisValue;
        width = listener.widthValue;
        height = listener.heightValue;
        rotation = listener.rotationValue;
        
        ofPushMatrix();
            ofTranslate(initXAxis + xAxis, initYAxis + yAxis);
            ofSetColor(initRed + red, initGeen + green, initBlue + blue);
            ofRotate(initRotation + rotation);
            ofDrawRectangle(0, 0, initWidth + width, initHeight + height);
            if(showSquaresId == true){
                ofSetColor(255, 0, 0);
                ofDrawBitmapString("<" + squareId, initXAxis + 10, initYAxis + 10);
                ofDrawBitmapString(red, 100, 100);
            }
        ofPopMatrix();
    }else{
        ofPushMatrix();
            ofTranslate(initXAxis, initYAxis);
            ofSetColor(initRed, initGeen, initBlue);
            ofRotate(initRotation);
            ofDrawRectangle(0, 0, initWidth, initHeight);
            if(showSquaresId == true){
                ofSetColor(255, 0, 0);
                ofDrawBitmapString("<" + squareId, initXAxis + 10, initYAxis + 10);
                ofDrawBitmapString(red, 100, 100);
            }
        ofPopMatrix();
    }
    
}