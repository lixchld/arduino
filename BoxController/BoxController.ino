
#include <AFMotor.h>
#include <Servo.h> 

int vibrationInput = 2;
volatile unsigned char vibration = 0;
int  key = 0;

//define the action code which will be executed under auto mode
int actions[] = { 'A', 'S', 'W', 'D'};

enum eBoxState {
  unknown = 0,// default value
  idle,       // box is idle  
  manualMode, // manual mode, and waiting for next command
  autoMode,   // auto mode
  err
};
eBoxState boxState = autoMode;
unsigned long lastCmdTime = 0;

/*
 b_motor_stop(): stop motor
 b_motor_com():  for Manual Operator
 b_servo_ini(); 
 b_servo_com();
 b_skill();
 */ 


//-------------------define motor----------------------------------------------//
AF_DCMotor motorL(1,MOTOR12_8KHZ);  //connect to M1
AF_DCMotor motorR(2,MOTOR12_8KHZ);  //connect to M2
int motor_speed = 80; //[modifid]motor speed 150-200,---min:100;max:255
int motor_delay = 400; //[modifid]delay time in step
int motor_speed_increase = 30;//speed increase while turn left/right

//-------------------define servo----------------------------------------------//
Servo hand_l_servo;  // create servo object to control a servo 
Servo hand_r_servo;  // create servo object to control a servo
int hand_l_pos = 90; // 
int hand_r_pos = 90; //
int hand_delay = 1;  //[modifid] speed of hand

//------------------main program-----------------------------------------------//

void setup()
{
  Serial.begin(9600);
  pinMode(vibrationInput, INPUT);
  b_motor_stop();
  b_servo_ini();

  //低电平变高电平的过程中，触发中断1，调用blink函数
  attachInterrupt(digitalPinToInterrupt(vibrationInput), blink, RISING);   
    
  delay(2000);  //waiting time
  
}


void loop()
{
  key = 0;
  
  if(Serial.available() > 0) {   

    // Quit from auto mode, and set box state to waitingCmd
    boxState = manualMode;
    lastCmdTime = millis();
    key = Serial.read();  
  }
  else{
    if( millis() - lastCmdTime > 6000 && boxState == manualMode ){
        // set the box state to the auto mode step0
        boxState = autoMode;
    }
  }
  int action = getAction( boxState );
  Serial.print("Action = ");
  Serial.println(action);
  if(action >= 30 && action <= 122) { 
    b_motor_com(action);  
    b_servo_com(action);
    b_skill(action);       
  }

    
  // servo_test();
}

int getAction( eBoxState state){
  int action = 0;

  switch( state ){
    case autoMode:
        if(vibration != 0){
          vibration = 0;
          int index = random( 0, 3);
          Serial.print("AutoMode random = ");
          Serial.println(index);
          action = actions[index];
          delay(300);
        }
        else{
          Serial.println("AutoMode no touch");          
        }
        
      break;
    case manualMode:
      Serial.print("ManualMode action = ");
      Serial.println(key);
      action = key;      
    case unknown:
    case idle:
    case err:
    default:
      break;
  }

  return action;
}

//---------------------------------motor-------------------------------//
//keyboard "w,a,s,d" for action;space for stop

void b_motor_stop(){
  motorL.run(RELEASE);
  motorR.run(RELEASE);
}

void b_motor_com(int keyword){
  //forward
  if(keyword=='w')
  {
    motorL.setSpeed(motor_speed);
    motorR.setSpeed(motor_speed);
    motorL.run(FORWARD);
    motorR.run(FORWARD);
  }
  //backward
  else if(keyword=='s'){
    motorL.setSpeed(motor_speed);
    motorR.setSpeed(motor_speed);
    motorL.run(BACKWARD);
    motorR.run(BACKWARD);
  }
  //turn left
  else if(keyword=='a'){
    motorL.setSpeed(motor_speed);
    motorR.setSpeed(motor_speed + motor_speed_increase);
    motorL.run(FORWARD);
    motorR.run(FORWARD);
  }
  //turn right
  else if(keyword=='d'){
    motorL.setSpeed(motor_speed + motor_speed_increase);
    motorR.setSpeed(motor_speed);
    motorL.run(FORWARD);
    motorR.run(FORWARD);
  }
  //forward step
  else if(keyword=='W')
  {
    motorL.setSpeed(motor_speed);
    motorR.setSpeed(motor_speed);
    motorL.run(FORWARD);
    motorR.run(FORWARD);
    delay(motor_delay); 
    b_motor_stop();
  }
  //backward step
  else if(keyword=='S'){
    motorL.setSpeed(motor_speed);
    motorR.setSpeed(motor_speed);
    motorL.run(BACKWARD);
    motorR.run(BACKWARD);
    delay(motor_delay); 
    b_motor_stop();
  }
  //turn left step
  else if(keyword=='A'){
    motorL.setSpeed(motor_speed);
    motorR.setSpeed(motor_speed);
    motorL.run(BACKWARD);
    motorR.run(FORWARD);
    delay(motor_delay); 
    b_motor_stop();
  }
  //turn right step
  else if(keyword=='D'){
    motorL.setSpeed(motor_speed);
    motorR.setSpeed(motor_speed);
    motorL.run(FORWARD);
    motorR.run(BACKWARD);
    delay(motor_delay); 
    b_motor_stop();
  }
  //Stop
  else if(keyword==' '){
    b_motor_stop();
  }
  else{
    b_motor_stop();
  }
}


