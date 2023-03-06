#include <ros.h>
#include <std_msgs/Int32.h>
#include <motor_control/motor_msg.h>

//Node
ros::NodeHandle motor;

//Motor pin
int enable = 3;
int entrada1 = 7;
int entrada2 = 8;

void callback(const motor_control::motor_msg& msg){
  int pwm = 0;
  //char direction_[20];
  pwm = msg.pwm;

  if ((String) msg.direction == "backward" ){
    digitalWrite(entrada1, HIGH);
    digitalWrite(entrada2, LOW);
    analogWrite(enable, pwm);
    
  } else if ((String) msg.direction == "forward"){
    digitalWrite(entrada1, LOW);
    digitalWrite(entrada2, HIGH);
    analogWrite(enable, pwm);
  }
  
  char log_msg_pwm[20];
  sprintf(log_msg_pwm, "Pwm: %d", pwm);
  
  motor.loginfo(log_msg_pwm);
  motor.loginfo(msg.direction);
}

//Topic
ros::Subscriber<motor_control::motor_msg> sub("cmd_pwm", &callback);

void setup()
{
  //ros
  motor.initNode();
  motor.subscribe(sub);

  //motor
  pinMode(enable, OUTPUT);
  pinMode(entrada1, OUTPUT);
  pinMode(entrada2, OUTPUT);
}

void loop()
{
  
  motor.spinOnce();
  delay(1);
}
