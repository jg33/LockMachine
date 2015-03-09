#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    syphonServe.setName("Lock Machine");
    rawServer.setName("Raw Feed");
    oscIn.setup(6666);

    
    ofSetVerticalSync(true);
    ofSetSmoothLighting(true);
    
    cvMan.setup();

    
    ///SCENE STUFF///
    //circles = (CircleScene*) sceneManager.add(new CircleScene());
    //partScene = (ParticleScene*) sceneManager.add(new ParticleScene(&syphonServe));
    hullScene = (ConvexHullScene*) sceneManager.add(new ConvexHullScene(&cvMan, &syphonServe));
    //web = (WebScene*) sceneManager.add(new WebScene() );
    sceneManager.add(new RawScene(&cvMan, &syphonServe));
    //sceneManager.add(new ConeScene(&cvMan, &syphonServe));
    sceneManager.add(new DifferenceScene(&cvMan, &syphonServe));
    sceneManager.add(new MeshBuildScene(&cvMan, &syphonServe));
    
    sceneManager.gotoScene("RawFeed", true);
    sceneManager.setup(true);
    ofSetLogLevel("ofxSceneManager", OF_LOG_VERBOSE);
    setSceneManager(&sceneManager);

    
    ////CONTROL PANEL//////
    addTransformControls();
    setDrawControlPanel(true);
    setDrawFramerate(true);
    
    controlPanel.addPanel("Camera Control", 1);
    controlPanel.setWhichPanel("Camera Control");
    controlPanel.addSlider("Input Smoothing", "InputSmoothing", 0.9, 0, 1, false);
    controlPanel.addSlider("Eye1 Gain", "1gain", 32, 0, 63, false);
    controlPanel.addSlider("Eye1 Brightness", "1brightness", 32, 0, 63, false);
    controlPanel.addSlider("Eye2 Gain", "2gain", 32, 0, 63, false);
    controlPanel.addSlider("Eye2 Brightness", "2brightness", 32, 0, 63, false);
    controlPanel.addToggle("Caluclate CV", "calcCv", true);
    controlPanel.addToggle("Glitch Catching", "glitchCatching", true);
    
    controlPanel.addPanel("ConvexHull Control",1);
    controlPanel.setWhichPanel("ConvexHull Control");
    controlPanel.addSlider2D("Hulls Offset", "hullOffset", 0, 0, -500, 500, -500, 500, true);
    controlPanel.addSlider("CV Threshold", "cvThreshold", 50, 0, 100, true);
    controlPanel.addSlider("Min CV Contours", "cvMin", 100, 0, 200, true);
    controlPanel.addSlider("Max CV Contours", "cvMax", 7000, 100, 100000, true);
    controlPanel.addSlider("Num CV Considered", "cvNConsidered", 1000, 0, 2400, true);
    controlPanel.addToggle("Draw Internals", "drawInternals", true);
    controlPanel.addToggle("Draw Externals", "drawExternals", true);
    controlPanel.addSlider("Maximum Distance", "MaxDist", 70, 0, 100, true);
    controlPanel.addSlider("Contour Simplificaiton", "ContSimp", 3, 0, 30, false);

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
    
    cvMan.startThread();

}

//--------------------------------------------------------------
void ofApp::update(){
    //cvMan.update();
    
    ofxOscMessage msg;
    
    while (oscIn.hasWaitingMessages()){
        oscIn.getNextMessage(&msg);
        processOsc(msg);
        
    }
    
    
    ofSetWindowTitle(sceneManager.getCurrentSceneName()+" @ "+  ofToString(ofGetFrameRate())+ " | grabbingBG: "+ ofToString(hullScene->bIsGrabbingBackground) );
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    popTransforms();
    ofSetLineWidth(1);
    //drawControlPanel();
    //drawFramerate(10, 10);
    rawServer.publishTexture(&cvMan.getFrame().getTexture());
}

