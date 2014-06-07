

#pragma once
#include "ofMain.h"
#include "ofxBox2dBaseShape.h"

// It would be nice to use ofRectangle but it is top/left and
// box2d needs a center rectangle.

class ofxBox2dCustomized : public ofxBox2dBaseShape {

private:
    float width, height;
    float radius;
    ofPoint circlePos;
    ofPoint rectPos;
    ofPoint SensorPos;
public:

	//------------------------------------------------
	void setup(b2World * b2dworld, float x, float y, float w, float h);
	//------------------------------------------------
    float getWidth()  { return width * 2;  }
    float getHeight() { return height * 2; }
    
    void draw();

    int bGround;
};














