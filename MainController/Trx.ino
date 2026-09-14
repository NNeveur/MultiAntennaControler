

//
// Write a string to Transceiver.  If Debug, then write a string and newline to debug
void trx_print(const char *in_string)
{
  UART_CAT.print(in_string);
}
//
// Write a char to Transceiver
//void trx_write(uint8_t in)
void trx_write(char in)
{
  UART_CAT.write(in);
}
//
// Write a char to Transceiver.  If Debug, then write a char and newline to debug
void trx_writeln(char in)
{
  UART_CAT.write(in);
}


char transceiver_in_string[2048]; // Incoming serial string to parse
//
//---------------------------------------------------------------------------------
// Some transceivers use binary data protocols which do not have any obvious
// beginning and end of each message.  Collect incoming traffic to a circular buffer.
// The Transceiver poll functions have responsibility to zero the outstanding
// byte count in the circular buffer before each poll for new data.
// This also hopefully provides for better behaviour when in passthru mode
// when all sorts of traffic may be present.
//---------------------------------------------------------------------------------
//
//
uint16_t char_pointer_in  = 0;    // Circular buffer pointer, last read character
uint16_t char_pointer_out = 0;    // Circular buffer pointer, last processed character
void transceiver_sync_read(void)
{
  while(UART_CAT.available()>0)       // Are incoming characters waiting to be processed?
  {
    transceiver_in_string[char_pointer_in++] = UART_CAT.read(); // Read the character from UART buffer
    if (char_pointer_in == 2048) char_pointer_in = 0;       // Wrap around at end.
  }
}
// Return number of chars available from Transceiver
uint16_t trx_available(void)
{
  uint16_t avail;
  if (char_pointer_in >= char_pointer_out) avail = char_pointer_in - char_pointer_out;
  else avail = char_pointer_in + (2048 - char_pointer_out);
  return avail;
}
// Clear incoming buffer
void trx_clear(void)
{
  char_pointer_out = char_pointer_in;
}

// Read chars from incoming circular buffer
uint8_t trx_read(void)
{
  char i;
  i = transceiver_in_string[char_pointer_out++];
  if (char_pointer_out == 2048) char_pointer_out = 0;       // Wrap around at end.

  // CAT Passthrough mode. Pass everything from serial (radio) to USB (computer)
  if (RadioParam.passthrough)
  {
    Serial.write(i);
  }
  return i;
}
//
// Read chars from Transceiver.  If Debug, then write newline to debug
uint8_t trx_readln(void)
{
  char i;
  i = transceiver_in_string[char_pointer_out++];
  if (char_pointer_out == 2048) char_pointer_out = 0;       // Wrap around at end.

  // CAT Passthrough mode. Pass everything from serial (radio) to USB (computer)
  if (RadioParam.passthrough)
  {
    Serial.write(i);
  }
  return i;
}


//
//---------------------------------------------------------------------------------
// Kenwood TS-440, TS-480 / TS-2000 Parse input
//---------------------------------------------------------------------------------
//
// This function uses input from serial_async_read()
void ts2000_parse_serial_input(void)
{
  char *pEnd;
  char frqstring[12];
  int32_t  frq_in;

  // Grab frequency and Mode if header is correct and length is consistent with an IF response
  if ((!strncmp("IF",transceiver_in_string,2)) && (strlen(transceiver_in_string) > 30))
  {
    strncpy(frqstring, transceiver_in_string+2,11);
    frq_in = strtol(frqstring,&pEnd,10);

    set_ant(current_ant);                              // Antenna switchover
    var_track.Frq = frq_in;
  }
  else if (!strncmp("PC",transceiver_in_string,2))       // Read Power Control level
  {
    trx_pwr = strtol(transceiver_in_string+2,&pEnd,10);  // 0 - 255
  }
  else if (!strncmp("MD",transceiver_in_string,2))       // Read active Mode (LSB, USB etc)
  {
    trx_mode = strtol(transceiver_in_string+2,&pEnd,10); // 1=LSB 2=USB 3=CW 4=FM 5=AM 6=FSK 7=CWR 8=PKT-L 9=FSK-R...
  }
}
//
//---------------------------------------------------------------------------------
// Kenwood TS-440, TS-480 / TS-2000 style Request Frequency and Mode
//---------------------------------------------------------------------------------
//
void ts2000_request_frequency(void)
{
  trx_print("IF;");                               // Transmit a frequency poll request to transceiver
}
//
//---------------------------------------------------------------------------------
// Autotune stuff
//
//---------------------------------------------------------------------------------
// Kenwood TS-480 / TS-2000 style Request Power
//---------------------------------------------------------------------------------
//
void ts2000_request_pwr(void)
{
  trx_print("PC;");                              // Query status of Power Control
  delay(10);
}
//
//---------------------------------------------------------------------------------
// Kenwood TS-480 / TS-2000 style Request Mode
//---------------------------------------------------------------------------------
//
void ts2000_request_mode(void)
{
  trx_print("MD;");                              // Query which operating mode is in use
  delay(10);
}
//
//---------------------------------------------------------------------------------
// Kenwood TS-480 / TS-2000 style Set Power
//---------------------------------------------------------------------------------
//
void ts2000_set_pwr(uint8_t pwr)
{
  sprintf(print_buf,"PC%03u;", pwr);
  trx_print(print_buf);
  delay(100);
}
//
//---------------------------------------------------------------------------------
// Kenwood TS-440, TS-480 / TS-2000 style Set Mode
//---------------------------------------------------------------------------------
//
void ts2000_set_mode(uint8_t mode)
{
  sprintf(print_buf,"MD%01u;", mode);
  trx_print(print_buf);
  delay(100);
}
//
//---------------------------------------------------------------------------------
// Kenwood TS-440, TS-480 / TS-2000 style Set Transmit Mode
//---------------------------------------------------------------------------------
//
void ts2000_set_tx(void)
{
  trx_print("TX;");
  delay(100);
}
void ts2000_set_rx(void)
{
  trx_print("RX;");
  delay(250);
}
