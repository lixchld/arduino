#include "joint.h" 

#define JOINT_CNT 2

Joint joint[JOINT_CNT];

int targetPos[JOINT_CNT];
int curPos[JOINT_CNT];
int pos[]={45, 75, 105, 135};
int i[]={0, 3};

void setup() {
  Serial.begin(9600);

  joint[0].setup(0, 3);
  joint[0].setPosition(pos[0]);  
    
  joint[1].setup(1, 3, 2);
  joint[1].setPosition(pos[3]);  
}

void loop() {

  for(int id=0; id< JOINT_CNT; id++){
    curPos[id] = joint[id].update();
    
    if( abs(curPos[id] - targetPos[id]) < 2 ){   
      i[id]++;
      if( i[id] > 3 ) i[id]=0;
      
      targetPos[id] = pos[ i[id] ];
  
      //Serial.print("set new position:");
      //Serial.println(targetPos);
      joint[id].setPosition(targetPos[id]);
    }
  }

  /*
  int curPos = joint.update();
  //Serial.print("curPos = ");
  //Serial.println(curPos);

  if( abs(curPos - targetPos) < 2 ){
    i++;
    if( i > 3 ) i=0;
    
    targetPos = pos[i];

    //Serial.print("set new position:");
    //Serial.println(targetPos);
    joint.setPosition(targetPos);
  }*/

  
}
