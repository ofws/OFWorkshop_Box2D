#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackgroundHex(0xfdefc2);

    box2d.init();
    box2d.setFPS(60);
    box2d.setGravity(0, 10);
    box2d.createBounds();
	box2d.registerGrabbing();
    box2d.setIterations(40, 20);

    //circle
    circle.setPhysics(3.0, 0.53, 0.1);
    circle.setup(box2d.getWorld(), ofGetWidth()/2, ofGetHeight()/2-100, 30);
    
    //rectangle
    rect.setPhysics(3.0, 0.53, 0.1);
    rect.setup(box2d.getWorld(), ofGetWidth()/2,ofGetHeight()/2,100,100);
    
    //edgeLine
    edgeLine.addVertex(300, 600);
    edgeLine.addVertex(ofGetWidth()/2,600);
    edgeLine.addVertex(724,600);
    edgeLine.setPhysics(0.0, 0.5, 0.5);
    edgeLine.create(box2d.getWorld());
    
    //triangle
    ofPoint triPos(512,200);
    triangle.addTriangle(ofPoint(triPos.x,triPos.y-30), ofPoint(triPos.x-30,triPos.y+30),ofPoint(triPos.x+30,triPos.y+30));
    triangle.setPhysics(3.0, 0.53, 0.1);
    triangle.create(box2d.getWorld());
    
    //star
    ofPoint starPos(512,100);
    diffShape.addVertex(starPos.x, starPos.y-50);
    diffShape.addVertex(starPos.x+14, starPos.y-20);
    diffShape.addVertex(starPos.x+47, starPos.y-15);
    diffShape.addVertex(starPos.x+23, starPos.y+7);
    diffShape.addVertex(starPos.x+29, starPos.y+40);
    diffShape.addVertex(starPos.x, starPos.y+25);
    diffShape.addVertex(starPos.x-29, starPos.y+40);
    diffShape.addVertex(starPos.x-23, starPos.y+7);
    diffShape.addVertex(starPos.x-47, starPos.y-15);
    diffShape.addVertex(starPos.x-14, starPos.y-20);
    
    diffShape.setPhysics(3.0, 0.53, 0.1);
    diffShape.create(box2d.getWorld());
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    box2d.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetHexColor(0x90d4e3);
    circle.draw();
    
    ofSetHexColor(0xe63b8b);
    rect.draw();
    
    
    ofSetColor(30);
    edgeLine.updateShape();
    edgeLine.draw();
    
    ofSetColor(232,190,79);
    triangle.draw();
    
    ofSetColor(21,84,132);
    diffShape.draw();
    
    // some debug information
	string info;
    info += "Total Bodies: "+ofToString(box2d.getBodyCount())+"\n";
	info += "Total Joints: "+ofToString(box2d.getJointCount())+"\n\n";
	info += "FPS: "+ofToString(ofGetFrameRate())+"\n";
    ofSetHexColor(0x444342);
	ofDrawBitmapString(info, 10, 15);
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
