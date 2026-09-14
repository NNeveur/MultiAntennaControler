
void drv8825_PwrOn(void);
void drv8825_PwrOff(void);
void drv8825_Incr(uint8_t res);
void drv8825_Decr(uint8_t res);
void drv8825_Move(void);
void drv8825_Init(void);

const int drv8825_dir   = 3;     // Direction pin
const int drv8825_step  = 4;     // Step pin (positive pulse of +1us for each step)
const int drv8825_enable= 5;     // Enable pin
const int drv8825_ms1   = 6;     // Microstepping pin MS1
const int drv8825_ms2   = 7;     // Microstepping pin MS2
const int drv8825_ms3   = 8;     // Microstepping pin MS8

//---------------------------------------------------------------------------------
//		Bipolar Stepper Motor Control Routine, using Allegro A4988 
//		or TI DRV8825 Double Full-Bridge Motor Driver
//---------------------------------------------------------------------------------
//
   
//
// Increment Stepper
//
void drv8825_Incr(uint8_t res)
{
  res = 3 - res;                       // Reversed: 0 for no microsteps
                                       // 1 for half step (2 microsteps)
                                       // 2 for quarter step (4 microsteps)
                                       // 3 for eighth step (8 microsteps)

  drv8825_PwrOn();                     // Ensure Power On state
  digitalWrite(drv8825_dir, LOW);      // Clockwise
  digitalWrite(drv8825_ms1, (res&0x01)?HIGH:LOW);  // ... Microstep resolution
  digitalWrite(drv8825_ms2, (res&0x02)?HIGH:LOW);
  digitalWrite(drv8825_step, HIGH);    // Prime for Movement, turn Step pulse on
}
//
// Decrement Stepper
//
void drv8825_Decr(uint8_t res)
{
  res = 3 - res;                       // Reversed: 0 for no microsteps
                                       // 1 for half step (2 microsteps)
                                       // 2 for quarter step (4 microsteps)
                                       // 3 for eighth step (8 microsteps)

  drv8825_PwrOn();                     // Ensure Power On state
  digitalWrite(drv8825_dir, HIGH);     // Counterclockwise
  digitalWrite(drv8825_ms1, (res&0x01)?HIGH:LOW);  // ... Microstep resolution
  digitalWrite(drv8825_ms2, (res&0x02)?HIGH:LOW);
  digitalWrite(drv8825_step, HIGH);    // Prime for Movement, turn Step pulse on
}

//
// Move Stepper (neends >1+ microsecond delay from positive edge)
//
void drv8825_Move(void)
{
  digitalWrite(drv8825_step, LOW);     // Move, turn Step pulse off  
}

//
// Turn the Stepper On
//
void drv8825_PwrOn(void)
{
  //digitalWrite(drv8825_reset, HIGH); // Release Reset, turn Stepper Motor On
  digitalWrite(drv8825_enable, LOW);   // Enable Stepper
}

//
// Turn the Stepper Off
//
void drv8825_PwrOff(void)
{
  //digitalWrite(drv8825_reset, LOW);  // Reset and turn Stepper Motor Off
  digitalWrite(drv8825_enable, HIGH);  // Disable Stepper, retain last state
}

//
// Init Stepper Outputs
//
void drv8825_Init(void)
{
  pinMode(drv8825_dir, OUTPUT);        // Direction Pin    
  pinMode(drv8825_step, OUTPUT);       // Step Pin
  pinMode(drv8825_ms2, OUTPUT);        // MS2 pin
  pinMode(drv8825_ms1, OUTPUT);        // MS1 pin
  pinMode(drv8825_enable, OUTPUT);     // Enable Pin    
  drv8825_PwrOff();                    // Ensure Power Off state
}

String inputString = "";      // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
bool command = false;
void commandOK() {
  digitalWrite(2, HIGH);
  delay(50);
  Serial.println("$LPOK");
  digitalWrite(2, LOW);
}

void setup() {
  // initialize serial:
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  drv8825_Init(); 
digitalWrite(2, HIGH);
delay(50);
Serial.println("$LOOPREADY");
digitalWrite(2, LOW);
}

void loop() {
uint8_t res = 3;
  // print the string when a newline arrives:
  if (stringComplete) {
    inputString.trim();

    if (inputString == "$LPINC" || inputString == "$STINC") {
      drv8825_Incr(res);
      commandOK();
    }
    else if (inputString == "$LPDEC" || inputString == "$STDEC") {
      drv8825_Decr(res);
      commandOK();
    }
    else if (inputString == "$LPMOV" || inputString == "$STMOVE") {
      drv8825_Move();
      commandOK();
    }
    else if (inputString == "$LPON" || inputString == "$STON") {
      drv8825_PwrOn();
      commandOK();
    }
    else if (inputString == "$LPOFF" || inputString == "$STOFF") {
      drv8825_PwrOff();
      commandOK();
    }
    else if (inputString == "$LPINI") {
      drv8825_Init();
      commandOK();
    }
    // clear the string:
    inputString = "";
    command = false;
    stringComplete = false;
  }
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()>0) {
    // get the new byte:
    char inChar = (char)Serial.read();
    if (inChar == '$') {
      command = true;
    }
    if (command == true) {
    // add it to the inputString:
      inputString += inChar;
    }
    
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
