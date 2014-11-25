//
//  ContainmentBlob.h
//  LockMachine
//
//  Created by Jesse Garrison on 11/7/14.
//
//

#ifndef __LockMachine__ContainmentBlob__
#define __LockMachine__ContainmentBlob__

#include <stdio.h>
#include "ofMain.h"

class ContainmentBlob{
    
public:
    ContainmentBlob(){};
    ContainmentBlob(ofVec3f _pos){setup(_pos);};
    
    void  setup(ofVec3f _pos);
    void update();
    void draw();
    
    float targetSize = 100;
    ofColor color;
    
    
private:
    ofVec3f pos;
    
    ofMesh theMesh, subMesh, baseMesh;
    
    vector<ofPolyline> lines;
    
    int seed;
    
    float size, prevSize;
    float smoothUp, smoothDown;
    float decay;
    float speed;
    
    vector<ofVec3f> randomPoints;
    
};

#endif /* defined(__LockMachine__ContainmentBlob__) */
