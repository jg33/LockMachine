#pragma once



#include "ofMain.h"
#include "ofxAppUtils.h"
#include "ofxSyphon.h"
#include "ofxOsc.h"
#include "CvManager.h"

#include "Scenes.h"

class CircleScene;
class ConvexHullScene;
class ContainmentPairScene;

class ofApp : public ofxApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        void onGuiEvent(guiCallbackData & d);
    


private:
    ofxSyphonServer syphonServe;
    ofxOscReceiver oscIn;
    
    ofxSceneManager sceneManager;
    CircleScene * circles;
    ConvexHullScene * hullScene;
    ContainmentPairScene * containment;
    
    ofVideoGrabber grabber;
    CvManager cvMan;
    
   // map<int,float> micInputs;
    //map<int,ofVec3f> dancers;
   // map<int,ofVec3f> POIs;
    //map<int,float> POIpower;
    
};
