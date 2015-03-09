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

            update();
            
            
        }
    
    };
    
    void setup(){
        activeCamera = CAM_EYE_1;
        bIsSmoothing = false;
        smoothing = 0.85;
        
        if(activeCamera == CAM_ISIGHT){
            iSight.setDeviceID(0);
            iSight.setup(width,height);
            iSight.setPixelFormat(OF_PIXELS_RGBA);
            iSight.setUseTexture(false);
        }
       
        eye1.setDesiredFrameRate(60);
        image.allocate(width, height, OF_IMAGE_COLOR);
        prevImage = image ;
        
        eye1.setup(width  , height);
        eye1.setPixelFormat(OF_PIXELS_RGBA);
        
        eye2.setDeviceID(1);
        eye2.setDesiredFrameRate(60);

        eye2.setup(width  , height);
        eye2.setPixelFormat(OF_PIXELS_RGBA);
        
        currentCvImage.allocate(width  , height);
        prevCvImage.allocate(width, height);
        diff.allocate(width, height);
        
        smoothedImage.allocate(width, height, OF_PIXELS_RGBA);

    }
    
    void update(){
        ofPixels tempImg;
        tempImg.allocate(width,height,OF_PIXELS_RGBA);
        
        if(smoothing<= 0.01){
            bIsSmoothing=false;
        } else {
            bIsSmoothing=true;
        }
        
        switch (activeCamera){
            case CAM_ISIGHT:
                iSight.update();
                if(iSight.isFrameNew()){
                    
                    if(bIsCalculatingCV) updateCv(iSight.getPixels());
                    if(!bIsCatchingGlitches || avgDiff < glitchThreshold){
                        
                        bHasNewFrame = true;
                        tempImg = iSight.getPixels() ;
                        
                        if(bIsSmoothing){
                            image = smoothImage(prevImage, tempImg,smoothing);
                            prevImage = image;
                        } else {
                            image = tempImg;
                        }
                    }else if(bIsCatchingGlitches && avgDiff > glitchThreshold) {
                        cout<<"caught a glitch on iSight!"<<endl;
                    }

                } else {
                    //bHasNewFrame = false;
                }
                break;
            case CAM_EYE_1:
                eye1.update();
                if(eye1.isFrameNew()){
                    
                    if(bIsCalculatingCV) updateCv(eye1.getPixels());
                    if(!bIsCatchingGlitches || avgDiff < glitchThreshold){
                    
                    bHasNewFrame = true;
                    tempImg = eye1.getPixels() ;
                    
                        if(bIsSmoothing){
                            image = smoothImage(prevImage, tempImg,smoothing);
                            prevImage = image;
                        } else {
                            image = tempImg;
                        }
                    }else if(bIsCatchingGlitches && avgDiff > glitchThreshold) {
                        cout<<"caught a glitch on 1!"<<endl;
                    }
                    
                }else{
                    //bHasNewFrame = false;
                }
                break;
            case CAM_EYE_2:
                eye2.update();
                if(eye2.isFrameNew()){
                    if(bIsCalculatingCV) updateCv(eye2.getPixels());
                    if(!bIsCatchingGlitches || avgDiff < glitchThreshold){
                        
                        bHasNewFrame = true;
                        tempImg = eye2.getPixels() ;
                        
                        if(bIsSmoothing){
                            image = smoothImage(prevImage, tempImg,smoothing);
                            prevImage = image;
                        } else {
                            image = tempImg;
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
    bool bIsCatchingGlitches = true;
    int glitchThreshold= 10;
    
    camera activeCamera;
    
   // ofImage getFrame(){return image; bHasNewFrame= false;};
    ofImage getFrame(){
        lock();
        finalImage = image;
        bHasNewFrame= false;
        unlock();

        return finalImage;

    };
    
    bool getHasNewFrame(){
        bool _bNewFrame;
        lock();
        _bNewFrame = bHasNewFrame;
        unlock();
        
        return _bNewFrame;
    }
    
    int getWidth(){
        int _width;
        lock();
        _width = width;
        unlock();
        
        return _width;
    }
    int getHeight(){
        bool _height;
        lock();
        _height = height;
        unlock();
        
        return _height;
    }
    
    ofxCvGrayscaleImage getCVImg(){};

    float smoothing;

    void close(){iSight.close();};
    
    void setGain1(float f){
        lock();
        eye1.setGain(f);
        unlock();
    }
    void setBrightness1(float f){
        lock();
        eye1.setBrightness(f);
        unlock();
    }
    
    void setGain2(float f){
        lock();
        eye2.setGain(f);
        unlock();
    }
    void setBrightness2(float f){
        lock();
        eye2.setBrightness(f);
        unlock();
    }
    
    void setSmoothing(float _smoothing){
        lock();
        smoothing = _smoothing;
        unlock();
    }
    
    

    
private:
    ofVideoGrabber iSight;
    ofxPS3EyeGrabber eye1, eye2;

    ofPixels image, prevImage, finalImage;
    ofPixels smoothedImage;

    
    ofxCvGrayscaleImage currentCvImage;
    ofxCvGrayscaleImage prevCvImage;
    ofxCvGrayscaleImage diff;

    float avgDiff;
    
    ofPixels smoothImage(ofPixels oldPix, ofPixels newPix, float smoothing){
        
        for (int i=0; i< smoothedImage.size();i++){
            //try{
                smoothedImage[i] = (oldPix[i]*smoothing )+ (newPix[i]*(1-smoothing));
                //cout<<smoothedImage[i]<<endl;
           // }catch (...){
                
           //  }
        }
        return smoothedImage;
        
    }
    
    void updateCv(ofPixels _pix){
        prevCvImage = currentCvImage;
        currentCvImage.setFromPixels(_pix);
        
        diff.absDiff(prevCvImage, currentCvImage);
        
        int val = 0;
        int skip =2;
        for(int i=0;i<diff.getPixels().size();i+=skip){
            val += diff.getPixels()[i] ;
        }
        avgDiff = val / (diff.getPixels().size()/skip);
        
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
                            
                            if (thisPoint.distance(thatPoint) < maxDist && thisPoint != thatPoint) tempInternalConnections.push_back( pair<ofPoint, ofPoint>(thisPoint,thatPoint));
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
