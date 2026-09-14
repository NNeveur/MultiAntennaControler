// AS_Nextriger.ino
//
/* === Trigger from Nextion Display  === */
void trigger1() // x01
{
//  band_mode = 1;
  ant_bank = 1;
  myNex.writeNum("bt1.val", 1);
  myNex.writeNum("bt2.val", 0);
  myNex.writeNum("bt3.val", 0);
  myNex.writeNum("bt4.val", 0);
  myNex.writeNum("bt5.val", 0);
  myNex.writeNum("bt6.val", 0);
  myNex.writeNum("bt7.val", 0);
  myNex.writeNum("bt8.val", 0);
  ant(ant_bank);
}

void trigger2() // x02
{
  //band_mode = 1;
  ant_bank = 2;
  myNex.writeNum("bt1.val", 0);
  myNex.writeNum("bt2.val", 1);
  myNex.writeNum("bt3.val", 0);
  myNex.writeNum("bt4.val", 0);
  myNex.writeNum("bt5.val", 0);
  myNex.writeNum("bt6.val", 0);
  myNex.writeNum("bt7.val", 0);
  myNex.writeNum("bt8.val", 0);
  ant(ant_bank);
}

void trigger3() // x03
{
//  band_mode = 1;
  ant_bank = 3;
  myNex.writeNum("bt1.val", 0);
  myNex.writeNum("bt2.val", 0);
  myNex.writeNum("bt3.val", 1);
  myNex.writeNum("bt4.val", 0);
  myNex.writeNum("bt5.val", 0);
  myNex.writeNum("bt6.val", 0);
  myNex.writeNum("bt7.val", 0);
  myNex.writeNum("bt8.val", 0);
  ant(ant_bank);
}

void trigger4() // x04
{
//  band_mode = 1;
  ant_bank = 4;
  myNex.writeNum("bt1.val", 0);
  myNex.writeNum("bt2.val", 0);
  myNex.writeNum("bt3.val", 0);
  myNex.writeNum("bt4.val", 1);
  myNex.writeNum("bt5.val", 0);
  myNex.writeNum("bt6.val", 0);
  myNex.writeNum("bt7.val", 0);
  myNex.writeNum("bt8.val", 0);
  ant(ant_bank);
}

void trigger5() // x05
{
//  band_mode = 1;
  ant_bank = 5;
  myNex.writeNum("bt1.val", 0);
  myNex.writeNum("bt2.val", 0);
  myNex.writeNum("bt3.val", 0);
  myNex.writeNum("bt4.val", 0);
  myNex.writeNum("bt5.val", 1);
  myNex.writeNum("bt6.val", 0);
  myNex.writeNum("bt7.val", 0);
  myNex.writeNum("bt8.val", 0);
  ant(ant_bank);
}

void trigger6() // x06
{
//  band_mode = 1;
  ant_bank = 6;
  myNex.writeNum("bt1.val", 0);
  myNex.writeNum("bt2.val", 0);
  myNex.writeNum("bt3.val", 0);
  myNex.writeNum("bt4.val", 0);
  myNex.writeNum("bt5.val", 0);
  myNex.writeNum("bt6.val", 1);
  myNex.writeNum("bt7.val", 0);
  myNex.writeNum("bt8.val", 0);
  ant(ant_bank);
}

void trigger7() // x07
{
//  band_mode = 1;
  ant_bank = 7;
  myNex.writeNum("bt1.val", 0);
  myNex.writeNum("bt2.val", 0);
  myNex.writeNum("bt3.val", 0);
  myNex.writeNum("bt4.val", 0);
  myNex.writeNum("bt5.val", 0);
  myNex.writeNum("bt6.val", 0);
  myNex.writeNum("bt7.val", 1);
  myNex.writeNum("bt8.val", 0);
  ant(ant_bank);
}

