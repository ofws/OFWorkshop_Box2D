#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackgroundHex(0xfdefc2);

    world.init();
    world.setGravity(0, 0);

    //Uncommand these code to see change
//    world.setFPS(60);
//    world.createGround();
//    world.createBounds();
//    world.registerGrabbing();
//    world.setIterations(40, 20);

    for (int i=0; i<100; i++) {
        float offSet =  ofRandom(-100,100);
        balls.push_back(ofPtr<ofxBox2dCircle>(new ofxBox2dCircle));
        balls.back().get()->setPhysics(3.0, 0.53, 0.1);
        balls.back().get()->setup(world.getWorld(), ofGetWidth()/2+offSet, ofGetHeight()/2+offSet, 30);
    }
}

//--------------------------------------------------------------
void ofApp::update(){

    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    world.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

    for(int i=0; i<balls.size(); i++) {
		ofFill();
		ofSetHexColor(0xe63b8b);
		balls[i].get()->draw();
	}
    
    ofRemove(balls, ofxBox2dBaseShape::shouldRemoveOffScreen);
    
    string number = "Balls size = " + ofToString(balls.size());
    ofDrawBitmapString(number,50,50);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
  
    for (int i=0; i<100; i++) {
        float offSet =  ofRandom(-100,100);
        balls.push_back(ofPtr<ofxBox2dCircle>(new ofxBox2dCircle));
        balls.back().get()->setPhysics(3.0, 0.53, 0.1);
        balls.back().get()->setup(world.getWorld(), ofGetWidth()/2+offSet, ofGetHeight()/2+offSet, 30);
    }
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
