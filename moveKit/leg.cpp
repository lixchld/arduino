/*************************************************** 
  This is a library for servo drived move kit

  Written by rex li  
 ****************************************************/

#include "leg.h"

leg::leg(){
    upperJoint = Joint();
    lowerJoint = Joint();
    mode = walk;
}

void leg::setup(uint8_t upperServoNum, uint8_t lowerServoNum){
    upperJoint.setup( upperServoNum );
    lowerJoint.setup( lowerServoNum ); 
}

void leg::update(){
    //TODO:
}

moveMode leg::setMode( moveMode mode){
    moveMode oldMode = this->mode;
    this->mode = mode;
    return oldMode;
}

bool leg::setData( uint8_t jointId, uint8_t cnt, movement* pData){

}

