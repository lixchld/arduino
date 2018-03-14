/*************************************************** 
  This is a library for servo drived move kit

  Written by rex li  
 ****************************************************/
#ifndef _MOVEMENT_CONTROLER_H_
#define _MOVEMENT_CONTROLER_H_

#include "leg.h"

class movementController{
    protected:
        leg* pLeg;
        uint8_t movementCnt;
        movement movements[];

    public:
        movementController();

        void setup();

        
};

#endif //_MOVEMENT_CONTROLER_H_