void trigger8() // x08
{
//  band_mode = 1;
  ant_bank = 8;
  myNex.writeNum("bt1.val", 0);
  myNex.writeNum("bt2.val", 0);
  myNex.writeNum("bt3.val", 0);
  myNex.writeNum("bt4.val", 0);
  myNex.writeNum("bt5.val", 0);
  myNex.writeNum("bt6.val", 0);
  myNex.writeNum("bt7.val", 0);
  myNex.writeNum("bt8.val", 1);
  ant(ant_bank);
}
void trigger9() // updating variables data from Setting page and write to EEPROM
{                // x20
  if (ant1.LoopAnt == 1) {
    myNex.writeStr("page CtrlLoop");
  } else {
     if (ant1.VLAnt == 1) {
      myNex.writeStr("page CtrlVL");
    } else {
    myNex.writeStr("page CtrlATAS");
    }
  }
}

void trigger10() // updating variables data from Setting page and write to EEPROM
{                // x20
  if (ant2.LoopAnt == 1) {
    myNex.writeStr("page CtrlLoop");
  } else {
     if (ant2.VLAnt == 1) {
      myNex.writeStr("page CtrlVL");
    } else {
    myNex.writeStr("page CtrlATAS");
    }
  }
}
void trigger11() // updating variables data from Setting page and write to EEPROM
{                // x20
  if (ant3.LoopAnt == 1) {
    myNex.writeStr("page CtrlLoop");
  } else {
     if (ant3.VLAnt == 1) {
      myNex.writeStr("page CtrlVL");
    } else {
    myNex.writeStr("page CtrlATAS");
    }
  }
}
void trigger12() // updating variables data from Setting page and write to EEPROM
{                // x20
  if (ant4.LoopAnt == 1) {
    myNex.writeStr("page CtrlLoop");
  } else {
     if (ant4.VLAnt == 1) {
      myNex.writeStr("page CtrlVL");
    } else {
    myNex.writeStr("page CtrlATAS");
    }
  }
}
void trigger13() // updating variables data from Setting page and write to EEPROM
{                // x20
  if (ant5.LoopAnt == 1) {
    myNex.writeStr("page CtrlLoop");
  } else {
     if (ant5.VLAnt == 1) {
      myNex.writeStr("page CtrlVL");
    } else {
    myNex.writeStr("page CtrlATAS");
    }
  }
}
void trigger14() // updating variables data from Setting page and write to EEPROM
{                // x20
  if (ant6.LoopAnt == 1) {
    myNex.writeStr("page CtrlLoop");
  } else {
     if (ant6.VLAnt == 1) {
      myNex.writeStr("page CtrlVL");
    } else {
    myNex.writeStr("page CtrlATAS");
    }
  }
}
void trigger15() // updating variables data from Setting page and write to EEPROM
{                // x20
  if (ant7.LoopAnt == 1) {
    myNex.writeStr("page CtrlLoop");
  } else {
     if (ant7.VLAnt == 1) {
      myNex.writeStr("page CtrlVL");
    } else {
    myNex.writeStr("page CtrlATAS");
    }
  }
}
void trigger16() // updating variables data from Setting page and write to EEPROM
{                // x20
  if (ant8.LoopAnt == 1) {
    myNex.writeStr("page CtrlLoop");
  } else {
     if (ant8.VLAnt == 1) {
      myNex.writeStr("page CtrlVL");
    } else {
    myNex.writeStr("page CtrlATAS");
    }
  }
}

