//
//  CvManager.h
//  LockMachine
//
//  Created by Jesse Garrison on 11/8/14.
//
//

#ifndef __LockMachine__CvManager__
#define __LockMachine__CvManager__

#include <stdio.h>
#include "ofMain.h"

class CvManager: public ofThread{
    
public:
    
    void threadedFunction(){

        
        while(isThreadRunning()){

            
            
            
        }
    
    };
    
    void setup(){
        grabber.setDeviceID(0);
        grabber.setup(width,height);
        
    }
    
    void update(){
        grabber.update();
        if(grabber.isFrameNew()){
            bHasNewFrame = true;
            image = grabber.getPixels();
            
        } else {
            
        }
    }
    
    int width=640; int height =480;
    
    bool bHasNewFrame = false ;
    
    bool bIsSmoothing;
    
    ofImage getFrame(){return image; bHasNewFrame= false;};
    
    void close(){grabber.close();};
    
private:
    ofVideoGrabber grabber;
    ofImage image;
    
    int smoothing;
};




class ConnectionManager : public ofThread{
    
public:
    void threadedFunction(){
        while(isThreadRunning()){
 
            lock();
            vector<vector<ofPoint> > tempHulls = hulls;
            vector< pair<ofPoint,ofPoint> > tempInternalConnections ;
            vector< pair<ofPoint,ofPoint> > tempExternalConnections ;
            unlock();
            
            for (int i=0;i<tempHulls.size();i++){ //for each hull
                
                for(int j =0;j<tempHulls[i].size();j++){ //go through its points
                    ofPoint thisPoint = tempHulls[i][j];
                    
                    if(bDrawInternal){
                        for(int k =j;k<tempHulls[i].size();k++){ //each of those looks through its other points
                            ofPoint thatPoint = tempHulls[i][k];
                            if (thisPoint.distance(thatPoint) < maxDist) tempInternalConnections.push_back( pair<ofPoint, ofPoint>(thisPoint,thatPoint));
                        }
                    }
                    if(bDrawExternal){
                        
                        for (int k=0; k<tempHulls.size(); k++) { //and other hulls
                            if (tempHulls[k]!=tempHulls[i]){
                                for (int l=k; l<tempHulls[k].size(); l++) { //and other hulls' points
                                    ofPoint thatPoint = tempHulls[k][l];
                                    if (thisPoint.distance(thatPoint)< maxDist) tempExternalConnections.push_back( pair<ofPoint, ofPoint>(thisPoint,thatPoint));
                                    
                                }
                            }
                            
                        }
                        
                    }
                }
            }
            
            lock();
            internalConnections = tempInternalConnections;
            externalConnections = tempExternalConnections;
            unlock();
        }
        
    };
    
    vector< pair<ofPoint,ofPoint> > getInternalConnections(){
        return internalConnections;
    };
    vector< pair<ofPoint,ofPoint> > getExternalConnections(){
        return externalConnections;
    };
    void setHulls(vector< vector<ofPoint> > _hulls){
        hulls=_hulls;
    };
    
    void setMaxDist(float _amt){
        maxDist = _amt;
    };
    
    void setDrawMode(bool drawInternal, bool drawExternal){
        bDrawInternal = drawInternal;
        bDrawExternal = drawExternal;
    }
    
private:
    
    float maxDist = 50;
    bool bDrawInternal, bDrawExternal;
    
    vector<vector<ofPoint> > hulls;
    vector< pair<ofPoint,ofPoint> > internalConnections, externalConnections;
    
    
};

class ConnectionDrawer : public ofThread{ //No threaded openGL calls?//
    
    
public :
    void threadedFunction(){
        drawnTex.allocate(ofGetWidth(), ofGetHeight());
        while(isThreadRunning()){
            ofFbo tempFbo;
            tempFbo.allocate(ofGetWidth(), ofGetHeight());
            
            tempFbo.begin();
            ofDrawLine(0, 0, 100, 100);
            tempFbo.end();
            
            lock();
            drawnTex = tempFbo;
            unlock();
        }
        
    }
    
    void setConnections( vector< pair<ofPoint, ofPoint> > _connections ){
        connections = _connections;
    }
    
    ofFbo getFbo(){
        return drawnTex;
    }
    
private:
    
    ofFbo drawnTex;
    
    vector< pair<ofPoint, ofPoint> > connections;
};

#endif /* defined(__LockMachine__CvManager__) */