//---------------------------------servo-------------------------------//
/*
Single click
 u - Left hand up
 i - Right hand up
 o - both hand up
 j - Left hand down
 k - Right hand down
 l - both hand down
 
 Double click: each hand sweep
 shift + key:  step action
 */

void b_servo_ini(){
  hand_l_servo.attach(9);  // attaches the servo on pin 9 to the servo object 
  hand_r_servo.attach(10);  // attaches the servo on pin 10 to the servo object 
  hand_l_servo.write(hand_l_pos); 
  hand_r_servo.write(hand_r_pos); 
}

void b_servo_com(int keyword){
  int pos;
  //left hand up
  if(keyword=='u')
  {
    for(pos = 0; pos < 180; pos += 1)  
    {                                
      hand_l_servo.write(180-pos);          
      delay(hand_delay);                       
    } 
  }
  //left hand down
  else if(keyword=='j'){
    for(pos = 180; pos>=1; pos-=1)    
    {                                
      hand_l_servo.write(180-pos);         
      delay(hand_delay);                    
    } 
  }

  //right hand up
  if(keyword=='i')
  {
    for(pos = 0; pos < 180; pos += 1) 
    {                                 
      hand_r_servo.write(pos);             
      delay(hand_delay);                       
    } 
  }
  //right hand down
  else if(keyword=='k'){
    for(pos = 180; pos>=1; pos-=1)    
    {                                
      hand_r_servo.write(pos);             
      delay(hand_delay);                    
    } 
  }
  //both hand up
  else if(keyword=='o'){   
    for(pos = 0; pos < 180; pos += 1) 
    {    
      hand_l_servo.write(180-pos);          
      hand_r_servo.write(pos);                                      
      delay(hand_delay);                       
    }
  }
  //both hand down
  else if(keyword=='l'){

    for(pos = 180; pos>=1; pos-=1)    
    {   
      hand_l_servo.write(180-pos);        
      hand_r_servo.write(pos);    
      delay(hand_delay);                      
    }
  }
  else  //left hand up step
  if(keyword=='U')
  {
    hand_l_pos -=10;  
    hand_l_pos = max(hand_l_pos,0);
    hand_l_servo.write(hand_l_pos);          
    delay(hand_delay);                       

  }
  //left hand down step
  else if(keyword=='J'){
    hand_l_pos +=10;      
    hand_l_pos = min(hand_l_pos,180);    
    hand_l_servo.write(hand_l_pos);         
    delay(hand_delay);                    

  }

  //right hand up step
  if(keyword=='I')
  {
    hand_r_pos +=10;     
    hand_r_pos = min(hand_r_pos,180);   
    hand_r_servo.write(hand_r_pos);             
    delay(hand_delay);                       
  }
  //right hand down step
  else if(keyword=='K'){
    hand_r_pos -=10;      
    hand_r_pos = max(hand_r_pos,0);    
    hand_r_servo.write(hand_r_pos);             
    delay(hand_delay);                    
  } 

  //both hand up step
  else if(keyword=='O'){
    hand_l_pos +=10;    
    hand_r_pos +=10;    
    hand_l_pos = max(hand_r_pos,0); 
    hand_r_pos = min(hand_r_pos,180); 
    hand_l_servo.write(180-hand_l_pos);          
    hand_r_servo.write(hand_r_pos);                                      
    delay(hand_delay);                       
  }
  //both hand down step
  else if(keyword=='L'){
    hand_l_pos -=10;    
    hand_r_pos -=10; 
    hand_l_pos = min(hand_r_pos,180); 
    hand_r_pos = max(hand_r_pos,0); 
    hand_l_servo.write(180-hand_l_pos);        
    hand_r_servo.write(hand_r_pos);    
    delay(hand_delay);    
  }
  else{ 
    // no action
  }
}



void servo_test(){
  Serial.print("Left Pos:");
  Serial.print(hand_l_pos);
  Serial.print(" ; Right Pos:");
  Serial.println(hand_r_pos);
  delay(1000);
}

void b_skill(int keyword){
  int pos;
  //rush
  if(keyword=='f'){
    //both hand down 
    for(pos = 90; pos>=1; pos-=1)    
    {   
      hand_l_servo.write(180-pos);        
      hand_r_servo.write(pos);    
      delay(hand_delay);                      
    }
    //go forward
    motorL.setSpeed(motor_speed);
    motorR.setSpeed(motor_speed);
    motorL.run(FORWARD);
    motorR.run(FORWARD);
    //both hand up  
    for(pos = 0; pos < 180; pos += 1) 
    {    
      hand_l_servo.write(180-pos);          
      hand_r_servo.write(pos);                                      
      delay(hand_delay);                       
    }
    delay(500); 
    b_motor_stop();
    delay(100); 
  }
}

void blink(){   //中断函数blink()
  vibration++;    //一旦中断触发，state就不断自加
}
