#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"

enum _moveState {
    MS_STOP,
    MS_LEFT,
    MS_RIGHT,
};

class userData{
public:
	int hits;
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
        // this is the function for contacts
        void contactStart(ofxBox2dContactArgs &e);
        void contactEnd(ofxBox2dContactArgs &e);
    
        ofxBox2d world;
        vector<ofPtr<ofxBox2dRect> > rects;
        ofxBox2dCircle circle;
        ofxBox2dRect rect;
        vector<ofPtr <ofxBox2dEdge> >  edgeLines;
        ofPolyline drawing;
    
        ofxBox2dCustomized character;
        bool jump, bGround;
        _moveState moveState;
    
        int moveSpeed;
        int timer;
};
