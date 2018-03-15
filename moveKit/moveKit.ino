#include "leg.h" 

#define JOINT_CNT 2

//Test code for leg
movement data[2][2];
leg leg1 = leg();
uint8_t moveDataId = 0;

void initMoveData(){
  data[0][0].sourcePosition = 75;
  data[0][0].targetPosition = 105;
  data[0][0].increment = 1;
  data[0][0].updateInterval = 10;
  data[0][0].id =  moveDataId++;
  data[0][0].updateChildren = true;
  data[0][1].sourcePosition = 105;
  data[0][1].targetPosition = 75;
  data[0][1].increment = 1;
  data[0][1].updateInterval = 10;
  data[0][1].id =  moveDataId++;
  data[0][1].updateChildren = true;

  data[1][0].sourcePosition = 75;
  data[1][0].targetPosition = 105;
  data[1][0].increment = 1;
  data[1][0].updateInterval = 2;
  data[1][0].id =  moveDataId++;
  data[1][0].updateChildren = false;  
  data[1][1].sourcePosition = 105;
  data[1][1].targetPosition = 75;
  data[1][1].increment = 1;
  data[1][1].updateInterval = 2;
  data[1][1].id =  moveDataId++;  
  data[1][1].updateChildren = false;  
}

void setup(){
    Serial.begin(9600);
    initMoveData();
    leg1.setup(0, 1);
    leg1.setData( 0, 2, (movement*)data[0] );
    leg1.setData( 1, 2, (movement*)data[1] );
}

void loop(){
  leg1.update();
}

//Test code for Joint
/*
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
}*/

