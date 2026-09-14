#ifndef MAINCTRL_H
#define MAINCTRL_H

#include <Arduino.h>
#include <EasyNextionLibrary.h>

struct antenna
{
  unsigned active : 1;
  char etiquette[20];
  unsigned band1 : 1;
  unsigned band2 : 1;
  unsigned band3 : 1;
  unsigned band4 : 1;
  unsigned band5 : 1;
  unsigned band6 : 1;
  unsigned band7 : 1;
  unsigned band8 : 1;
  unsigned band9 : 1;
  unsigned band10 : 1;
  unsigned band11 : 1;
  unsigned LoopAnt : 1;
  unsigned VLAnt : 1;
  unsigned ATASAnt : 1;
};

extern antenna ant1;
extern antenna ant2;
extern antenna ant3;
extern antenna ant4;
extern antenna ant5;
extern antenna ant6;
extern antenna ant7;
extern antenna ant8;

struct mode
{
  uint8_t freqsource;
  uint8_t selector;
};
extern mode OpMode;

struct radio
{
  uint8_t model;
  uint16_t speed;
  uint8_t port;             // 0 = TTL polarity, 1 = Reverse polarity Serial (if RS232 without MAX232)
  uint8_t param;             // SERIAL_8N1
  boolean passthrough;      // Pass all data from USB (computer) to serial (radio) and vice versa
  uint16_t pollRate;
  uint8_t  ICOM_address;    // ICOM CI-V Address, only relevant for ICOM transceivers
  uint8_t  tx_pwrlevel;
};
extern radio RadioParam;

struct var_track_t {
  int32_t  Frq;                  // Frequency information in Hz
  int32_t  Pos;                  // Position Information, referenced at 1000000
};
extern var_track_t var_track;

struct vl_param_t {
  int8_t  units;                  // Frequency information in Hz
  int8_t  MotorN;                  // Frequency information in Hz
  int8_t  encoderN;                  // Frequency information in Hz
  int16_t pulseround;                  // Position Information, referenced at 1000000
  int16_t unitsround;                  // Position Information, referenced at 1000000
  int16_t motorspeed;                  // Position Information, referenced at 1000000
  int32_t maxlength;                  // Position Information, referenced at 1000000
};
extern vl_param_t vl_param;

extern uint8_t current_ant;
extern uint8_t current_band;
extern uint8_t ant_bank;

extern EasyNex myNex;

//
// Ant Ctrl Module Commands
#define SW_ALL_OFF  "$SWOFFALL"	// all relays switch off
#define SW_ALL_ON 	"$SWONALL"	// all relays switch on
#define SW_ANT_OFF	"$SWOFFANT"	  // relay switch off + relay #
#define SW_ANT_ON 	"$SWONANT"	  // relay switch on + relay #
#define SW_OK		    "$SWOK"		  // module command response
//
//
// Loop Ctrl Module Commands
#define LOOP_INCR  	"$LPINC"	// stepper increment + resolution step
#define LOOP_DECR 	"$LPDEC"	// stepper decrement + resolution step
#define LOOP_MOVE 	"$LPMOV"	// stepper move
#define LOOP_OFF	  "$LPOFF"	// stepper power off
#define LOOP_ON		  "$LPON"		// stepper power on
#define LOOP_INIT	  "$LPINI"	// stepper initialisation
#define LOOP_OK		  "$LPOK"		// module command response
//
//
// VL Ctrl Module Commands
#define VL_EXPP     "$VLEXPP"	  // wire expand + pulse #
#define VL_RETP	    "$VLRETP"	  // wire retract + pulse #
#define VL_MOVEP    "$VLMOVEP"	// wire move to + position (in pulse)
#define VL_STOP     "$VLST"		  // full stop
#define VL_SETP     "$VLSETP"		// set position in pulse
#define VL_SETM     "$VLSETM"		// set number of motor 1 or 2
#define VL_POS      "$VLPOS"		// module command response position in pulse
#define VL_OK		    "$VLOK"		  // module command response
#define VL_READY    "$VLREADY"	// module command response READY

//
// macros VL antenna related
#define VL_PULSE_INCH	109		// encoder pulses per inch of wire
#define LAMDA4(f) ((5616/f)/2)	// freq mhz to 1/4 wave inchs
#define NPULSE(f) (((5616/f)/2)*VL_PULSE_INCH) 	// freq mhz to 1/4 wave encoder pulses
//
// ATAS Ctrl Module Commands
# define ATAS_UP  	"$ATASUP"	// antenna move up
# define ATAS_DOWN 	"$ATASDW"	// antenna move down
# define ATAS_STOP 	"$ATASST"	// full stop
# define ATAS_OK	  "$ATASOK"	// module command response
//
//
//
// Bool stuff
#define WORKING    0
#define DONE       1
#define SUCCESS    1
#define FAIL       2
#define NOPWR      3

//-----------------------------------------------------------------------------
// Soft Reset Teensy 3 style
#define RESTART_ADDR       0xE000ED0C
#define RESTART_VAL        0x5FA0004
#define SOFT_RESET()       ((*(volatile uint32_t *)RESTART_ADDR) = (RESTART_VAL))

//-----------------------------------------------------------------------------
// Macros
#ifndef SQR
#define SQR(x) ((x)*(x))
#endif
#ifndef ABS
#define ABS(x) ((x>0)?(x):(-x))
#endif

#define UART_DISP Serial1
#define Dispbaud 115200
#define UART_RS422 Serial2
extern uint16_t RSbaud;
#define UART_CAT Serial3
extern uint16_t CATbaud;

#define LoopTag "Mag Loop Ctrl"
#define VLTag "VariLength Ctrl"
#define ATASTag "Yeasu ATAS Ctrl"
#define InacTag "Inactive"

#define Encoder0 2
#define Encoder1 3
#define EncoderSW 4

extern uint8_t ModeCtrl;   // 0=Main menu 1=Selector 2=LoopCtrl 3=VariCtrl 4=ATASCtrl
#define MainMenu 0
#define Selector 1
#define LoopCtrl 2
#define VariCtrl 3
#define ATASCtrl 4

extern char print_buf[64];
extern int32_t trx_pwr;
extern int32_t trx_mode;

void set_ant(int ant_relay);
void ant(int Nrelay);
void loadEEPROM();
void saveEEPROM();
void dispCtrlSelector();
void rs422_parse_incoming();
void rs422_read_and_parse();
void vlFreqPos(float Freq);
void vlFreqInch(float Freq);
void ts2000_parse_serial_input();
void ts2000_request_frequency();
void ts2000_request_pwr();
void ts2000_request_mode();
void ts2000_set_pwr(uint8_t pwr);
void ts2000_set_mode(uint8_t mode);
void ts2000_set_tx();
void ts2000_set_rx();

#endif
