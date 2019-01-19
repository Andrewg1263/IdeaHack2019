// the setup function runs once when you press reset or power the board
  int motor_left = 5;
  int motor_right = 6;
  
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(motor_left, OUTPUT);
  pinMode (motor_right, OUTPUT);
}

void vibrate_left(){
  digitalWrite(motor_left,HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(motor_left, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);         
}

void vibrate_right(){
  digitalWrite(motor_right,HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(motor_right, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);         
}
void vibrate_stop (){
  digitalWrite(motor_left, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(motor_right, LOW);
}

// the loop function runs over and over again forever
void loop() {
//  vibrate_left () ; 
//  vibrate_right() ;                                                                                                                                                                  
//  vibrate_stop();
//  delay (3000);                  
}
