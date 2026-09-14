#include <PID_v1.h>
#include <EEPROM.h>
#include <Encoder.h>

// VL Ctrl Module Commands
#define VL_EXPP     "$VLEXPP"	  // wire expand + pulse #
#define VL_RETP	    "$VLRETP"	  // wire retract + pulse #
#define VL_MOVEP    "$VLMOVEP"	// move position
#define VL_STOP     "$VLST"		  // full stop
#define VL_PULSE_FB	"$VLPFB"		// set pulse number feedback + pulse #
#define VL_PULSE    "$VLP"		  // module command response every x pulse
#define VL_OK		    "$VLOK"		  // module command response

// macros VL man stepr antenna related
#define VL_PULSE_INCH	107		// encoder pulses per inch of wire
#define LAMDA4(f) ((5616/f)/2)	// freq mhz to 1/4 wave inchs
#define NPULSE(f) (((5616/f)/2)*VL_PULSE_INCH) 	// freq mhz to 1/4 wave encoder pulses

char incoming_command_string[50];

String inputString = "";      // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
bool command = false;

#define PWM1  5 //Motor Enamble pin Runs on PWM signal
#define InA1  8  // Motor Forward pin
#define InB1  9 // Motor Reverse pin
#define PWM2  6 // Motor2 Enamble pin Runs on PWM signal
#define InA2  10 // Motor2 Forward pin
#define InB2  11 // Motor2 Reverse pin
#define LOOPTIME        10                    // PID loop time
#define FORWARD         1                       // direction of rotation
#define BACKWARD        2                       // direction of rotation
#define GapV      200
int encoder1Pin1 = 2; //motor1 Encoder Output 'A' must connected with intreput pin of arduino nano int0.
int encoder1Pin2 = 4; //motor1 Encoder Output 'B' must connected with intreput pin of arduino nano noint.
int encoder2Pin1 = 3; //motor2 Encoder Output 'A' must connected with intreput pin of arduino nano int1.
int encoder2Pin2 = 7; //motor2 Encoder Output 'B' must connected with intreput pin of arduino nano noint.
volatile long lastPosition1 = 0; // Here updated value of encoder store.
volatile long lastPosition2 = 0; // Here updated value of encoder store.
long posInit1 = 0; // Raw encoder value
long tickNumber1 = 0; // Raw encoder value
long posInit2 = 0; // Raw encoder value
long tickNumber2 = 0; // Raw encoder value
boolean run1 = false; 
boolean run2 = false; 
int PWM_val1 = 255;
int PWM_val2 = 255;
int MotorN = 1;
int PPR = 264;  // 11 pulse * 24 ratio gear = encoder Pulse per revolution.
//double kp = 1 , ki = 0.01 , kd = 0.1;             // modify for optimal performance
double consKp = 1, consKi = 0.01, consKd = 0.1;    // Conservative for near final position
double aggKp = 4, aggKi = 0.2, aggKd = 1;          // Aggressive for start

double input1 = 0, output1 = 0, setpoint1 = 0;
double input2 = 0, output2 = 0, setpoint2 = 0;

Encoder myEnc1(2, 4);
Encoder myEnc2(3, 7);

PID myPID1(&input1, &output1, &setpoint1, consKp, consKi, consKd, P_ON_E, DIRECT);  
PID myPID2(&input2, &output2, &setpoint2, consKp, consKi, consKd, P_ON_E, DIRECT);  

// Function prototypes
void loadEEPROM();
void saveEEPROM();
void commandOK();
void vlgetp();
void vlpos();
void vlstop();
void vlexpp(long pulse);
void vlretp(long pulse);
void vlmovep(long position);
void parse_incoming();
void serialEvent();
void moveMotor1(int direction, int PWM_val1, long position);
void moveMotor2(int direction, int PWM_val2, long position);
void updateEncoder1();
void updateEncoder2();
void motorForward1(int PWM_val1);
void motorForward2(int PWM_val2);
void motorBackward1(int PWM_val1);
void motorBackward2(int PWM_val2);
void motorBrake1();
void motorBrake2();

