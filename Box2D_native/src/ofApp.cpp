#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(30);

    world.init();
    world.setFPS(60);
    world.setGravity(0, 30);
    world.createBounds();
	world.registerGrabbing();
    world.setIterations(40, 20);
    world.enableEvents();
    
    character.setPhysics(3.0, 0.3, 0.05);
    character.setup(world.getWorld(), ofGetWidth()/2,700,40,75);
    character.body->SetFixedRotation(true);
    
    jump = false;
    bGround = false;
    moveState = MS_STOP;
   
}

//--------------------------------------------------------------
void ofApp::update(){
    
    world.update();
    
    int jumpForce = 5000;
    int maxSpeed = 10;
    float desiredVel = 0;
    
    //---------------moveState
    switch ( moveState ){
        case MS_LEFT:  desiredVel = -10; break;
        case MS_STOP:  desiredVel =  0; break;
        case MS_RIGHT: desiredVel =  10; break;
    }
    
    ofVec2f vel = character.getVelocity();
    float velChange = desiredVel - vel.x;
    float impulse = character.body->GetMass() * velChange; //disregard time factor
    character.addImpulseForce(ofVec2f(impulse,0), character.getPosition());
    
    
    //-------------moving plateform
    if (ofGetElapsedTimeMillis()-timer > 2000) {
        timer = ofGetElapsedTimeMillis();
        moveSpeed *=-1;
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    character.draw();
    
    string info;
    info += ofToString(character.getVelocity(),2) + "\n";
	ofSetColor(140);
    ofDrawBitmapString(info, character.getPosition()+ofPoint(50,0));
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

 

    if(key == 'a'){
        moveState = MS_LEFT;
    }
    
    if(key == 'd'){
        moveState = MS_RIGHT;
    }
    
    if(key == 'w'){
        jump = true;
    }
    
    
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if(key == 'a'|| key == 'd'){
        moveState = MS_STOP;
    }
    if(key == 'w'){
        jump = false;
    }

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
