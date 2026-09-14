
#include "Arduino.h"
#include <EEPROM.h>
#include "math.h"
#include "EasyNextionLibrary.h" // https://github.com/Seithan/EasyNextionLibrary
//#include <FreqCount.h>
#include "MainCtrl.h"

uint16_t RSbaud = 19200;
uint16_t CATbaud = 9600;
uint8_t ModeCtrl = 0;
char print_buf[64];
int32_t trx_pwr = 0;
int32_t trx_mode = 0;

EasyNex myNex(UART_DISP);

antenna ant1;
antenna ant2;
antenna ant3;
antenna ant4;
antenna ant5;
antenna ant6;
antenna ant7;
antenna ant8;

mode OpMode;
radio RadioParam;
var_track_t var_track;
vl_param_t vl_param;

uint8_t last_display_ant = 0;
uint8_t last_ant_relay = 0;
uint8_t last_display_mant = 0;

uint8_t current_ant = 1;
uint8_t current_band = 1;
uint8_t last_ant = 0;

uint8_t ant_bank = 0;

uint8_t CheckInit = 0;

void setup() {
  // put your setup code here, to run once:
myNex.begin(Dispbaud); // start Nextion Display
myNex.writeStr("page 0");
delay(2000);
myNex.writeStr("page MenuSetup");

Serial.begin(9600);
UART_RS422.begin(RSbaud);

EEPROM.get(0, CheckInit);
if (CheckInit != 99){
  CheckInit=99;
  EEPROM.put(0, CheckInit);
  saveEEPROM();
} else loadEEPROM();

UART_CAT.begin(CATbaud);

set_ant(current_ant);
//Serial.println(sizeof(ant1));
//Serial.println(sizeof(ant2));
//Serial.println(sizeof(ant3));
//Serial.println(sizeof(ant4));
//Serial.println(sizeof(ant5));
//Serial.println(sizeof(ant6));
//Serial.println(sizeof(ant7));
//Serial.println(sizeof(ant8));

}

void loop() {
  // put your main code here, to run repeatedly:
 myNex.NextionListen();
}
