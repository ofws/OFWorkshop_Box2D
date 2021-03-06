#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"

//

enum _moveState {
    MS_STOP,
    MS_LEFT,
    MS_RIGHT,
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
		
        ofxBox2d world;
        ofxBox2dCustomized character;
        bool jump, bGround;
        _moveState moveState;
        int moveSpeed;
        int timer;
};