void setup() {
  // initialize serial:
  Serial.begin(9600);
//  Serial1.begin(9600);

  pinMode(PWM1, OUTPUT);
  pinMode(InA1, OUTPUT); 
  pinMode(InB1, OUTPUT); 
  pinMode(PWM2, OUTPUT);
  pinMode(InA2, OUTPUT); 
  pinMode(InB2, OUTPUT); 

  pinMode(encoder1Pin1, INPUT_PULLUP); 
  pinMode(encoder1Pin2, INPUT_PULLUP);
  pinMode(encoder2Pin1, INPUT_PULLUP); 
  pinMode(encoder2Pin2, INPUT_PULLUP);

  digitalWrite(encoder1Pin1, HIGH); //turn pullup resistor on
  digitalWrite(encoder1Pin2, HIGH); //turn pullup resistor on
  digitalWrite(encoder2Pin1, HIGH); //turn pullup resistor on
  digitalWrite(encoder2Pin2, HIGH); //turn pullup resistor on

 // TCCR1B = TCCR1B & 0b11111000 | 1;  // set 31KHz PWM to prevent motor noise
  myPID1.SetMode(AUTOMATIC);   //set PID in Auto mode
  myPID1.SetSampleTime(LOOPTIME);  // refresh rate of PID controller
  myPID1.SetOutputLimits(-255, 255); // this is the MAX PWM value to move motor, here change in value reflect change in speed of motor.
  myPID2.SetMode(AUTOMATIC);   //set PID in Auto mode
  myPID2.SetSampleTime(LOOPTIME);  // refresh rate of PID controller
  myPID2.SetOutputLimits(-255, 255); // this is the MAX PWM value to move motor, here change in value reflect change in speed of motor.

  EEPROM.get(0, PPR);
  if (PPR != 264){
  Serial.println("Init EEProm");
    PPR=264;
    EEPROM.put(0, PPR);
    saveEEPROM();
  }
  loadEEPROM();
  Serial.println("$VLREADY");
//  Serial1.println("$VLREADY");
}

void loadEEPROM()
{
//  Serial.println("debut lecture eeprom");
  EEPROM.get(3, MotorN);
  EEPROM.get(6, lastPosition1);
  EEPROM.get(9, lastPosition2);
//  Serial.println("Fin lecture eeprom");
}

void saveEEPROM()
{
//  Serial.println("debut ecriture eeprom");

  EEPROM.put(3, MotorN);
  EEPROM.put(6, lastPosition1);
  EEPROM.put(9, lastPosition2);
//  Serial.println("Fin ecriture eeprom");
}

void commandOK() {
  Serial.println("$VLOK");
//  Serial1.println("$VLOK");
}

void loop() {
//serial1Event();
serialEvent();
updateEncoder1();
if (MotorN == 2)
  updateEncoder2();
}

void vlgetp() {
  Serial.print("$VLPOS1:");
  Serial.println(lastPosition1);
//  Serial1.print("$VLPOS1:");
//  Serial1.println(lastPosition1);
if (MotorN == 2) {
  Serial.print("$VLPOS2:");
  Serial.println(lastPosition2);
//  Serial1.print("$VLPOS2:");
//  Serial1.println(lastPosition2);
  }
}

void vlpos() {
  Serial.print("$VLPOS1:");
  Serial.println(lastPosition1);
//  Serial1.print("$VLPOS1:");
//  Serial1.println(lastPosition1);
if (MotorN == 2) {
  Serial.print("$VLPOS2:");
  Serial.println(lastPosition2);
//  Serial1.print("$VLPOS2:");
//  Serial1.println(lastPosition2);
  }
}  

void vlstop() {
  motorBrake1(); 
if (MotorN == 2) 
  motorBrake2(); 
  commandOK();
}  

void vlexpp(long pulse) {
  long position1;
  long position2;
  position1 = lastPosition1 + pulse;
  moveMotor1 (FORWARD, PWM_val1, position1 );
if (MotorN == 2) {
  position2 = lastPosition2 + pulse;
  moveMotor2 (FORWARD, PWM_val2, position2 );
  }
  commandOK();
}  

void vlretp(long pulse) {
  long position1;
  long position2;
  position1 = lastPosition1 - pulse;
  moveMotor1 (BACKWARD, PWM_val1, position1 );
if (MotorN == 2) {
  position2 = lastPosition2 - pulse;
  moveMotor2 (BACKWARD, PWM_val2, position2 );
  }
  commandOK();
}  

void vlmovep(long position) {
  if ( position > lastPosition1 ) {
    moveMotor1 (FORWARD, PWM_val1, position );
    if (MotorN == 2) 
      moveMotor2 (FORWARD, PWM_val2, position );
    } else {
    moveMotor1 (BACKWARD, PWM_val1, position );
    if (MotorN == 2) 
      moveMotor2 (BACKWARD, PWM_val2, position );
    }
  commandOK();
}  

