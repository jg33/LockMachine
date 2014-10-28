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
        circles.push_back(Circle());
        
    }
    
    circles[0].setPosition(50, ofGetHeight()/2, 0);
    circles[1].setPosition(100, ofGetHeight()/2, 0);
    circles[2].setPosition(250, ofGetHeight()/2, 0);
    circles[3].setPosition(450, ofGetHeight()/2, 0);
    circles[4].setPosition(650, ofGetHeight()/2, 0);
    
    for (int i = 0; i<circles.size(); i++){
        circles[i].setSize(10);
    }
    
    cout<<"setup circles!"<<endl;
    finishedEntering();
    
}

void CircleScene::update(){

    
}

void CircleScene::setSizes(map<int,float> s){
    for (int i=0; i<circles.size(); i++) {
        try {
            circles[i].setSize(s[i-1]*50);

        } catch (exception e) {
            cout<< "except"<< endl;
        }
    }
    
}


void CircleScene::draw(){
    ofBackground(0);
    for (int i=0; i<circles.size(); i++) {
        circles[i].draw();
    }
    

    
}