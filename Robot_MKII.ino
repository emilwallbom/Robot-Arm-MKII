#include "Robot_MKII_main.h"

void setup() {
  Serial.begin(9600);

  base.attach(BASE_PIN); 
  joint_1.attach(JOINT_1_PIN);
  joint_2.attach(JOINT_2_PIN);

  pos_base = base.read();
  pos_j1   = joint_1.read();
  pos_j2   = joint_2.read();

  pinMode(SW_PIN, INPUT);
  digitalWrite(13, LOW);
  Serial.println("Program started");
}

void loop() {
  if (Serial.available() > 0 && Serial.read() == 'z') 
     zeroingFunction();

  readJoystick();

  if (pressed){
    controlJoint_2();
  } else {
    controlJoint_1();
  }

  controlBase();

  delay(15);
}

void controlJoint_1(){
  if (command & COMMAND_UP) {
    Serial.println("COMMAND UP 1");
    pos_j1+=2;
    joint_1.write(pos_j1);
  }

  if (command & COMMAND_DOWN) {
    Serial.println("COMMAND DOWN 1");
    pos_j1-=2;
    joint_1.write(pos_j1);
  }
}

void controlJoint_2(){
  if (command & COMMAND_UP) {
    Serial.println("COMMAND UP 2");
    pos_j2++;
    joint_2.write(pos_j2);
  }

  if (command & COMMAND_DOWN) {
    Serial.println("COMMAND DOWN 2");
    pos_j2--;
    joint_2.write(pos_j2);
  }
}

void controlBase(){
  if (command & COMMAND_LEFT) {
    Serial.println("COMMAND LEFT");
    pos_base++;
    base.write(pos_base);
  }

  if (command & COMMAND_RIGHT) {
    Serial.println("COMMAND RIGHT");
    pos_base--;
    base.write(pos_base);
  }
}

void readJoystick(){
  bValue = digitalRead(SW_PIN);
  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);
  // converts the analog value to commands
  // reset commands
  command = COMMAND_NO;

  // check left/right commands
  if (xValue < LEFT_THRESHOLD)
    command = command | COMMAND_LEFT;
  else if (xValue > RIGHT_THRESHOLD)
    command = command | COMMAND_RIGHT;

  // check up/down commands
  if (yValue < UP_THRESHOLD)
    command = command | COMMAND_UP;
  else if (yValue > DOWN_THRESHOLD)
    command = command | COMMAND_DOWN;
  // Check button state with threshold
  if(bValue == 0){
    bCount++;
    if(bCount>10) pressed = true;
    else          pressed = false;
  }else bCount = 0;
}

void zeroingFunction() {
  base.write(90);
  joint_1.write(90);
  joint_2.write(90);
  xValue = 0; 
  yValue = 0; 
  pos_base = 90;
  pos_j1 = 90;
  pos_j2 = 90;
  delay(1000);
  Serial.println("Zeroing completed.");
}