void parse_incoming(void)
{
  uint8_t x;
  char *pEnd;
  String cpos = "";
  String incoming_command = incoming_command_string;
//  int8_t  pos;
  long pos;
  unsigned int len;
  
  if (!strcasecmp("VLGETP",incoming_command_string))	           // Retrieve lastPosition
  {
    vlgetp();
  }
  
  else  if (!strcasecmp("VLST",incoming_command_string))	           // All Stop
  {
    vlstop();
  }
  
  else   if (!strncasecmp("VLSETP",incoming_command_string,6))	           // Reset position
  {
    len = incoming_command.length();
    cpos = incoming_command.substring(6);
    pos = cpos.toInt();
    lastPosition1=pos;
    lastPosition2=pos;
    vlpos();
    commandOK();
  }

  else   if (!strncasecmp("VLMOVEP",incoming_command_string,7))	           // Move to position
  {
    len = incoming_command.length();
    cpos = incoming_command.substring(7);
    pos = cpos.toInt();
    vlmovep(pos);
  }

  else if (!strncasecmp("VLEXPP",incoming_command_string,6))     // move forward to n pulse
  {
    len = incoming_command.length();
    cpos = incoming_command.substring(6);
    pos = cpos.toInt();
    vlexpp(pos);
  }

  else if (!strncasecmp("VLRETP",incoming_command_string,6))     // move backward to n pulse
  {
    len = incoming_command.length();
    cpos = incoming_command.substring(6);
    pos = cpos.toInt();
    vlretp(pos);
  }

  else if (!strncasecmp("VLSETM",incoming_command_string,6))     // move backward to n pulse
  {
    len = incoming_command.length();
    cpos = incoming_command.substring(6);
    pos = cpos.toInt();
    MotorN = pos;
    commandOK();
  }
}

void serialEvent() {

  static uint8_t a;                     // Indicates number of chars received in an incoming command
  static bool Incoming;
  uint8_t ReceivedChar;
  uint8_t waiting;                      // Number of chars waiting in receive buffer

  waiting = Serial.available();         // Find out how many characters are waiting to be read.
//  waiting = Serial1.available();         // Find out how many characters are waiting to be read.

  if (waiting && !Incoming)
    {
      ReceivedChar = Serial.read();
//      ReceivedChar = Serial1.read();
      if (ReceivedChar == '$')          // Start command symbol was received,
      {                                 // we can begin processing input command
        Incoming = true;
        a = 0;
        waiting--;
      }
    }	
  while (waiting && Incoming)
    {
      ReceivedChar = Serial.read();
//      ReceivedChar = Serial1.read();
      waiting--;
      if (a == sizeof(incoming_command_string)-1)  // Line is too long, discard input
      {
        Incoming = false;
        a = 0;
      }
      // Check for End of line
      else if ((ReceivedChar=='\r') || (ReceivedChar=='\n') || (ReceivedChar==';'))
      {
        incoming_command_string[a] = 0; // Terminate line
        parse_incoming();           // Parse the command
        Incoming = false;
        a = 0;
      }
      else                              // Receive message, char by char
      {
        incoming_command_string[a] = ReceivedChar;
      }
      a++;                                         // String length count++
    }
}

/*
void serial1Event() {

  static uint8_t a;                     // Indicates number of chars received in an incoming command
  static bool Incoming;
  uint8_t ReceivedChar;
  uint8_t waiting;                      // Number of chars waiting in receive buffer

  waiting = Serial1.available();         // Find out how many characters are waiting to be read.

  if (waiting && !Incoming)
    {
      ReceivedChar = Serial1.read();
      if (ReceivedChar == '$')          // Start command symbol was received,
      {                                 // we can begin processing input command
        Incoming = true;
        a = 0;
        waiting--;
      }
    }	
  while (waiting && Incoming)
    {
      ReceivedChar = Serial1.read();
      waiting--;
      if (a == sizeof(incoming_command_string)-1)  // Line is too long, discard input
      {
        Incoming = false;
        a = 0;
      }
      // Check for End of line
      else if ((ReceivedChar=='\r') || (ReceivedChar=='\n') || (ReceivedChar==';'))
      {
        incoming_command_string[a] = 0; // Terminate line
        parse_incoming();           // Parse the command
        Incoming = false;
        a = 0;
      }
      else                              // Receive message, char by char
      {
        incoming_command_string[a] = ReceivedChar;
      }
      a++;                                         // String length count++
    }
}
*/
void moveMotor1(int direction, int PWM_val1, long position)  {
  posInit1 = lastPosition1;    // abs(count)
  tickNumber1 = position;
  input1 = lastPosition1;
  setpoint1 = tickNumber1;
  myPID1.Compute();
  PWM_val1 = output1;
  if (PWM_val1 >=0) motorForward1(PWM_val1);
  else motorBackward1(abs(PWM_val1));
}

