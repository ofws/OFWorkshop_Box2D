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
    //--------------------------- rects
    for(int i=0; i<100;i++){
        rects.push_back(ofPtr<ofxBox2dRect>(new ofxBox2dRect));
        rects.back()->setPhysics(3.0, 0.3, 0.05);
        rects.back()->setup(world.getWorld(), ofRandom(0,ofGetWidth()),ofRandom(ofGetHeight()/2,ofGetHeight()-30),ofRandom(30),ofRandom(80));
    }
    //--------------------------- moving platform
    rect.setPhysics(0, 0.3, 0.1);
    rect.setup(world.getWorld(), 500,ofGetHeight()/4,180,25);
    moveSpeed = 1;
    timer = ofGetElapsedTimeMillis();
    //--------------------------- character
    character.setPhysics(3.0, 0.3, 0.05);
    character.setup(world.getWorld(), ofGetWidth()/2,700,40,75);
    character.body->SetFixedRotation(true);
    // --------------- set user data
    character.setData(new userData());
    userData * data = (userData*)character.getData();
    data->hits	= 0;
    //------------------- moveState
    jump = false;
    bGround = false;
    moveState = MS_STOP;
    //------------- register the listener so that we get the events
	ofAddListener(world.contactStartEvents, this, &ofApp::contactStart);
	ofAddListener(world.contactEndEvents, this, &ofApp::contactEnd);
    
}
//--------------------------------------------------------------
void ofApp::contactStart(ofxBox2dContactArgs &e){

    if(e.a != NULL && e.b != NULL) {
    
        userData * aData = (userData*)e.a->GetBody()->GetUserData();
        userData * bData = (userData*)e.b->GetBody()->GetUserData();
        
        
        if(aData && e.a->IsSensor()) {
            aData->hits ++;
        }
        
        if(bData && e.b->IsSensor()) {
            bData->hits ++;
        }
        
    }
}

//--------------------------------------------------------------
void ofApp::contactEnd(ofxBox2dContactArgs &e){
    if(e.a != NULL && e.b != NULL) {
        
        userData * aData = (userData*)e.a->GetBody()->GetUserData();
        userData * bData = (userData*)e.b->GetBody()->GetUserData();
        
        if(aData && e.a->IsSensor()) {
            aData->hits --;
        }
        
        if(bData && e.b->IsSensor()) {
            bData->hits --;
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
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
    
    
    userData * data = (userData*)character.getData();
    data->hits>0 ? bGround = true : bGround =false;
    character.bGround = bGround;
    
    if (jump && bGround) {
        jump = false;
        character.setVelocity(character.getVelocity().x, character.getVelocity().y-5);
        character.addImpulseForce(ofVec2f(0, -jumpForce), character.getPosition());
    }
    
    //-------------moving plateform
    if (ofGetElapsedTimeMillis()-timer > 2000) {
        timer = ofGetElapsedTimeMillis();
        moveSpeed *=-1;
    }
    rect.setPosition(rect.getPosition().x+moveSpeed, rect.getPosition().y);
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    character.draw();
    
	
    for(int i=0; i<edgeLines.size(); i++){
        edgeLines[i].get()->updateShape();
        ofSetColor(120);
        edgeLines[i].get()->draw();
    }
    
    ofSetColor(140);
    drawing.draw();
    
    ofSetColor(142, 117, 199);
    rect.draw();
    
    for (int i=0; i<rects.size(); i++) {
        ofSetColor(196, 41, 116);
        rects[i].get()->draw();
    }
    
    string info;
    info += ofToString(character.getVelocity(),2) + "\n";
    info += ofToString("ground: "+ ofToString(bGround)) + "\n";
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

    drawing.addVertex(x,y);

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
  
    if (edgeLines.size()>1) {
        edgeLines.erase(edgeLines.begin());
    }
    
    drawing.addVertex(x,y);
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

    drawing.setClosed(false);
	drawing.simplify();
    
    edgeLines.push_back(ofPtr<ofxBox2dEdge>(new ofxBox2dEdge));
    edgeLines.back().get()->addVertexes(drawing);
    edgeLines.back().get()->setPhysics(0.0, 0.5, 0.5);
    edgeLines.back().get()->create(world.getWorld());
    
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