void trigger17() // main setup x11
{
  loadEEPROM();
  myNex.writeStr("page AntSetup");
  myNex.writeNum("c1.val", ant1.active);
  String strToWrite;
    strToWrite = ant1.etiquette;
//  Serial.println(strToWrite);
  myNex.writeStr("t11.txt", strToWrite);
  myNex.writeNum("a1b1.val", ant1.band1);
  myNex.writeNum("a1b2.val", ant1.band2);
  myNex.writeNum("a1b3.val", ant1.band3);
  myNex.writeNum("a1b4.val", ant1.band4);
  myNex.writeNum("a1b5.val", ant1.band5);
  myNex.writeNum("a1b6.val", ant1.band6);
  myNex.writeNum("a1b7.val", ant1.band7);
  myNex.writeNum("a1b8.val", ant1.band8);
  myNex.writeNum("a1b9.val", ant1.band9);
  myNex.writeNum("a1b10.val", ant1.band10);
  myNex.writeNum("a1b11.val", ant1.band11);
  myNex.writeNum("a1b12.val", ant1.LoopAnt);
  myNex.writeNum("a1b13.val", ant1.VLAnt);
  myNex.writeNum("a1b14.val", ant1.ATASAnt);

  myNex.writeNum("c2.val", ant2.active);
    strToWrite = ant2.etiquette;
  myNex.writeStr("t12.txt", strToWrite);
  myNex.writeNum("a2b1.val", ant2.band1);
  myNex.writeNum("a2b2.val", ant2.band2);
  myNex.writeNum("a2b3.val", ant2.band3);
  myNex.writeNum("a2b4.val", ant2.band4);
  myNex.writeNum("a2b5.val", ant2.band5);
  myNex.writeNum("a2b6.val", ant2.band6);
  myNex.writeNum("a2b7.val", ant2.band7);
  myNex.writeNum("a2b8.val", ant2.band8);
  myNex.writeNum("a2b9.val", ant2.band9);
  myNex.writeNum("a2b10.val", ant2.band10);
  myNex.writeNum("a2b11.val", ant2.band11);
  myNex.writeNum("a2b12.val", ant2.LoopAnt);
  myNex.writeNum("a2b13.val", ant2.VLAnt);
  myNex.writeNum("a2b14.val", ant2.ATASAnt);

  myNex.writeNum("c3.val", ant3.active);
    strToWrite = ant3.etiquette;
  myNex.writeStr("t13.txt", strToWrite);
  myNex.writeNum("a3b1.val", ant3.band1);
  myNex.writeNum("a3b2.val", ant3.band2);
  myNex.writeNum("a3b3.val", ant3.band3);
  myNex.writeNum("a3b4.val", ant3.band4);
  myNex.writeNum("a3b5.val", ant3.band5);
  myNex.writeNum("a3b6.val", ant3.band6);
  myNex.writeNum("a3b7.val", ant3.band7);
  myNex.writeNum("a3b8.val", ant3.band8);
  myNex.writeNum("a3b9.val", ant3.band9);
  myNex.writeNum("a3b10.val", ant3.band10);
  myNex.writeNum("a3b11.val", ant3.band11);
  myNex.writeNum("a3b12.val", ant3.LoopAnt);
  myNex.writeNum("a3b13.val", ant3.VLAnt);
  myNex.writeNum("a3b14.val", ant3.ATASAnt);

  myNex.writeNum("c4.val", ant4.active);
    strToWrite = ant4.etiquette;
  myNex.writeStr("t14.txt", strToWrite);
  myNex.writeNum("a4b1.val", ant4.band1);
  myNex.writeNum("a4b2.val", ant4.band2);
  myNex.writeNum("a4b3.val", ant4.band3);
  myNex.writeNum("a4b4.val", ant4.band4);
  myNex.writeNum("a4b5.val", ant4.band5);
  myNex.writeNum("a4b6.val", ant4.band6);
  myNex.writeNum("a4b7.val", ant4.band7);
  myNex.writeNum("a4b8.val", ant4.band8);
  myNex.writeNum("a4b9.val", ant4.band9);
  myNex.writeNum("a4b10.val", ant4.band10);
  myNex.writeNum("a4b11.val", ant4.band11);
  myNex.writeNum("a4b12.val", ant4.LoopAnt);
  myNex.writeNum("a4b13.val", ant4.VLAnt);
  myNex.writeNum("a4b14.val", ant4.ATASAnt);

  myNex.writeNum("c5.val", ant5.active);
    strToWrite = ant5.etiquette;
  myNex.writeStr("t15.txt", strToWrite);
  myNex.writeNum("a5b1.val", ant5.band1);
  myNex.writeNum("a5b2.val", ant5.band2);
  myNex.writeNum("a5b3.val", ant5.band3);
  myNex.writeNum("a5b4.val", ant5.band4);
  myNex.writeNum("a5b5.val", ant5.band5);
  myNex.writeNum("a5b6.val", ant5.band6);
  myNex.writeNum("a5b7.val", ant5.band7);
  myNex.writeNum("a5b8.val", ant5.band8);
  myNex.writeNum("a5b9.val", ant5.band9);
  myNex.writeNum("a5b10.val", ant5.band10);
  myNex.writeNum("a5b11.val", ant5.band11);
  myNex.writeNum("a5b12.val", ant5.LoopAnt);
  myNex.writeNum("a5b13.val", ant5.VLAnt);
  myNex.writeNum("a5b14.val", ant5.ATASAnt);

  myNex.writeNum("c6.val", ant6.active);
    strToWrite = ant6.etiquette;
  myNex.writeStr("t16.txt", strToWrite);
  myNex.writeNum("a6b1.val", ant6.band1);
  myNex.writeNum("a6b2.val", ant6.band2);
  myNex.writeNum("a6b3.val", ant6.band3);
  myNex.writeNum("a6b4.val", ant6.band4);
  myNex.writeNum("a6b5.val", ant6.band5);
  myNex.writeNum("a6b6.val", ant6.band6);
  myNex.writeNum("a6b7.val", ant6.band7);
  myNex.writeNum("a6b8.val", ant6.band8);
  myNex.writeNum("a6b9.val", ant6.band9);
  myNex.writeNum("a6b10.val", ant6.band10);
  myNex.writeNum("a6b11.val", ant6.band11);
  myNex.writeNum("a6b12.val", ant6.LoopAnt);
  myNex.writeNum("a6b13.val", ant6.VLAnt);
  myNex.writeNum("a6b14.val", ant6.ATASAnt);

  myNex.writeNum("c7.val", ant7.active);
    strToWrite = ant7.etiquette;
  myNex.writeStr("t17.txt", strToWrite);
  myNex.writeNum("a7b1.val", ant7.band1);
  myNex.writeNum("a7b2.val", ant7.band2);
  myNex.writeNum("a7b3.val", ant7.band3);
  myNex.writeNum("a7b4.val", ant7.band4);
  myNex.writeNum("a7b5.val", ant7.band5);
  myNex.writeNum("a7b6.val", ant7.band6);
  myNex.writeNum("a7b7.val", ant7.band7);
  myNex.writeNum("a7b8.val", ant7.band8);
  myNex.writeNum("a7b9.val", ant7.band9);
  myNex.writeNum("a7b10.val", ant7.band10);
  myNex.writeNum("a7b11.val", ant7.band11);
  myNex.writeNum("a7b12.val", ant7.LoopAnt);
  myNex.writeNum("a7b13.val", ant7.VLAnt);
  myNex.writeNum("a7b14.val", ant7.ATASAnt);

  myNex.writeNum("c8.val", ant8.active);
  strToWrite = ant8.etiquette;
  myNex.writeStr("t18.txt", strToWrite);
  myNex.writeNum("a8b1.val", ant8.band1);
  myNex.writeNum("a8b2.val", ant8.band2);
  myNex.writeNum("a8b3.val", ant8.band3);
  myNex.writeNum("a8b4.val", ant8.band4);
  myNex.writeNum("a8b5.val", ant8.band5);
  myNex.writeNum("a8b6.val", ant8.band6);
  myNex.writeNum("a8b7.val", ant8.band7);
  myNex.writeNum("a8b8.val", ant8.band8);
  myNex.writeNum("a8b9.val", ant8.band9);
  myNex.writeNum("a8b10.val", ant8.band10);
  myNex.writeNum("a8b11.val", ant8.band11);
  myNex.writeNum("a8b12.val", ant8.LoopAnt);
  myNex.writeNum("a8b13.val", ant8.VLAnt);
  myNex.writeNum("a8b14.val", ant8.ATASAnt);

}

