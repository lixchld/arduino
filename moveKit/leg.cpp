/*************************************************** 
  This is a library for servo drived move kit

  Written by rex li  
 ****************************************************/

#include "leg.h"

leg::leg(){
    joints[0] = Joint();             // create upper joint
    joints[1] = Joint( &joints[0] );  // create lower joint and set upper joint as parent
    ppMovement[0] = NULL;
    ppMovement[1] = NULL;
}

void leg::setup(uint8_t upperServoNum, uint8_t lowerServoNum){
    joints[0].setup( upperServoNum );
    joints[1].setup( lowerServoNum ); 
}

void leg::update(){
#ifdef _DEBUG_OUTPUT_ENABLED
  Serial.print( "Leg::update ");
#endif
  for(int jointId=0; jointId< JOINT_CNT; jointId++){
    joints[jointId].updateChildren = (ppMovement[jointId]+curMovementIndex[jointId])->updateChildren;
    curPos[jointId] = joints[jointId].update();
    
    #ifdef _DEBUG_OUTPUT_ENABLED
    Serial.print( "Leg::update [");
    Serial.print(jointId);
    Serial.print("]: curPos=");
    Serial.print(curPos[jointId]);
    Serial.print(" TargetPosition=");
    Serial.println( (ppMovement[jointId]+curMovementIndex[jointId])->targetPosition);
    #endif
     
    if( abs(curPos[jointId] - (ppMovement[jointId]+curMovementIndex[jointId])->targetPosition) <= 2 ){   
      curMovementIndex[jointId]++;
      if( curMovementIndex[jointId] > movementCnt[jointId] ) curMovementIndex[jointId]=0;
  
      #ifdef _DEBUG_OUTPUT_ENABLED
      Serial.print("set new position on Joint[");
      Serial.print(jointId);
      Serial.print("]=");      
      Serial.println( (ppMovement[jointId]+curMovementIndex[jointId])->targetPosition);
      #endif
      
      joints[jointId].setPosition( (ppMovement[jointId]+curMovementIndex[jointId])->targetPosition);
    }
  }
}


bool leg::setData( uint8_t jointId, uint8_t cnt, movement* pData, bool changeNow){
    if(jointId > 1)
        return false;
    
    if( cnt > 0){
        Serial.println("new movement data 1:");      
        movementCnt[jointId] = cnt;
        ppMovement[jointId] = pData;

        #ifdef _DEBUG_OUTPUT_ENABLED
        for( int i=0; i< cnt; i++){
          Serial.println("new movement data:");
          Serial.print("data[");
          Serial.print(i);
          Serial.print("].sourcePosition=");
          Serial.println( (pData+i)->sourcePosition);    
          
          Serial.print("data[");
          Serial.print(i);
          Serial.print("].targetPosition=");
          Serial.println( (pData+i)->targetPosition);   
          
          Serial.print("data[");
          Serial.print(i);
          Serial.print("].increment=");
          Serial.println( (pData+i)->increment);  
          
          Serial.print("data[");
          Serial.print(i);
          Serial.print("].updateInterval=");
          Serial.println( (pData+i)->updateInterval);

                  
          Serial.print("data[");
          Serial.print(i);
          Serial.print("].id=");
          Serial.println( (pData+i)->id);
        }

        #endif

        joints[jointId].setPosition( pData->targetPosition);
        joints[jointId].setIncrement(pData->increment);
        joints[jointId].setInterval(pData->updateInterval);
    }

}

