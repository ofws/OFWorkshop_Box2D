#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(30);

    box2d.init();
    box2d.setFPS(60);
    box2d.setGravity(0, 30);
    box2d.createGround();
	box2d.registerGrabbing();
    box2d.setIterations(40, 20);
   
    timer = ofGetElapsedTimeMillis();
}
//--------------------------------------------------------------
void ofApp::update(){
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    box2d.update();
    
    if(ofGetElapsedTimeMillis()-timer>200){
        timer = ofGetElapsedTimeMillis();
        circles.push_back(ofPtr<ofxBox2dCircle>(new ofxBox2dCircle));
        circles.back().get()->setPhysics(3.0, 0.3, 0.05);
        circles.back().get()->setup(box2d.getWorld(), 100, 100, 15);
        circles.back().get()->addForce(ofVec2f(10,5), 100);
    }
    
    ofRemove(circles, ofxBox2dBaseShape::shouldRemoveOffScreen);
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    for(int i=0; i<edgeLines.size(); i++){
        edgeLines[i].get()->updateShape();
        ofSetColor(200);
        edgeLines[i].get()->draw();
    }
    
    for(int i=0; i<circles.size(); i++){
        ofSetColor(142, 117, 199);
        circles[i].get()->draw();
    }
    
    ofSetColor(200);
    drawing.draw();
    
    string info;
    info += "Draw lines with mouse \n";
    info += "press 'c' = clean lines \n";
    info+= ofToString(box2d.getBodyCount());
	ofSetColor(200);
    ofDrawBitmapString(info, 100,100);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == 'c') {
        drawing.clear();
        edgeLines.clear();
    }
    
    if (key == 's') {
        
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

    drawing.addVertex(x,y);

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
  
    
    drawing.addVertex(x,y);
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

    drawing.setClosed(false);
	drawing.simplify();
    
    edgeLines.push_back(ofPtr<ofxBox2dEdge>(new ofxBox2dEdge));
    edgeLines.back().get()->addVertexes(drawing);
    edgeLines.back().get()->setPhysics(0.0, 0.5, 0.5);
    edgeLines.back().get()->create(box2d.getWorld());
    
    drawing.clear();
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
