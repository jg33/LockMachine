#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    syphonServe.setName("String Machine");
    oscIn.setup(6666);
    
    setSceneManager(&sceneManager);
    circles = (CircleScene*) sceneManager.add(new CircleScene());
    sceneManager.add(new ParticleScene());
    sceneManager.gotoScene("Particles");
    
    addTransformControls();
    setDrawControlPanel(true);
    setDrawFramerate(true);
    
    cout<< isDebug()<<endl;
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
        }
        
    }
    
    circles->setSizes(micInputs);
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    syphonServe.publishScreen();
    
    //drawControlPanel();
    //drawFramerate(10, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    bDebug=true;
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
