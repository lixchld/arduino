#include <AFMotor.h>


#define SENSOR_L 4
#define SENSOR_LM 3
#define SENSOR_M 2
#define SENSOR_RM 1
#define SENSOR_R 0

AF_DCMotor motor_l(1);
AF_DCMotor motor_r(2);

int sensor[5];
int adj[5];
int s_min[5];
int s_max[5];

int speed_value = 150;

//Following threshold needs to be adjust according to ambinent light intensity
int lower_threshold = 80;
int threshold = 128;
int upper_threshold = 200;

void setup() {
  Serial.begin(9600);

  motor_l.setSpeed(255);
  motor_l.run(RELEASE);
  motor_r.setSpeed(255);
  motor_r.run(RELEASE);

  for( int i=0; i<5; i++){
    // init min & max to make sure they could be updated
    s_min[i] = 255;
    s_max[i] = 0;  
  }
}

void updateSensors(){
  for(int idx = 0; idx<5; idx++){
    sensor[idx] = analogRead(idx);
    
    //update the min & max value
    if( sensor[idx] > s_max[idx]) {
      s_max[idx] = sensor[idx];
    }

    if(sensor[idx] < s_min[idx]){
      s_min[idx] = sensor[idx];
    }
    
    adj[idx] = map( sensor[idx], s_min[idx], s_max[idx], 0, 255);
    adj[idx] = constrain( adj[idx], 0, 255);
    
    delay(3);
  }
}


void loop() {
  
  updateSensors();

  if( adj[SENSOR_M] < lower_threshold ){
    if( adj[SENSOR_LM] > threshold && adj[SENSOR_RM] > threshold ){
      Serial.println( "Move forward");
      
      motor_l.run( FORWARD );
      motor_l.setSpeed( speed_value );

      motor_r.run( FORWARD );
      motor_r.setSpeed( speed_value );
    } else if( adj[SENSOR_L] < lower_threshold) {
      if(adj[SENSOR_LM] < lower_threshold) {
        if(adj[SENSOR_M ] < lower_threshold) { 
          if(adj[SENSOR_RM] <  lower_threshold){
            if(adj[SENSOR_R] < lower_threshold ) {
              Serial.println("Stop at the black block");
              
              motor_l.run(RELEASE);
              motor_r.run(RELEASE);
            }
          }
        }
      }
    } else {
      Serial.println("Do Nothing");
    }
  } else {
    if( adj[SENSOR_L] < upper_threshold && adj[SENSOR_R] > upper_threshold ){
      Serial.println("Turn left sharp");
      motor_l.run(RELEASE);
      motor_l.setSpeed(0);

      motor_r.run(FORWARD);
      motor_r.setSpeed( speed_value+25);
      
    } else if( adj[SENSOR_L] > upper_threshold && adj[SENSOR_R] < upper_threshold ){
      Serial.println("Turn right sharp");
      
      motor_l.run(FORWARD);
      motor_l.setSpeed(speed_value + 25);

      motor_r.run(RELEASE);
      motor_r.setSpeed( 0);
    } else if( adj[SENSOR_LM] < upper_threshold && adj[SENSOR_RM] > upper_threshold ){
      Serial.println("Turn left");
      
      motor_l.run(RELEASE);
      motor_l.setSpeed(0);

      motor_r.run(FORWARD);
      motor_r.setSpeed( speed_value-25);        
    } else if( adj[SENSOR_LM] > upper_threshold && adj[SENSOR_RM] < upper_threshold ){
      Serial.println("Turn right");
      
      motor_l.run(FORWARD);
      motor_l.setSpeed(speed_value-25);

      motor_r.run(RELEASE);
      motor_r.setSpeed( 0);
    }
    else
    {
      Serial.println("Do nothing 11");
    }
  } 
  
  
  for( int idx = 0; idx<5; idx++){
    Serial.print( "Sensor");
    Serial.print( idx );
    Serial.print( ": ");
    Serial.print( sensor[idx] );
    Serial.print( " - " );
    Serial.print("Adj");
    Serial.print(idx);
    Serial.print( ": " );
    Serial.print( adj[idx] );
    Serial.print( " - " );
  }
  Serial.println();

}
