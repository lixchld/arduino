/*************************************************** 
  This is a library for servo drived move kit

  Written by rex li  
 ****************************************************/
#ifndef _LEG_H_
#define _LEG_H_

#include "joint.h"

enum moveMode {
    unknown = 0,
    stopped = 1,
    walking = 2,
    running = 4,
    stopping = 8
}

struct movement{
    uint8_t targetPosition;
    uint8_t updateInterval;
    uint8_t increment;
}

class leg{

    protected: 
        Joint upperJoint;
        Joint lowerJoint;
        moveMode mode;
        movement* pUpperData;
        movement* pLowerData;

    public:
        leg();

        void setup(uint8_t upperServoNum, uint8_t lowerServoNum);

        moveMode setMode( moveMode mode );

        bool setData( uint8_t jointId, uint8_t cnt, movement* pData);

        void update();
};

#endif //_LEG_H_