void moveMotor2(int direction, int PWM_val2, long position)  {
  posInit2 = lastPosition2;    // abs(count)
  tickNumber2 = position;
  input2 = lastPosition2;
  setpoint2 = tickNumber2;
  myPID2.Compute();
  PWM_val2 = output2;
  if (PWM_val2 >=0) motorForward2(PWM_val2);
  else motorBackward2(abs(PWM_val2));
}

void updateEncoder1(){
  long newPosition1 = myEnc1.read();
  double gap1;

  if (run1) {
    if (newPosition1 != lastPosition1) {
      lastPosition1 = newPosition1;
    }
    if ((abs(lastPosition1)) == tickNumber1) {
      motorBrake1();
    } else {
    input1 = lastPosition1;
    setpoint1 = tickNumber1;

 gap1 = abs(setpoint1-input1); //distance away from setpoint

  if (gap1 < GapV)
  {  //we're close to setpoint, use conservative tuning parameters
    myPID1.SetTunings(consKp, consKi, consKd);
  }
  else
  {
     //we're far from setpoint, use aggressive tuning parameters
     myPID1.SetTunings(aggKp, aggKi, aggKd);
  }
    myPID1.Compute();
    PWM_val1 = output1;
    if (PWM_val1 >=0) motorForward1(PWM_val1);
    else motorBackward1(abs(PWM_val1));
    }
  }
}
void updateEncoder2(){
  long newPosition2 = myEnc2.read();
  double gap2;

  if (run2) {
    if (newPosition2 != lastPosition2) {
      lastPosition2 = newPosition2;
    }
    if ((abs(lastPosition2)) == tickNumber2) {
      motorBrake2();
    } else {
    input2 = lastPosition2;
    setpoint2 = tickNumber2;

    gap2 = abs(setpoint2-input2); //distance away from setpoint

  if (gap2 < GapV)
  {  //we're close to setpoint, use conservative tuning parameters
    myPID2.SetTunings(consKp, consKi, consKd);
  }
  else
  {
     //we're far from setpoint, use aggressive tuning parameters
     myPID2.SetTunings(aggKp, aggKi, aggKd);
  }
    myPID2.Compute();
    PWM_val2 = output2;
    if (PWM_val2 >=0) motorForward2(PWM_val2);
    else motorBackward2(abs(PWM_val2));
    }
  }
}

void motorForward1(int PWM_val1)  {
  analogWrite(PWM1, PWM_val1);
  digitalWrite(InA1, LOW);
  digitalWrite(InB1, HIGH);
  run1 = true;
}
void motorForward2(int PWM_val2)  {
  analogWrite(PWM2, PWM_val2);
  digitalWrite(InA2, LOW);
  digitalWrite(InB2, HIGH);
  run2 = true;
}

void motorBackward1(int PWM_val1)  {
  analogWrite(PWM1, PWM_val1);
  digitalWrite(InA1, HIGH);
  digitalWrite(InB1, LOW);
  run1 = true;
}
void motorBackward2(int PWM_val2)  {
  analogWrite(PWM2, PWM_val2);
  digitalWrite(InA2, HIGH);
  digitalWrite(InB2, LOW);
  run2 = true;
}

void motorBrake1()  {
  analogWrite(PWM1, 0);
  digitalWrite(InA1, HIGH);
  digitalWrite(InB1, HIGH);
  saveEEPROM();
  run1 = false;
  Serial.print("$VLPOS1:");
  Serial.println(lastPosition1);
//  Serial1.print("$VLPOS1:");
//  Serial1.println(lastPosition1);
}
void motorBrake2()  {
  analogWrite(PWM2, 0);
  digitalWrite(InA2, HIGH);
  digitalWrite(InB2, HIGH);
  saveEEPROM();
  run2 = false;
  Serial.print("$VLPOS2:");
  Serial.println(lastPosition2);
//  Serial1.print("$VLPOS2:");
//  Serial1.println(lastPosition2);
}
