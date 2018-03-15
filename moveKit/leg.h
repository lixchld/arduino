/*************************************************** 
  This is a library for servo drived move kit

  Written by rex li  
 ****************************************************/
#ifndef _LEG_H_
#define _LEG_H_

#include "joint.h"

#define JOINT_CNT 2

struct movement{
    uint8_t sourcePosition; // source position
    uint8_t targetPosition; // target position
    uint8_t updateInterval; // update interval in milisecond
    uint8_t increment;      // increment of angle for each step
    uint8_t id;             // unique identifier of the movement
    bool    updateChildren; // update children's position
};

struct calibration{
    unsigned long startTime;// start time in millisecond
    unsigned long endTime;  // end time in millisecond
    movement* pMovement;    // pointer of the movement 
};

class leg{
    protected: 
        Joint joints[2];
        movement* ppMovement[2];
        uint8_t movementCnt[2];

        int targetPos[JOINT_CNT];
        int curPos[JOINT_CNT];
        int curMovementIndex[JOINT_CNT]={0, 0};        

    public:
        leg();

        void setup(uint8_t upperServoNum, uint8_t lowerServoNum);

        bool setData( uint8_t jointId, uint8_t cnt, movement* pData, bool changeNow = false);

        void update();
};

#endif //_LEG_H_
