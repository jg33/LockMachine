#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    syphonServe.setName("String Machine");
    oscIn.setup(6666);
    ofSetVerticalSync(true);
    ofSetSmoothLighting(true);
    
    circles = (CircleScene*) sceneManager.add(new CircleScene());
    sceneManager.add(new ParticleScene());
    hullScene = (ConvexHullScene*) sceneManager.add(new ConvexHullScene());
    sceneManager.gotoScene("ConvexHull", true);
    sceneManager.setup(true);
    ofSetLogLevel("ofxSceneManager", OF_LOG_VERBOSE);
    setSceneManager(&sceneManager);

    
    ////CONTROL PANEL//////
    addTransformControls();
    setDrawControlPanel(true);
    setDrawFramerate(true);
    
    controlPanel.addPanel("ConvexHull Control",1);
    controlPanel.setWhichPanel("ConvexHull Control");
    controlPanel.addSlider2D("Hulls Offset", "Hull Offset", 0, 0, -500, 500, -500, 500, true);

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
    ofxOscMessage msg;
    
    while (oscIn.hasWaitingMessages()){
        oscIn.getNextMessage(&msg);
        vector<string> address = ofSplitString(msg.getAddress(),"/");

        if(address[1] == "mic"){
            micInputs[ofToInt(address[2])]= msg.getArgAsFloat(0);
            cout<< msg.getAddress() <<endl;
            
        } else if ( address[1] == "dancer"){
            dancers[ofToInt(address[2])] = ofVec3f(msg.getArgAsFloat(0),msg.getArgAsFloat(1),msg.getArgAsFloat(2));
        } else if (address[1] == "POI" && address[3] == "pos"){
            POIs[ofFromString<int>(address[2])] = ofVec3f(msg.getArgAsFloat(0), msg.getArgAsFloat(1), msg.getArgAsFloat(2));
            
        } else if(address[1] == "POI" && address[3] == "power"){
            POIpower[ofFromString<int>(address[2])] = msg.getArgAsFloat(0);
        }
        
    }
    
    
    
    circles->setSizes(micInputs);
    //connections->setPoints(&POIs);
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    popTransforms();
    
    syphonServe.publishScreen();
    
    //drawControlPanel();
    //drawFramerate(10, 10);
}

void ofApp::onGuiEvent(guiCallbackData & d){
    if (ofIsStringInString(d.getXmlName(), "POI")){
        vector <string> poiNum = ofSplitString(d.getXmlName(), "I");
        POIs[ofFromString<int>(poiNum[1])] = ofVec3f(d.getFloat(0),d.getFloat(1));
        cout<< "set POI!"<<endl;
    }
    
    if (d.getDisplayName() == "Hulls Offset"){
        hullScene->offsetX = d.getInt(0);
        hullScene->offsetY = d.getInt(1);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key){
            case 'd':
            bDebug = !bDebug;
            hullScene->bIsDebug = bDebug;
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
