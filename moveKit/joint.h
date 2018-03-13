/*************************************************** 
  This is a library for servo drived move kit

  Written by rex li  
 ****************************************************/
#ifndef _Joint_h_
#define _Joint_h_

#include <Adafruit_PWMServoDriver.h>

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
        uint8_t curPos;     // current position/angle of servo
        uint8_t targetPos;  // target position to move
        Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();;

    public:

        /**************************************************************************/
        /*! 
        // @brief Construct a joint instance
        // @param new position to move
        // @param interval between each movemvent
        */
        /**************************************************************************/
        Joint( uint8_t servoNum, int interval=1);

        /**************************************************************************/
        /*! 
        // @brief move to the target position
        */
        /**************************************************************************/
        uint8_t update();

        /**************************************************************************/
        /*! 
        // @brief set the new position to move to
        // @param new position to move
        // @return previous setting for position
        */
        /**************************************************************************/
        uint8_t setPosition( uint8_t position);

        /**************************************************************************/
        /*! 
        // @brief change the speed, it might be during an uncompleted movement
        // @param new position to move
        // @param new speed
        // @return old speed
        */
        /**************************************************************************/       
        uint8_t setSpeed( uint8_t speed );

        /**************************************************************************/
        /*! 
        // @brief return current speed
        // @return current speed
        */
        /**************************************************************************/   
        uint8_t getCurSpeed();

        /**************************************************************************/
        /*! 
        // @brief return current position
        // @return current position        */
        /**************************************************************************/   
        uint8_t getCurPosition();
};

#endif //_Joint_h_
