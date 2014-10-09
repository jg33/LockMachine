//
//  Circle.h
//  StringMachine
//
//  Created by Jesse Garrison on 10/8/14.
//
//

#ifndef __StringMachine__Circle__
#define __StringMachine__Circle__

#include <stdio.h>
#include "ofMain.h"

class Circle : public ofNode {
    public:
    Circle();
        void customDraw();
        void inline setSize(float s){size = s;};
        void inline setColor(ofColor c){color = c;};
        //void inline setPosition(float x, float y, float z){ pos = ofVec3f(x,y,z);};
    
private:
    ofColor color;
    float size;
    
    ofVec3f pos;
    
};



#endif /* defined(__StringMachine__Circle__) */
