#define VRX_PIN  A0 // Arduino pin connected to VRX pin
#define VRY_PIN  A1 // Arduino pin connected to VRY pin
#define SW_PIN   13  // Arduino pin connected to SW  pin

#define LEFT_THRESHOLD  400
#define RIGHT_THRESHOLD 800
#define UP_THRESHOLD    400
#define DOWN_THRESHOLD  800

#define COMMAND_NO     0x00
#define COMMAND_LEFT   0x01
#define COMMAND_RIGHT  0x02
#define COMMAND_UP     0x04
#define COMMAND_DOWN   0x08

#include <Servo.h>
#define BASE_PIN 2
#define JOINT_1_PIN 3
#define JOINT_2_PIN 4

int t = millis();

int pos_base = 0;
int pos_j1 = 0;
int pos_j2 = 0;
Servo base, joint_1, joint_2;  

bool pressed = false;
int xValue = 0 ; // To store value of the X axis
int yValue = 0 ; // To store value of the Y axis
int bValue = 1; // To store value of the button
int command = COMMAND_NO;
unsigned long buttonPressTime = 0;  // Time when button was pressed
unsigned long buttonHoldDuration = 0;
  int bCount = 0;


void zeroingFunction();
void readJoystick();