void trigger18() // main setup x11
{
//  loadEEPROM();
  myNex.writeStr("page ModeSetup");
}

void trigger19() // main setup x11
{
//  loadEEPROM();
  myNex.writeStr("page RadioSetup");
}

void trigger20() // main setup x11
{
//  loadEEPROM();
  myNex.writeStr("page LoopSetup");
}

void trigger21() // main setup x11
{
//  loadEEPROM();
  myNex.writeStr("page VLSetup");
}

void trigger22() // main setup x11
{
//  loadEEPROM();
  myNex.writeStr("page ATASSetup");
}

void trigger23() // main setup x11
{
//  loadEEPROM();
  dispCtrlSelector();
}

void trigger24() // main setup x11
{
//  loadEEPROM();
  myNex.writeStr("page CtrlLoop");
}

void trigger25() // main setup x11
{
//  loadEEPROM();
  myNex.writeStr("page CtrlVL");
}

void trigger26() // main setup x11
{
//  loadEEPROM();
  myNex.writeStr("page CtrlATAS");
}

void trigger27() // setup applique updating variables data from Setting page and write to EEPROM
{                // x1b

  ant1.active = myNex.readNumber("c1.val");
  String strToWrite = myNex.readStr("t11.txt");
  strToWrite.toCharArray(ant1.etiquette, 20);
//  Serial.println(ant1.etiquette);
  ant1.band1 = myNex.readNumber("a1b1.val");
  ant1.band2 = myNex.readNumber("a1b2.val");
  ant1.band3 = myNex.readNumber("a1b3.val");
  ant1.band4 = myNex.readNumber("a1b4.val");
  ant1.band5 = myNex.readNumber("a1b5.val");
  ant1.band6 = myNex.readNumber("a1b6.val");
  ant1.band7 = myNex.readNumber("a1b7.val");
  ant1.band8 = myNex.readNumber("a1b8.val");
  ant1.band9 = myNex.readNumber("a1b9.val");
  ant1.band10 = myNex.readNumber("a1b10.val");
  ant1.band11 = myNex.readNumber("a1b11.val");
  ant1.LoopAnt = myNex.readNumber("a1b12.val");
  ant1.VLAnt = myNex.readNumber("a1b13.val");
  ant1.ATASAnt = myNex.readNumber("a1b14.val");

  ant2.active = myNex.readNumber("c2.val");
  strToWrite = myNex.readStr("t12.txt");
  strToWrite.toCharArray(ant2.etiquette, 20);
  ant2.band1 = myNex.readNumber("a2b1.val");
  ant2.band2 = myNex.readNumber("a2b2.val");
  ant2.band3 = myNex.readNumber("a2b3.val");
  ant2.band4 = myNex.readNumber("a2b4.val");
  ant2.band5 = myNex.readNumber("a2b5.val");
  ant2.band6 = myNex.readNumber("a2b6.val");
  ant2.band7 = myNex.readNumber("a2b7.val");
  ant2.band8 = myNex.readNumber("a2b8.val");
  ant2.band9 = myNex.readNumber("a2b9.val");
  ant2.band10 = myNex.readNumber("a2b10.val");
  ant2.band11 = myNex.readNumber("a2b11.val");
  ant2.LoopAnt = myNex.readNumber("a2b12.val");
  ant2.VLAnt = myNex.readNumber("a2b13.val");
  ant2.ATASAnt = myNex.readNumber("a2b14.val");

  ant3.active = myNex.readNumber("c3.val");
  strToWrite = myNex.readStr("t13.txt");
  strToWrite.toCharArray(ant3.etiquette, 20);
  ant3.band1 = myNex.readNumber("a3b1.val");
  ant3.band2 = myNex.readNumber("a3b2.val");
  ant3.band3 = myNex.readNumber("a3b3.val");
  ant3.band4 = myNex.readNumber("a3b4.val");
  ant3.band5 = myNex.readNumber("a3b5.val");
  ant3.band6 = myNex.readNumber("a3b6.val");
  ant3.band7 = myNex.readNumber("a3b7.val");
  ant3.band8 = myNex.readNumber("a3b8.val");
  ant3.band9 = myNex.readNumber("a3b9.val");
  ant3.band10 = myNex.readNumber("a3b10.val");
  ant3.band11 = myNex.readNumber("a3b11.val");
  ant3.LoopAnt = myNex.readNumber("a3b12.val");
  ant3.VLAnt = myNex.readNumber("a3b13.val");
  ant3.ATASAnt = myNex.readNumber("a3b14.val");

  ant4.active = myNex.readNumber("c4.val");
  strToWrite = myNex.readStr("t14.txt");
  strToWrite.toCharArray(ant4.etiquette, 20);
  ant4.band1 = myNex.readNumber("a4b1.val");
  ant4.band2 = myNex.readNumber("a4b2.val");
  ant4.band3 = myNex.readNumber("a4b3.val");
  ant4.band4 = myNex.readNumber("a4b4.val");
  ant4.band5 = myNex.readNumber("a4b5.val");
  ant4.band6 = myNex.readNumber("a4b6.val");
  ant4.band7 = myNex.readNumber("a4b7.val");
  ant4.band8 = myNex.readNumber("a4b8.val");
  ant4.band9 = myNex.readNumber("a4b9.val");
  ant4.band10 = myNex.readNumber("a4b10.val");
  ant4.band11 = myNex.readNumber("a4b11.val");
  ant4.LoopAnt = myNex.readNumber("a4b12.val");
  ant4.VLAnt = myNex.readNumber("a4b13.val");
  ant4.ATASAnt = myNex.readNumber("a4b14.val");

  ant5.active = myNex.readNumber("c5.val");
  strToWrite = myNex.readStr("t15.txt");
  strToWrite.toCharArray(ant5.etiquette, 20);
  ant5.band1 = myNex.readNumber("a5b1.val");
  ant5.band2 = myNex.readNumber("a5b2.val");
  ant5.band3 = myNex.readNumber("a5b3.val");
  ant5.band4 = myNex.readNumber("a5b4.val");
  ant5.band5 = myNex.readNumber("a5b5.val");
  ant5.band6 = myNex.readNumber("a5b6.val");
  ant5.band7 = myNex.readNumber("a5b7.val");
  ant5.band8 = myNex.readNumber("a5b8.val");
  ant5.band9 = myNex.readNumber("a5b9.val");
  ant5.band10 = myNex.readNumber("a5b10.val");
  ant5.band11 = myNex.readNumber("a5b11.val");
  ant5.LoopAnt = myNex.readNumber("a5b12.val");
  ant5.VLAnt = myNex.readNumber("a5b13.val");
  ant5.ATASAnt = myNex.readNumber("a5b14.val");

  ant6.active = myNex.readNumber("c6.val");
  strToWrite = myNex.readStr("t16.txt");
  strToWrite.toCharArray(ant6.etiquette, 20);
  ant6.band1 = myNex.readNumber("a6b1.val");
  ant6.band2 = myNex.readNumber("a6b2.val");
  ant6.band3 = myNex.readNumber("a6b3.val");
  ant6.band4 = myNex.readNumber("a6b4.val");
  ant6.band5 = myNex.readNumber("a6b5.val");
  ant6.band6 = myNex.readNumber("a6b6.val");
  ant6.band7 = myNex.readNumber("a6b7.val");
  ant6.band8 = myNex.readNumber("a6b8.val");
  ant6.band9 = myNex.readNumber("a6b9.val");
  ant6.band10 = myNex.readNumber("a6b10.val");
  ant6.band11 = myNex.readNumber("a6b11.val");
  ant6.LoopAnt = myNex.readNumber("a6b12.val");
  ant6.VLAnt = myNex.readNumber("a6b13.val");
  ant6.ATASAnt = myNex.readNumber("a6b14.val");

  ant7.active = myNex.readNumber("c7.val");
  strToWrite = myNex.readStr("t17.txt");
  strToWrite.toCharArray(ant7.etiquette, 20);
  ant7.band1 = myNex.readNumber("a7b1.val");
  ant7.band2 = myNex.readNumber("a7b2.val");
  ant7.band3 = myNex.readNumber("a7b3.val");
  ant7.band4 = myNex.readNumber("a7b4.val");
  ant7.band5 = myNex.readNumber("a7b5.val");
  ant7.band6 = myNex.readNumber("a7b6.val");
  ant7.band7 = myNex.readNumber("a7b7.val");
  ant7.band8 = myNex.readNumber("a7b8.val");
  ant7.band9 = myNex.readNumber("a7b9.val");
  ant7.band10 = myNex.readNumber("a7b10.val");
  ant7.band11 = myNex.readNumber("a7b11.val");
  ant7.LoopAnt = myNex.readNumber("a7b12.val");
  ant7.VLAnt = myNex.readNumber("a7b13.val");
  ant7.ATASAnt = myNex.readNumber("a7b14.val");

  ant8.active = myNex.readNumber("c8.val");
  strToWrite = myNex.readStr("t18.txt");
  strToWrite.toCharArray(ant8.etiquette, 20);
  ant8.band1 = myNex.readNumber("a8b1.val");
  ant8.band2 = myNex.readNumber("a8b2.val");
  ant8.band3 = myNex.readNumber("a8b3.val");
  ant8.band4 = myNex.readNumber("a8b4.val");
  ant8.band5 = myNex.readNumber("a8b5.val");
  ant8.band6 = myNex.readNumber("a8b6.val");
  ant8.band7 = myNex.readNumber("a8b7.val");
  ant8.band8 = myNex.readNumber("a8b8.val");
  ant8.band9 = myNex.readNumber("a8b9.val");
  ant8.band10 = myNex.readNumber("a8b10.val");
  ant8.band11 = myNex.readNumber("a8b11.val");
  ant8.LoopAnt = myNex.readNumber("a8b12.val");
  ant8.VLAnt = myNex.readNumber("a8b13.val");
  ant8.ATASAnt = myNex.readNumber("a8b14.val");

  saveEEPROM();

  myNex.writeStr("page MenuSetup");
//  dispPage1();
}

