/*************************************************** 
  This is a library for servo drived move kit

  Written by rex li  
 ****************************************************/
#ifndef _Joint_h_
#define _Joint_h_

#include <Adafruit_PWMServoDriver.h>

//#define _DEBUG_OUTPUT_ENABLED

// 2*3.7v -> 4.0-4.74-5.0 v min=110;max=560 0-180
#define SERVOMIN  110 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  560 // this is the 'maximum' pulse length count (out of 4096)

class Joint{
    private:
        int increment;              // increment to move for each interval
        int  updateInterval;        // interval between updates
        unsigned long lastUpdate;   // last update of position    

    protected: 
        uint8_t servoNum;   // servo number
        uint8_t speed;      // speed of joint move: value speed level is from 1-10
        uint16_t curPos;     // current position/angle of servo
        uint16_t targetPos;  // target position to move
        Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();;

    public:

        /**************************************************************************/
        /*! 
        // @brief Construct a joint instance
        */
        /**************************************************************************/
        Joint();

        /**************************************************************************/
        /*! 
        // @brief initialize the jiont instance
        // @param new position to move
        // @param interval between each movemvent
        */
        /**************************************************************************/
        void setup( uint8_t servoNum, int interval=1, int increment = 1);        

        /**************************************************************************/
        /*! 
        // @brief move to the target position
        */
        /**************************************************************************/
        int update();

        /**************************************************************************/
        /*! 
        // @brief set the new position to move to
        // @param new position to move
        // @return previous setting for position
        */
        /**************************************************************************/
        int setPosition( uint8_t position);

        /**************************************************************************/
        /*! 
        // @brief change the interval, as a result the speed will change accordingly
        // @param new interval to update the postion
        // @return old interval
        */
        /**************************************************************************/       
        uint16_t setInterval( uint16_t interval );

        /**************************************************************************/
        /*! 
        // @brief change the increment of movement, as a result the speed will change accordingly
        // @param new increment is used to move to target postion
        // @return old increment
        */
        /**************************************************************************/       
        uint16_t setIncrement( uint16_t increment );

        /**************************************************************************/
        /*! 
        // @brief return current position
        // @return current position        */
        /**************************************************************************/   
        int getCurPosition();
};

#endif //_Joint_h_
