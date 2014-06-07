

#pragma once
#include "ofMain.h"
#include "ofxBox2dBaseShape.h"

/*
 to use this, you need to add following code in ofxBox2d.h after #pragma once:
 
 #include "ofxBox2dCustomized.h"
 */

class ofxBox2dCustomized : public ofxBox2dBaseShape {

private:
    float width, height;
    float radius;
    ofPoint circlePos;
    ofPoint rectPos;
    ofPoint SensorPos;

public:

	void setup(b2World * b2dworld, float x, float y, float w, float h);
	   
    void draw();

    int bGround;
};














