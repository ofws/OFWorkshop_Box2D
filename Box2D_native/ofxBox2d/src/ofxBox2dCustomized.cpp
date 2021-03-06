

#include "ofxBox2dCustomized.h"

//------------------------------------------------
void ofxBox2dCustomized::setup(b2World * b2dworld, float x, float y, float w, float h) {

    w /= 2;
    h /= 2;
	width = w; height = h;
    //------------------------------------------------create dynamic body
	b2BodyDef bodyDef;
	if(density == 0.f) bodyDef.type	= b2_staticBody;
	else               bodyDef.type	= b2_dynamicBody;
	bodyDef.position.Set(x/OFX_BOX2D_SCALE, y/OFX_BOX2D_SCALE);
	body = b2dworld->CreateBody(&bodyDef);
    //------------------------------------------------add fixtures
    //--this is rectangle fixture
    b2PolygonShape shape;
    shape.SetAsBox(width/OFX_BOX2D_SCALE, height/OFX_BOX2D_SCALE,b2Vec2(0,0),0);
	fixture.shape		= &shape;
	fixture.density		= density;
	fixture.friction	= friction;
	fixture.restitution = bounce;
    body->CreateFixture(&fixture);
    
    //--this is circle fixture
    b2CircleShape circle;
    circlePos.set(0, h);
    circle.m_radius		= w/OFX_BOX2D_SCALE;
	circle.m_p.Set(circlePos.x/OFX_BOX2D_SCALE, circlePos.y/OFX_BOX2D_SCALE);
    fixture.shape		= &circle;
	fixture.density		= density;
	fixture.friction	= friction;
	fixture.restitution = bounce;
    body->CreateFixture(&fixture);
    
    alive = true;
    bGround = false;
}


//------------------------------------------------
void ofxBox2dCustomized::draw() {
	
	if(body == NULL) {
		return;	
	}
    
    //-------------------------------------get fixtures shapes
    b2Vec2 circlePos;
    float r;
    const b2Transform& xf = body->GetTransform();
    ofPolyline shapes;
    //---------this is how you access all fixtures
    for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext()) {
         b2Shape::Type shapeType = f->GetType();
         if (shapeType == b2Shape::e_circle){
                b2CircleShape* circle = (b2CircleShape*)f->GetShape();
                r =  circle->m_radius * OFX_BOX2D_SCALE;
                circlePos = b2Mul(xf,circle->m_p);
         }
        else if (shapeType == b2Shape::e_polygon)
         {
             ofPolyline line;
             b2PolygonShape* poly = (b2PolygonShape*)f->GetShape();
             for(int i=0; i<poly->m_count; i++) {
                 b2Vec2 pt = b2Mul(xf, poly->m_vertices[i]);
                 shapes.addVertex(worldPtToscreenPt(pt));
             }
         }
     }
    
    //--------------------------draw rect
    ofSetColor(145,192,219);
    ofBeginShape();
    vector<ofPoint>& vertices = shapes.getVertices();
    for(int j = 0; j < vertices.size(); j++) {
        ofVertex(vertices[j]);
    }
    ofEndShape();
    
    //--------------------------draw circle
    ofColor c(248,40,94);
    ofSetColor(c);
    ofCircle(worldPtToscreenPt(circlePos), r);
    
    //--------------------------draw eyes
    ofSetColor(255);
    ofCircle(getPosition().x, getPosition().y-height/3*2, width/3*2);
    ofSetColor(30);
    ofCircle(getPosition().x, getPosition().y-height/3*2, width/5*2);

}
















