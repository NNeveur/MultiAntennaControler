// macros VL antenna related
//#define VL_PULSE_INCH	109		// encoder pulses per inch of wire
//#define LAMDA4(f) ((5616/f)/2)	// freq mhz to 1/4 wave inchs
//#define NPULSE(f) (((5616/f)/2)*VL_PULSE_INCH) 	// freq mhz to 1/4 wave encoder pulses
//

void vlFreqPos(float Freq){
  double Npos;
  Npos = NPULSE(Freq);
}

void vlFreqInch(float Freq){
  double Npos;
  Npos = LAMDA4(Freq);
}
