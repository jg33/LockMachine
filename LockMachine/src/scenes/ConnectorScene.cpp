//
//  ConnectorScene.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 10/13/14.
//
//

#include "ConnectorScene.h"

void ConnectorScene::setup(){
    
    
}

void ConnectorScene::update(){
    connections.clear();
    if (points->size()>0) {
        
    for (int i=0;i<points->size();i++){
        for(int j=0;j<points->size();j++){
            if(points->at(i).distance(points->at(j))<connectionDistance){
                connections.push_back(Connection());
                connections.at(connections.size()-1).start=points->at(i);
                connections.at(connections.size()-1).end=points->at(j);
                connections.at(connections.size()-1).dist= points->at(i).distance(points->at(j));
                float powerFactor = pointPower->at(i) * pointPower->at(j);
                connections.at(connections.size()-1).maxWidth = maxLineWidth * powerFactor;
                connections.at(connections.size()-1).maxDist = connectionDistance;
            }
        }
        
    }
    }
    
}

void ConnectorScene::draw(){
    ofBackground(0);
    ofSetColor(255);
    
    for (int i=0; i<connections.size(); i++) {
        connections[i].draw();
    }
    for (int i=0; i<points->size();i++){
        ofCircle(points->at(i), pointPower->at(i)*5);
    }
    
}

