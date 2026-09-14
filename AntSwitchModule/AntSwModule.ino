/*
  Serial Event example

  When new serial data arrives, this sketch adds it to a String.
  When a newline is received, the loop prints the string and clears it.

  A good test for this is to try it with a GPS receiver that sends out
  NMEA 0183 sentences.

  NOTE: The serialEvent() feature is not available on the Leonardo, Micro, or
  other ATmega32U4 based boards.

  created 9 May 2011
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/SerialEvent
*/

char incoming_command_string[50];

String inputString = "";      // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
bool command = false;
void setup() {
  // initialize serial:
  Serial.begin(9600);
  pinMode(0, INPUT_PULLUP);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
   for (int thisPin = 3; thisPin < 11; thisPin++) {
     pinMode(thisPin, OUTPUT);
     digitalWrite(thisPin, HIGH);
     delay(50);
     digitalWrite(thisPin, LOW);
     delay(50);
  }
digitalWrite(2, HIGH);
delay(50);
Serial.println("$SWREADY");
digitalWrite(2, LOW);
}

void serialEvent();

void commandOK() {
  digitalWrite(2, HIGH);
  delay(50);
  Serial.println("$SWOK");
  digitalWrite(2, LOW);
}




void loop() {
serialEvent();
}


void switchAllOff() {
     for (int thisPin = 3; thisPin < 11; thisPin++) {
     digitalWrite(thisPin, LOW);

  }
  commandOK();
}

void switchAllOn() {
     for (int thisPin = 3; thisPin < 11; thisPin++) {
     digitalWrite(thisPin, HIGH);
  }
  commandOK();
}

void switchOff(int8_t Relay) {
      digitalWrite(Relay+2, LOW);
  commandOK();
}

void switchOn(int8_t Relay) {
      digitalWrite(Relay+2, HIGH);
  commandOK();
}




void parse_incoming(void)
{
  uint8_t x;
  char *pEnd;
  int8_t  AntRelay;

  if (!strcasecmp("SWOFFALL",incoming_command_string))	           // Retrieve calibration values
  {
    switchAllOff();
  }

  else   if (!strcasecmp("SWONALL",incoming_command_string))	           // Retrieve calibration values
  {
    switchAllOn();
  }

  else if (!strncasecmp("SWOFFANT",incoming_command_string,8))     // Write new calibration values
  {
    AntRelay = strtol(incoming_command_string+8,&pEnd,10);
    switchOff(AntRelay);
  }

  else if (!strncasecmp("SWONANT",incoming_command_string,7))     // Write new calibration values
  {
    AntRelay = strtol(incoming_command_string+7,&pEnd,10);
    switchOn(AntRelay);
  }
}
/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {

  static uint8_t a;                     // Indicates number of chars received in an incoming command
  static bool Incoming;
  uint8_t ReceivedChar;
  uint8_t waiting;                      // Number of chars waiting in receive buffer

  waiting = Serial.available();         // Find out how many characters are waiting to be read.

   if (waiting && !Incoming)
    {
      ReceivedChar = Serial.read();
      // A valid incoming message starts with an "attention" symbol = '$'.
      // in other words, any random garbage received on USB port is ignored.
      if (ReceivedChar == '$')          // Start command symbol was received,
      {                                 // we can begin processing input command
        Incoming = true;
        a = 0;
        waiting--;
      }
      //else ***********************ADD UART Receive here
    }
    // Input command is on its way.  One or more characters are waiting to be read
    // and Incoming flag has been set. Read any available bytes from the USB OUT endpoint
    while (waiting && Incoming)
    {
      ReceivedChar = Serial.read();
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
