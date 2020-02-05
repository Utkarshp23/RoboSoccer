#include <PS2X_lib.h>  //for v1.6

/******************************************************************
   set pins connected to PS2 controller:
     - 1e column: original
     - 2e colmun: Stef?
   replace pin numbers by the ones you use
 ******************************************************************/
#define PS2_DAT        13  //14    
#define PS2_CMD        11  //15
#define PS2_SEL        10  //16
#define PS2_CLK        12  //17

/******************************************************************
   select modes of PS2 controller:
     - pressures = analog reading of push-butttons
     - rumble    = motor rumbling
   uncomment 1 of the lines for each mode selection
 ******************************************************************/
#define pressures   true
//#define pressures   false
//#define rumble      true
#define rumble      false

PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning
//you must always either restart your Arduino after you connect the controller,
//or call config_gamepad(pins) again after connecting the controller.

int error = 0;
byte type = 0;
byte vibrate = 0;
float Rxa, Rya;
int8_t dir1 = 4;
int8_t dir2 = 2;
int8_t pwm1 = 5;
int8_t pwm2 = 3;

void setup() {

  Serial.begin(115200);
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);

  delay(300);  //added delay to give wireless ps2 module some time to startup, before configuring it

  //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************

  //setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  error = ps2x.config_gamepad(12, 11, 10, 9, pressures, rumble);

  if (error == 0)
  {
    //    Serial.print("Found Controller, configured successful ");
    Serial.print("pressures = ");
    if (pressures)
      Serial.println("true ");
    else
      Serial.println("false");
    Serial.print("rumble = ");
    if (rumble)
      Serial.println("true)");
    else
      Serial.println("false");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
  }
  else if (error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if (error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

  //  Serial.print(ps2x.Analog(1), HEX);

  type = ps2x.readType();
  switch (type) {
    case 0:
      Serial.print("Unknown Controller type found ");
      break;
    case 1:
      Serial.print("DualShock Controller found ");
      break;
    case 2:
      Serial.print("GuitarHero Controller found ");
      break;
    case 3:
      Serial.print("Wireless Sony DualShock Controller found ");
      break;
  }
}
int lxa , lya, rxa, rya;
void loop() {

  ps2x.read_gamepad(false, vibrate);
  vibrate = ps2x.Analog(PSAB_CROSS);

  /*  if (ps2x.Button(PSB_TRIANGLE))
      Serial.println("Triangle pressed");
    if (ps2x.ButtonPressed(PSB_CIRCLE))              //will be TRUE if button was JUST pressed
      Serial.println("Circle just pressed");
    if (ps2x.NewButtonState(PSB_CROSS))              //will be TRUE if button was JUST pressed OR released
      Serial.println("X just changed");
    if (ps2x.ButtonReleased(PSB_SQUARE))             //will be TRUE if button was JUST released
      Serial.println("Square just released");
  */

//   Serial.print(ps2x.Analog(PSS_LX));
//   Serial.print("  ");
//   Serial.print(ps2x.Analog(PSS_LY));
//   Serial.print("  ");
//   Serial.print(ps2x.Analog(PSS_RX));
//   Serial.print("  ");
//   Serial.println(ps2x.Analog(PSS_RY));
//   
  lxa = map(ps2x.Analog(PSS_LX), 0 , 255 ,  -120 , 120);
  lya = map(ps2x.Analog(PSS_LY), 0 , 255 ,  127 , -127);
  rxa = map(ps2x.Analog(PSS_RX), 0 , 255 ,  -120 ,  120);
  rya = map(ps2x.Analog(PSS_RY), 0 , 255 ,  100 , -100);

  if(lya>-20&&lya<20)
     lya=0;
  if(rya>-20&&rya<20)
     rya=0;
     

  //
  //  Rxa = 0.5 * rxa + 0.5 * lxa;
  //  Rya = 0.5 * rya + 0.5 * lya;
  //

  //  digitalWrite(dir1 , 0);
  //  analogWrite(pwm1 , 100);
  if (lya < 0)
  {
    digitalWrite(dir2 , 0);
    analogWrite(pwm2 , lya);
  }
  else
  {
    digitalWrite(dir2 , 1);
    analogWrite(pwm2 , -lya);
  }

  if (rya < 0)
  {
    digitalWrite(dir1 , 1);
    analogWrite(pwm1 , rya);
  } else
  {

    digitalWrite(dir1 , 0);
    analogWrite(pwm1 , -rya);
  }

    Serial.print("Stick Values:");
  Serial.print(rxa);
  Serial.print("   ");
  Serial.print(rya);
  Serial.print("   ");
  Serial.print(lxa);
  Serial.print("   ");
  Serial.print(lya);
  Serial.println("   ");
}//  Serial.println(atan2(rxa,ry
