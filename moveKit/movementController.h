/*************************************************** 
  This is a library for servo drived move kit

  Written by rex li  
 ****************************************************/
#ifndef _MOVEMENT_CONTROLER_H_
#define _MOVEMENT_CONTROLER_H_

#include "leg.h"


enum moveMode {
    unknown = 0,
    stopped = 1,
    walking = 2,
    running = 4,
    stopping = 8
}

class movementController{
    protected:
        leg* pLeg;
        uint8_t movementCnt;
        movement movements[];

    public:
        movementController();

        /**************************************************************************/
        /*! 
        // @brief initialize the controller instance
        */
        /**************************************************************************/
        void setup();

        /**************************************************************************/
        /*! 
        // @brief calibrate the movement of the leg. the 
        // @return old mode 
        */
        /**************************************************************************/          
        moveMode changeMode(moveMode mode);

        /**************************************************************************/
        /*! 
        // @brief calibrate the movement of the leg. the 
        // @return true, if successed; otherwise, false 
        */
        /**************************************************************************/  
        bool calibrate( moveMode mode, calibration* pCalibation);

        /**************************************************************************/
        /*! 
        // @brief update the status of leg
        // @return void
        */
        /**************************************************************************/        
        void update();
};

#endif //_MOVEMENT_CONTROLER_H_