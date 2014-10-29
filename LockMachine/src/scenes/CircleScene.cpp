//
//  CircleScene.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 10/8/14.
//
//

#include "CircleScene.h"


void CircleScene::setup(){
    for (int i=0; i<NUMCIRCLES; i++) {
        
    }

    
    cout<<"setup circles!"<<endl;
    finishedEntering();
    
}

void CircleScene::update(){

    
}

void CircleScene::setSizes(map<int,float> s){

    
}


void CircleScene::draw(){
    ofBackground(0);
    
    ofSetColor(255);
    ofDrawCircle(10, 10, 50);
    
    
    

    
}