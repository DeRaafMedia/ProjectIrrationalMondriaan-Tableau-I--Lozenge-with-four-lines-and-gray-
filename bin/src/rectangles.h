//
//  rectangels.h
//  ProjectIrrationalMondriaan
//
//  Created by Remco Platjes on 16-11-14.
//
//

#ifndef __ProjectIrrationalMondriaan__rectangels__
#define __ProjectIrrationalMondriaan__rectangels__

#include <stdio.h>
#include "oscHandlers.h"

class rectangles{
    public:
        //void setup(string squareId);
        //void update(string squareId);
        void draw(string squareId,
                  int initXAxis,
                  int initYAxis,
                  int initWidth,
                  int initHeight,
                  int initRed,
                  int initGeen,
                  int initBlue,
                  int initRotation,
                  bool showSquaresId,
                  bool oscEnabled);
    
        string squareId;
        int xAxis;
        int yAxis;
        int width;
        int height;
        int red;
        int green;
        int blue;
        int rotation;
    
        oscHandlers listener;
        ofTrueTypeFont font;
    
    private:
};

#endif /* defined(__ProjectIrrationalMondriaan__rectangels__) */
