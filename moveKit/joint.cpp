#include "joint.h"

/**************************************************************************/
/*! 
// @brief Construct a joint instance
// @param new position to move
// @param interval between each movemvent
*/
/**************************************************************************/
Joint::Joint( ){
    this->servoNum = 0;
    updateInterval = 3;
    lastUpdate = 0;
    increment = 1;
};

/**************************************************************************/
/*! 
// @brief initialize the jiont instance
// @param new position to move
// @param interval between each movemvent
*/
/**************************************************************************/
void Joint::setup( uint8_t servoNum, int interval, int increment ){
    this->servoNum = servoNum;
    updateInterval = interval;
    lastUpdate = 0;
    this->increment = increment;
    speed = 10;

    pwm.begin();
    pwm.setPWMFreq(60);
}
        

/**************************************************************************/
/*! 
// @brief move to the target position
// @return the current position
*/
/**************************************************************************/
int Joint::update(){
  
#ifdef _DEBUG_OUTPUT_ENABLED
  Serial.print( "Joint.curPos = ");
  Serial.print( curPos );
  Serial.print( " Joint.targetPos = ");
  Serial.println( targetPos);
#endif

    if(curPos == targetPos )
        return curPos;

    if((millis() - lastUpdate) > updateInterval)  // time to update
    {
      lastUpdate = millis();

        if( targetPos > curPos ){
          curPos += increment;
          if( curPos > targetPos ) curPos = targetPos;
        }
        else{
          curPos -= increment;
          if( curPos < targetPos ) curPos = targetPos;
        }
          
        #ifdef _DEBUG_OUTPUT_ENABLED
          Serial.print( "Joint.setPWM: ");
          Serial.println( curPos );
        #endif    
        pwm.setPWM(servoNum, 0, curPos);
        
        if(speed < 10)
            delay(10-speed);           
    }
    return map( curPos, SERVOMIN, SERVOMAX, 0, 180);
}


/**************************************************************************/
/*! 
// @brief set the new position to move to
// @param new position to move
// @return previous setting for position
*/
/**************************************************************************/
int Joint::setPosition( uint8_t position){
    int oldPos = targetPos;
    targetPos =  map( position, 0, 180, SERVOMIN, SERVOMAX);
    return map( oldPos,SERVOMIN, SERVOMAX, 0, 180);
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
    uint8_t oldSpeed = speed;
    speed = speed;
    return oldSpeed;
}


/**************************************************************************/
/*! 
// @brief return current speed
// @return old speed
*/
/**************************************************************************/   
uint8_t Joint::getCurSpeed(){
    return speed;
}

/**************************************************************************/
/*! 
// @brief return current position
// @return current position
*/
/**************************************************************************/   
int Joint::getCurPosition(){
    return map( curPos,SERVOMIN, SERVOMAX, 0, 180);
}