void trigger28() // main setup x11
{
//  loadEEPROM();
  myNex.writeStr("page BridgeSetup");
}

void trigger29() // save Mode Setup
{
//  saveEEPROM();
  myNex.writeStr("page MenuSetup");
}

void trigger30() // save RadioSetup
{
//  saveEEPROM();
  myNex.writeStr("page MenuSetup");
}

void trigger31() // save BridgeSetup
{
//  saveEEPROM();
  myNex.writeStr("page MenuSetup");
}

void trigger32() // save LoopSetup
{
//  saveEEPROM();
  myNex.writeStr("page MenuSetup");
}

void trigger33() // save VLSetup
{
//  saveEEPROM();
  if (myNex.readNumber("c2.val")== 1)
    vl_param.units=1;
  else
    vl_param.units=2;

  if (myNex.readNumber("c0.val")== 1)
    vl_param.MotorN=1;
  else
    vl_param.MotorN=2;

  if (myNex.readNumber("c4.val")== 1)
    vl_param.encoderN=1;
  else
    vl_param.encoderN=2;

  vl_param.pulseround=myNex.readNumber("pulseround.val");                  // Position Information, referenced at 1000000
  vl_param.unitsround=myNex.readNumber("roundlength.val");                  // Position Information, referenced at 1000000
  vl_param.motorspeed=myNex.readNumber("motorspeed.val");                  // Position Information, referenced at 1000000
  vl_param.maxlength=myNex.readNumber("maxlen.val");                  // Position Information, referenced at 1000000

  saveEEPROM();

  myNex.writeStr("page MenuSetup");
}

void trigger34() // save ATASSetup
{
//  saveEEPROM();
  myNex.writeStr("page MenuSetup");
}
