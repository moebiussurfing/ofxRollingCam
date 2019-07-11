#include "ofxRollingCam.h"

//--------------------------------------------------------------
ofxRollingCam::ofxRollingCam(){
//    cam.disableMouseInput();
    scaleN = 1.0;
    scaleT = scaleN;
//    cam.setscaleance(ofGetHeight());
//    camSpeed = DEFAULT_CAM_SP * dt;
    camSpeed = DEFAULT_CAM_SP;

    target = ofVec3f(0, 0, 0);
//    dt = 1.0f;

    DEBUG_Text_Roll.setup();
    DEBUG_Text_Roll.setPosition( glm::vec2(223, 230) );
    DEBUG_Text_Roll.setFontSize(8);
    DEBUG_Text_Roll.setName("DEBUG ROLL");
    DEBUG_Text_Roll.setShadowVisible(false);
}

//--------------------------------------------------------------
void ofxRollingCam::set_dt(float _dt)
{
    dt = _dt;
}

//--------------------------------------------------------------
void ofxRollingCam::setTarget(ofVec3f _target){

    target = _target;
}

//--------------------------------------------------------------
void ofxRollingCam::setup(float _camSpeed,float _scaleance){
//    cam.disableMouseInput();
    scaleN =_scaleance;
    scaleT = scaleN;

//    _camSpeed *= dt;
    camSpeed = ofClamp(_camSpeed,0,1);
//    camSpeed = ofClamp(_camSpeed,0,1) * dt;
}

//--------------------------------------------------------------
void ofxRollingCam::update(){
    posS.set(posT.x-posN.x,posT.y-posN.y,posT.z-posN.z);
    posS.set(posS.x*camSpeed,posS.y*camSpeed,posS.z*camSpeed);
    posN.set(posN.x+posS.x, posN.y+posS.y,posN.z+posS.z);
    
    scaleS=scaleT-scaleN;
    scaleS=scaleS*camSpeed;
    scaleN=scaleN+scaleS;
//    cam.setscaleance(scaleN);

    // text debug
    str = "ROLLING CAMERA\n\n" ;
    str += "scaleS: " + ofToString( scaleS ) + "\n";
    str += "scaleT: " + ofToString( scaleT ) + "\n";
    str += "scaleN: " + ofToString( scaleN ) + "\n";
    str += "posS  : " + ofToString( posS ) + "\n";
    str += "posT  : " + ofToString( posT ) + "\n";
    str += "posN  : " + ofToString( posN ) + "\n";
    DEBUG_Text_Roll.setText(str);
}

//--------------------------------------------------------------
void ofxRollingCam::draw()
{
    DEBUG_Text_Roll.draw();
}

//--------------------------------------------------------------
void ofxRollingCam::begin(){
    ofPushMatrix();
////    cam.begin();

////    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);//TODO
    ofTranslate(target);

    ofRotateX(posN.x);
    ofRotateY(posN.y);
    ofRotateZ(posN.z);
    ofScale(scaleN, scaleN,scaleN);
}

//--------------------------------------------------------------
void ofxRollingCam::end(){
////    cam.end();
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofxRollingCam::setCamSpeed(float _camSpeed){
//    camSpeed = ofClamp(_camSpeed,0,1) * dt;
//    _camSpeed *= dt;
    camSpeed = ofClamp(_camSpeed,0,1);
}

//--------------------------------------------------------------
void ofxRollingCam::setRandomPos(float _randomAngle){
    ofVec3f ram3f;
    int ramSize=_randomAngle;
    ram3f.set(ofRandom(-ramSize, ramSize),ofRandom(-ramSize, ramSize),ofRandom(-ramSize, ramSize));
    posT.set(ofRandom(posN.x,(int)(posN.x+ram3f.x)%360), ofRandom(posN.y,(int)(posN.y+ram3f.y)%360),ofRandom(posN.z,(int)(posN.z+ram3f.z)%360));
}

//--------------------------------------------------------------
void ofxRollingCam::setPos(float _x,float _y,float _z){
    posT.set(_x,_y,_z);
}

//--------------------------------------------------------------
void ofxRollingCam::setRandomScale(float _min,float _max){
    scaleT=ofRandom(_min,_max);
}

//--------------------------------------------------------------
void ofxRollingCam::setScale(float _scale){
    scaleT=_scale;
}

//--------------------------------------------------------------
//void testApp::mousePressed(int x, int y, int button){
//    camSetRandom();
//}

