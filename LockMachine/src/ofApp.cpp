#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    syphonServe.setName("String Machine");
    oscIn.setup(6666);
    ofSetVerticalSync(true);
    ofSetSmoothLighting(true);

    
    ///CAMERA////
    //cam = ofVideoGrabber();
    
    //grabber.setDeviceID(1);
    //grabber.setup(640, 480);
    
    cvMan.setup();
    //cvMan.startThread();

    
    ///SCENE STUFF///
    circles = (CircleScene*) sceneManager.add(new CircleScene());
    sceneManager.add(new ParticleScene());
    hullScene = (ConvexHullScene*) sceneManager.add(new ConvexHullScene(&cvMan, &syphonServe));
    containment = (ContainmentPairScene*) sceneManager.add(new ContainmentPairScene(&cvMan, &syphonServe));
    
    
    
    sceneManager.gotoScene("ContainmentPair", true);
    sceneManager.setup(true);
    ofSetLogLevel("ofxSceneManager", OF_LOG_VERBOSE);
    setSceneManager(&sceneManager);

    
    ////CONTROL PANEL//////
    addTransformControls();
    setDrawControlPanel(true);
    setDrawFramerate(true);
    
    controlPanel.addPanel("ConvexHull Control",1);
    controlPanel.setWhichPanel("ConvexHull Control");
    controlPanel.addSlider2D("Hulls Offset", "hullOffset", 0, 0, -500, 500, -500, 500, true);
    controlPanel.addSlider("CV Threshold", "cvThreshold", 50, 0, 100, true);
    controlPanel.addSlider("Min CV Contours", "cvMin", 10, 0, 200, true);
    controlPanel.addSlider("Max CV Contours", "cvMax", 1000, 100, 100000, true);
    controlPanel.addSlider("Num CV Considered", "cvNConsidered", 1000, 0, 2400, true);
    controlPanel.addToggle("Draw Internals", "drawInternals", false);
    controlPanel.addToggle("Draw Externals", "drawExternals", false);
    controlPanel.addSlider("Maximum Distance", "MaxDist", 50, 0, 100, true);
    controlPanel.addSlider("Input Smoothing", "InputSmoothing", 0.5, 0, 1, false);

    controlPanel.addPanel("Extras", 1);
    controlPanel.setWhichPanel("Extras");
    controlPanel.addSlider2D("POI0", "POI0", ofGetWidth()/2, ofGetHeight()/2, 0, ofGetWidth(), 0, ofGetHeight(), false);
    controlPanel.addSlider2D("POI1", "POI1", ofGetWidth()/2, ofGetHeight()/2, 0, ofGetWidth(), 0, ofGetHeight(), false);
    controlPanel.addSlider2D("POI2", "POI2", ofGetWidth()/2, ofGetHeight()/2, 0, ofGetWidth(), 0, ofGetHeight(), false);
    controlPanel.addSlider2D("POI3", "POI3", ofGetWidth()/2, ofGetHeight()/2, 0, ofGetWidth(), 0, ofGetHeight(), false);
    
    controlPanel.setupEvents();
    controlPanel.enableEvents();
    ofAddListener(controlPanel.guiEvent, this, &ofApp::onGuiEvent);
    
    //////SCENE SPECIFICS/////////

    
    for(int i=0;i<50;i++){
        //POIs[i] = ofVec3f(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()));
       // POIpower[i] = ofRandom(1);
    }

}

//--------------------------------------------------------------
void ofApp::update(){
    cvMan.update();
    
    ofxOscMessage msg;
    
    while (oscIn.hasWaitingMessages()){
        oscIn.getNextMessage(&msg);
        vector<string> address = ofSplitString(msg.getAddress(),"/");

        if(address[1] == "mic"){
          //  micInputs[ofToInt(address[2])]= msg.getArgAsFloat(0);
            cout<< msg.getAddress() <<endl;
            
        } else if ( address[1] == "dancer"){
         //   dancers[ofToInt(address[2])] = ofVec3f(msg.getArgAsFloat(0),msg.getArgAsFloat(1),msg.getArgAsFloat(2));
        } else if (address[1] == "POI" && address[3] == "pos"){
          //  POIs[ofFromString<int>(address[2])] = ofVec3f(msg.getArgAsFloat(0), msg.getArgAsFloat(1), msg.getArgAsFloat(2));
            
        } else if(address[1] == "POI" && address[3] == "power"){
           // POIpower[ofFromString<int>(address[2])] = msg.getArgAsFloat(0);
        } else if(address[1] == "leftBlob" && address[2] == "size"){
            containment->setWiggle(LEFT, msg.getArgAsFloat(0));
        }
        
    }
    
    
    
    //circles->setSizes(micInputs);
    //connections->setPoints(&POIs);
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    popTransforms();
    //drawControlPanel();
    //drawFramerate(10, 10);
}

void ofApp::exit(){
    cvMan.stopThread();
}

void ofApp::onGuiEvent(guiCallbackData & d){
    if (ofIsStringInString(d.getXmlName(), "POI")){
        vector <string> poiNum = ofSplitString(d.getXmlName(), "I");
     //   POIs[ofFromString<int>(poiNum[1])] = ofVec3f(d.getFloat(0),d.getFloat(1));
        cout<< "set POI!"<<endl;
    }
    
    if (d.getDisplayName() == "Hulls Offset"){
        hullScene->offsetX = d.getInt(0);
        hullScene->offsetY = d.getInt(1);
    } else if(d.getXmlName() == "MaxDist"){
        hullScene->maxDist = d.getInt(0);
    } else if(d.getXmlName() == "cvMin"){
        hullScene->cvMinArea = d.getInt(0);
    }else if(d.getXmlName() == "cvMax"){
        hullScene->cvMaxArea = d.getInt(0);

    }else if(d.getXmlName() == "cvNConsidered"){
        hullScene->cvNConsidered = d.getInt(0);

    }else if(d.getXmlName() == "cvThreshold"){
        hullScene->cvThreshold = d.getInt(0);
        
    } else if(d.getXmlName() == "drawInternals"){
        hullScene->bDrawInternal = d.getInt(0);
        
    }else if(d.getXmlName() == "drawExternals"){
        hullScene->bDrawExternal = d.getInt(0);
        
    }else if(d.getXmlName() == "InputSmoothing"){
        hullScene->inputSmoothing = d.getFloat(0);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key){
            case 'd':
            bDebug = !bDebug;
            hullScene->bIsDebug = bDebug;
            containment->bIsDebug = bDebug;
            break;
            case 'g':
            hullScene->bIsGrabbingBackground = !hullScene->bIsGrabbingBackground;
            break;
            case '[':
            sceneManager.prevScene();
            break;
            case ']':
            sceneManager.nextScene();
            break;
            case 'f':
            ofToggleFullscreen();
            break;
            
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    setNewScreenSize(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
