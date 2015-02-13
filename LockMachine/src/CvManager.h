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
#include "ofxPS3EyeGrabber.h"
#include "ofxOpenCv.h"

enum camera{
    CAM_ISIGHT,
    CAM_EYE_1,
    CAM_EYE_2
    
};

class CvManager: public ofThread{
    
public:
    
    void threadedFunction(){

        
        while(isThreadRunning()){

            
            
            
        }
    
    };
    
    void setup(){
        activeCamera = CAM_EYE_1;
        bIsSmoothing = false;
        smoothing = 0.7;
        
        if(activeCamera == CAM_ISIGHT){
            iSight.setDeviceID(0);
            iSight.setup(width,height);
        }
       
        eye1.setDesiredFrameRate(30);
        image.allocate(width, height, OF_IMAGE_COLOR);
        prevImage.setFromPixels(image);
        
        eye1.setup(width  , height);
        eye1.setPixelFormat(OF_PIXELS_RGB);
        
        eye2.setDeviceID(1);
        eye2.setup(width  , height);
        eye2.setPixelFormat(OF_PIXELS_RGB);
        
        currentCvImage.allocate(width  , height);
        prevCvImage.allocate(width, height);
    }
    
    void update(){
        
        if(smoothing<= 0.01){
            bIsSmoothing=false;
        } else {
            bIsSmoothing=true;
        }
        
        switch (activeCamera){
            case CAM_ISIGHT:
                iSight.update();
                if(iSight.isFrameNew()){
                    
                    updateCv(iSight.getPixels());
                    if(!bIsCatchingGlitches || avgDiff < glitchThreshold){
                        bHasNewFrame = true;
                        image = iSight.getPixels();
                    
                        if(bIsSmoothing){
                            image = smoothImage(prevImage, image, smoothing);
                            prevImage.setFromPixels(image);
                        }
                    } else if(bIsCatchingGlitches && avgDiff > glitchThreshold) {
                        cout<<"caught one!"<<endl;
                    }
                } else {
                    bHasNewFrame = false;
                }
                break;
            case CAM_EYE_1:
                eye1.update();
                if(eye1.isFrameNew()){
                    
                    if(bIsCalculatingCV) updateCv(eye1.getPixels());
                    if(!bIsCatchingGlitches || avgDiff < glitchThreshold){
                    
                    bHasNewFrame = true;
                    image.setFromPixels( eye1.getPixels() );
                    
                        if(bIsSmoothing){
                            image = smoothImage(prevImage, image,smoothing);
                            prevImage.setFromPixels(image);
                        }
                    }else if(bIsCatchingGlitches && avgDiff > glitchThreshold) {
                        cout<<"caught a glitch on 1!"<<endl;
                    }
                    
                }else{
                    bHasNewFrame = false;
                }
                break;
            case CAM_EYE_2:
                eye2.update();
                if(eye2.isFrameNew()){
                    if(bIsCalculatingCV) updateCv(eye1.getPixels());
                    if(!bIsCatchingGlitches || avgDiff < glitchThreshold){
                        
                        bHasNewFrame = true;
                        image.setFromPixels( eye2.getPixels() );
                        
                        if(bIsSmoothing){
                            image = smoothImage(prevImage, image,smoothing);
                            prevImage.setFromPixels(image);
                        }
                    }else if(bIsCatchingGlitches && avgDiff > glitchThreshold) {
                        cout<<"caught a glitch on 2!"<<endl;
                    }
                    
                }else{}
                break;
            default:
                break;
                
                
        }
        

        
    }
    
    int width=640; int height =480;
    
    bool bHasNewFrame = false ;
    
    bool bIsSmoothing = false;
    
    bool bIsCalculatingCV = true;
    bool bIsCatchingGlitches = false;
    int glitchThreshold= 100;
    
    camera activeCamera;
    
    ofImage getFrame(){return image; bHasNewFrame= false;};
    //ofImage getSmoothed(){return smoothImage(prevImage, image, smoothing); bHasNewFrame= false;};
    
    ofxCvGrayscaleImage getCVImg(){};

    float smoothing;

    void close(){iSight.close();};
    
    void setGain1(float f){
        eye1.setGain(f);
    }
    void setBrightness1(float f){
        eye1.setBrightness(f);
    }
    
    void setGain2(float f){
        eye2.setGain(f);
    }
    void setBrightness2(float f){
        eye2.setBrightness(f);
    }

    
private:
    ofVideoGrabber iSight;
    ofxPS3EyeGrabber eye1, eye2;

    ofImage image, prevImage;
    
    ofxCvGrayscaleImage currentCvImage;
    ofxCvGrayscaleImage prevCvImage;
    float avgDiff;
    
    ofPixels smoothImage(ofPixels oldPix, ofPixels newPix, float smoothing){
        ofPixels smoothedImage;
        smoothedImage.allocate(oldPix.getWidth(), oldPix.getHeight(), OF_PIXELS_RGBA);
        
        
        
        for (int i=0; i<smoothedImage.size();i++){
            try{
                smoothedImage[i] = (oldPix[i]*smoothing )+ (newPix[i]*(1-smoothing));
            }catch (...){
                
            }
        }
        
        return smoothedImage;
        
    }
    
    void updateCv(ofPixels _pix){
        prevCvImage = currentCvImage;
        currentCvImage.setFromPixels(_pix);
        
        ofxCvGrayscaleImage diff;
        diff.allocate(width, height);
        diff= currentCvImage;
        diff.absDiff(prevCvImage);
        
        int val = 0;
        for(int i=0;i<diff.getPixels().size();i++){
            val += diff.getPixels()[i] ;
        }
        avgDiff = val / diff.getPixels().size();
        
    }
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
