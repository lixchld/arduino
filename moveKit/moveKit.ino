#include "joint.h" 

Joint joint = Joint(0);
int targetPos = 0;
int pos[3];
int i=0;

void setup() {
  joint.setSpeed(5);
  joint.setPosition(pos[0]);
  pos[0] = 30;
  pos[1] = 45;
  pos[2] = 60;
  pos[3] = 90;
}

void loop() {
  if( joint.update() == targetPos ){
    targetPos = pos[++i];
    
    joint.setPosition(targetPos);
  }
  delay( 500);

  if(i> 3) i=0;
  
}
