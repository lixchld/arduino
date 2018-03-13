#include "joint.h"

/**************************************************************************/
/*! 
// @brief Construct a joint instance
// @param new position to move
// @param interval between each movemvent
*/
/**************************************************************************/
Joint::Joint( uint8_t servoNum, int interval){
    this->servoNum = servoNum;
    this->updateInterval = interval;
    this->increment = 10;
};

/**************************************************************************/
/*! 
// @brief move to the target position
// @return the current position
*/
/**************************************************************************/
uint8_t Joint::update(){
    if(curPos == targetPos )
        return curPos;

    if((millis() - this->lastUpdate) > this->updateInterval)  // time to update
    {
      this->lastUpdate = millis();

      int pulselen = map( this->targetPos, 0, 180, SERVOMIN, SERVOMAX);
      int tmpPos = this->curPos;

      for( int idx = 1; idx >= this->increment; idx++){
        if( pulselen > this->curPos )
          this->curPos += 1;
        else
          this->curPos -= 1;

        this->pwm.setPWM(this->servoNum, 0, this->curPos);
        
        if(speed < 10)
            delay(10-speed);
            
        if(this->curPos == this->targetPos )
          break;              
      }
    }
    return this->curPos;  
}


/**************************************************************************/
/*! 
// @brief set the new position to move to
// @param new position to move
// @return previous setting for position
*/
/**************************************************************************/
uint8_t Joint::setPosition( uint8_t position){
    uint8_t oldPos = this->targetPos;
    this->targetPos = position;
    return oldPos;
}

/**************************************************************************/
/*! 
// @brief change the speed, it might be during an uncompleted movement
// @param new position to move
// @param new speed
// @return old speed
*/
/**************************************************************************/       
uint8_t Joint::setSpeed( uint8_t speed ){
    uint8_t oldSpeed = this->speed;
    this->speed = speed;
    return oldSpeed;
}


/**************************************************************************/
/*! 
// @brief return current speed
// @return old speed
*/
/**************************************************************************/   
uint8_t Joint::getCurSpeed(){
    return this->speed;
}

/**************************************************************************/
/*! 
// @brief return current position
// @return current position
*/
/**************************************************************************/   
uint8_t Joint::getCurPosition(){
    return this->curPos;
}