void ofApp::exit(){
    cvMan.waitForThread();
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
    } else if(d.getXmlName() == "cvMax"){
        hullScene->cvMaxArea = d.getInt(0);

    } else if(d.getXmlName() == "cvNConsidered"){
        hullScene->cvNConsidered = d.getInt(0);

    } else if(d.getXmlName() == "cvThreshold"){
        hullScene->cvThreshold = d.getInt(0);
        
    } else if(d.getXmlName() == "drawInternals"){
        hullScene->bDrawInternal = d.getInt(0);
        
    } else if(d.getXmlName() == "drawExternals"){
        hullScene->bDrawExternal = d.getInt(0);
        
    } else if (d.getXmlName() == "ContSimp"){
        hullScene->simplification = d.getFloat(0);
    } else if(d.getXmlName() == "InputSmoothing"){
        cvMan.setSmoothing(d.getFloat(0)) ;
    } else if (d.getXmlName() =="1gain"){
        cvMan.setGain1(d.getFloat(0));
    } else if (d.getXmlName() =="1brightness"){
        cvMan.setBrightness1(d.getFloat(0));
    } else if (d.getXmlName() =="2gain"){
        cvMan.setGain2(d.getFloat(0));
    } else if (d.getXmlName() =="2brightness"){
        cvMan.setBrightness2(d.getFloat(0));
    } else if (d.getXmlName() == "glitchCatching"){
        cvMan.bIsCatchingGlitches = d.getInt(0);
    } else if (d.getXmlName() == "calcCv"){
        cvMan.bIsCalculatingCV = d.getInt(0);
    } else{
        cout<<"unknown UI event: "<<d.getXmlName()<<endl;
    }
    
}

void ofApp::processOsc(ofxOscMessage &msg){
    
    vector<string> address = ofSplitString(msg.getAddress(),"/");
    
    if(address[1]=="gui"){
        guiCallbackData oscGuiEvent;
        oscGuiEvent.setup(address[2],address[2]);
        oscGuiEvent.addValueF(msg.getArgAsFloat(0));
        onGuiEvent(oscGuiEvent);
    }
    
    /*
    if(address[1] == "camera"){
        cout<<"CaM!"<<endl;
        switch (msg.getArgAsInt32(0)) {
            case 1:
                cvMan.activeCamera = CAM_EYE_1;
                break;
            case 2:
                cvMan.activeCamera = CAM_EYE_2;
                break;
            default:
                break;
        }
    }
     */
    
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
    } else if(address[1] == "camera"){
        switch (msg.getArgAsInt32(0)) {
                cout<<msg.getArgAsInt32(0)<<endl;
            case 1:
                cvMan.activeCamera = CAM_EYE_1;
                break;
            case 2:
                cvMan.activeCamera = CAM_EYE_2;
                break;
            default:
                break;
        }
    }

    
    cout<< address[1]<< endl;

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key){
            case 'd':
            bDebug = !bDebug;
            hullScene->bIsDebug = bDebug;
            //]containment->bIsDebug = bDebug;
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
            case'p':
            partScene->partsToAdd = ofRandom(25,40);
            break;
            case '1':
            cvMan.activeCamera= CAM_EYE_1;
            break;
            case '2':
            cvMan.activeCamera = CAM_EYE_2;
            break;
    }
    if(sceneManager.getCurrentSceneName() == "Particles"){
        switch (key) {
            case '1':
                partScene->partsToAdd = ofRandom(1,10);
                break;
            case '2':
                partScene->partsToAdd = ofRandom(10,20);
                break;
            case '3':
                partScene->partsToAdd = ofRandom(30,40);
                break;
            case '4':
                partScene->partsToAdd = ofRandom(60,100);
                break;
            default:
                break;
        }
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
    if(sceneManager.getCurrentSceneName() == "Web"){
        web->addPoint(ofPoint(x,y));
        
    }

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
