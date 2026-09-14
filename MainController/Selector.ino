void display_antsel(int Nant)
{
  if (last_display_ant != Nant)
  {
    switch (Nant)
    {
    case 1:
      myNex.writeNum("bt1.val", 1);
      myNex.writeNum("bt2.val", 0);
      myNex.writeNum("bt3.val", 0);
      myNex.writeNum("bt4.val", 0);
      myNex.writeNum("bt5.val", 0);
      myNex.writeNum("bt6.val", 0);
      myNex.writeNum("bt7.val", 0);
      myNex.writeNum("bt8.val", 0);
      break;

    case 2:
      myNex.writeNum("bt1.val", 0);
      myNex.writeNum("bt2.val", 1);
      myNex.writeNum("bt3.val", 0);
      myNex.writeNum("bt4.val", 0);
      myNex.writeNum("bt5.val", 0);
      myNex.writeNum("bt6.val", 0);
      myNex.writeNum("bt7.val", 0);
      myNex.writeNum("bt8.val", 0);
      break;

    case 3:
      myNex.writeNum("bt1.val", 0);
      myNex.writeNum("bt2.val", 0);
      myNex.writeNum("bt3.val", 1);
      myNex.writeNum("bt4.val", 0);
      myNex.writeNum("bt5.val", 0);
      myNex.writeNum("bt6.val", 0);
      myNex.writeNum("bt7.val", 0);
      myNex.writeNum("bt8.val", 0);
      break;

    case 4:
      myNex.writeNum("bt1.val", 0);
      myNex.writeNum("bt2.val", 0);
      myNex.writeNum("bt3.val", 0);
      myNex.writeNum("bt4.val", 1);
      myNex.writeNum("bt5.val", 0);
      myNex.writeNum("bt6.val", 0);
      myNex.writeNum("bt7.val", 0);
      myNex.writeNum("bt8.val", 0);
      break;

    case 5:
      myNex.writeNum("bt1.val", 0);
      myNex.writeNum("bt2.val", 0);
      myNex.writeNum("bt3.val", 0);
      myNex.writeNum("bt4.val", 0);
      myNex.writeNum("bt5.val", 1);
      myNex.writeNum("bt6.val", 0);
      myNex.writeNum("bt7.val", 0);
      myNex.writeNum("bt8.val", 0);
      break;

    case 6:
      myNex.writeNum("bt1.val", 0);
      myNex.writeNum("bt2.val", 0);
      myNex.writeNum("bt3.val", 0);
      myNex.writeNum("bt4.val", 0);
      myNex.writeNum("bt5.val", 0);
      myNex.writeNum("bt6.val", 1);
      myNex.writeNum("bt7.val", 0);
      myNex.writeNum("bt8.val", 0);
      break;

    case 7:
      myNex.writeNum("bt1.val", 0);
      myNex.writeNum("bt2.val", 0);
      myNex.writeNum("bt3.val", 0);
      myNex.writeNum("bt4.val", 0);
      myNex.writeNum("bt5.val", 0);
      myNex.writeNum("bt6.val", 0);
      myNex.writeNum("bt7.val", 1);
      myNex.writeNum("bt8.val", 0);
      break;

    case 8:
      myNex.writeNum("bt1.val", 0);
      myNex.writeNum("bt2.val", 0);
      myNex.writeNum("bt3.val", 0);
      myNex.writeNum("bt4.val", 0);
      myNex.writeNum("bt5.val", 0);
      myNex.writeNum("bt6.val", 0);
      myNex.writeNum("bt7.val", 0);
      myNex.writeNum("bt8.val", 1);
      break;
    }
    last_display_ant = Nant;
  }
}

void set_ant(int ant_relay)
{
//  digitalWrite(RS_En, HIGH);
  Serial2.println(SW_ALL_OFF);
  Serial.println(SW_ALL_OFF);
  delay(500);
  Serial2.print(SW_ANT_ON);
  Serial2.println(ant_relay);
  Serial.print(SW_ANT_ON);
  Serial.println(ant_relay);
//  Serial2.print('/n');
  delay(500);
//  digitalWrite(RS_En, LOW);


}

void ant(int Nrelay)
{
  if (last_ant_relay != Nrelay)
  {
    EEPROM.put(50, current_ant); // Update band info to Memory when LPF chnages
    EEPROM.put(52, Nrelay);       // Update band info to Memory when LPF chnages

    set_ant(Nrelay);
     Serial.print("Nrelay:");
     Serial.println(Nrelay);
    // Serial.print("Current Band:");
    // Serial.println(current_band);

    current_ant = Nrelay;
    last_ant_relay = Nrelay;
  }
}


void dispCtrlSelector() {

  String strToWrite;

  loadEEPROM();
  myNex.writeStr("page CtrlSelector");

 if (ant1.active ==1) {
   myNex.writeStr("tsw bt1,1");
   myNex.writeNum("bt1.bco", 50712);
  strToWrite = ant1.etiquette;
  myNex.writeStr("bt1.txt", strToWrite);
  if ((ant1.LoopAnt == 1) || (ant1.VLAnt == 1) || (ant1.ATASAnt == 1)) {
    myNex.writeNum("bt1.h", 40);
    if (ant1.LoopAnt == 1) {
      myNex.writeStr("bc1.txt", LoopTag);
    } else {
      if (ant1.VLAnt == 1) {
        myNex.writeStr("bc1.txt", VLTag);
      } else {
        myNex.writeStr("bc1.txt", ATASTag);
      }
    }
    myNex.writeStr("vis 11,1");
    } else {
    myNex.writeNum("bt1.h", 81);
    myNex.writeStr("vis 11,0");
  }
   } else {
   myNex.writeNum("bt1.h", 81);
   myNex.writeStr("tsw bt1,0");
   myNex.writeStr("bt1.txt", InacTag);
   myNex.writeNum("bt1.bco", 27469);
   myNex.writeStr("vis 11,0");
 }

 if (ant2.active ==1) {
   myNex.writeStr("tsw bt2,1");
   myNex.writeNum("bt2.bco", 50712);
  strToWrite = ant2.etiquette;
  myNex.writeStr("bt2.txt", strToWrite);
  if ((ant2.LoopAnt == 1) || (ant2.VLAnt == 1) || (ant2.ATASAnt == 1)) {
    myNex.writeNum("bt2.h", 40);
    if (ant2.LoopAnt == 1) {
      myNex.writeStr("bc2.txt", LoopTag);
    } else {
      if (ant2.VLAnt == 1) {
        myNex.writeStr("bc2.txt", VLTag);
      } else {
        myNex.writeStr("bc2.txt", ATASTag);
      }
    }
    myNex.writeStr("vis 12,1");
    } else {
      myNex.writeNum("bt2.h", 81);
    myNex.writeStr("vis 12,0");
  }
 } else {
  myNex.writeNum("bt2.h", 81);
   myNex.writeStr("tsw bt2,0");
   myNex.writeStr("bt2.txt", InacTag);
   myNex.writeNum("bt2.bco", 27469);
   myNex.writeStr("vis 12,0");
 }

 if (ant3.active ==1) {
   myNex.writeStr("tsw bt3,1");
   myNex.writeNum("bt3.bco", 50712);
  strToWrite = ant3.etiquette;
  myNex.writeStr("bt3.txt", strToWrite);
  if ((ant3.LoopAnt==1) || (ant3.VLAnt==1) || (ant3.ATASAnt==1)) {
    myNex.writeNum("bt3.h", 40);
    if (ant3.LoopAnt==1) {
      myNex.writeStr("bc3.txt", LoopTag);
    } else {
      if (ant3.VLAnt==1) {
        myNex.writeStr("bc3.txt", VLTag);
      } else {
        myNex.writeStr("bc3.txt", ATASTag);
      }
    }
    myNex.writeStr("vis 13,1");
    } else {
      myNex.writeNum("bt3.h", 81);
    myNex.writeStr("vis 13,0");
  }
 } else {
  myNex.writeNum("bt3.h", 81);
   myNex.writeStr("tsw bt3,0");
   myNex.writeStr("bt3.txt", InacTag);
   myNex.writeNum("bt3.bco", 27469);
   myNex.writeStr("vis 13,0");
}

 if (ant4.active ==1) {
   myNex.writeStr("tsw bt4,1");
   myNex.writeNum("bt4.bco", 50712);
  strToWrite = ant4.etiquette;
  myNex.writeStr("bt4.txt", strToWrite);
  if ((ant4.LoopAnt==1) || (ant4.VLAnt==1) || (ant4.ATASAnt==1)) {
    myNex.writeNum("bt4.h", 40);
    if (ant4.LoopAnt==1) {
      myNex.writeStr("bc4.txt", LoopTag);
    } else {
      if (ant4.VLAnt==1) {
        myNex.writeStr("bc4.txt", VLTag);
      } else {
        myNex.writeStr("bc4.txt", ATASTag);
      }
    }
    myNex.writeStr("vis 14,1");
    } else {
      myNex.writeNum("bt4.h", 81);
    myNex.writeStr("vis 14,0");
  }
 } else {
  myNex.writeNum("bt4.h", 81);
   myNex.writeStr("tsw bt4,0");
   myNex.writeStr("bt4.txt", InacTag);
   myNex.writeNum("bt4.bco", 27469);
    myNex.writeStr("vis 14,0");
}

 if (ant5.active ==1) {
   myNex.writeStr("tsw bt5,1");
   myNex.writeNum("bt5.bco", 50712);
  strToWrite = ant5.etiquette;
  myNex.writeStr("bt5.txt", strToWrite);
  if ((ant5.LoopAnt==1) || (ant5.VLAnt==1) || (ant5.ATASAnt==1)) {
    myNex.writeNum("bt5.h", 40);
    if (ant5.LoopAnt==1) {
      myNex.writeStr("bc5.txt", LoopTag);
    } else {
      if (ant5.VLAnt==1) {
        myNex.writeStr("bc5.txt", VLTag);
      } else {
        myNex.writeStr("bc5.txt", ATASTag);
      }
    }
    myNex.writeStr("vis 15,1");
    } else {
      myNex.writeNum("bt5.h", 81);
    myNex.writeStr("vis 15,0");
  }
 } else {
  myNex.writeNum("bt5.h", 81);
   myNex.writeStr("tsw bt5,0");
   myNex.writeStr("bt5.txt", InacTag);
   myNex.writeNum("bt5.bco", 27469);
    myNex.writeStr("vis 15,0");
}

 if (ant6.active ==1) {
   myNex.writeStr("tsw bt6,1");
   myNex.writeNum("bt6.bco", 50712);
  strToWrite = ant6.etiquette;
  myNex.writeStr("bt6.txt", strToWrite);
  if ((ant6.LoopAnt==1) || (ant6.VLAnt==1) || (ant6.ATASAnt==1)) {
    myNex.writeNum("bt6.h", 40);
    if (ant6.LoopAnt==1) {
      myNex.writeStr("bc6.txt", LoopTag);
    } else {
      if (ant6.VLAnt==1) {
        myNex.writeStr("bc6.txt", VLTag);
      } else {
        myNex.writeStr("bc6.txt", ATASTag);
      }
    }
    myNex.writeStr("vis 16,1");
    } else {
      myNex.writeNum("bt6.h", 81);
    myNex.writeStr("vis 16,0");
  }
 } else {
  myNex.writeNum("bt6.h", 81);
   myNex.writeStr("tsw bt6,0");
   myNex.writeStr("bt6.txt", InacTag);
   myNex.writeNum("bt6.bco", 27469);
    myNex.writeStr("vis 16,0");
}

 if (ant7.active ==1) {
   myNex.writeStr("tsw bt7,1");
   myNex.writeNum("bt7.bco", 50712);
  strToWrite = ant7.etiquette;
  myNex.writeStr("bt7.txt", strToWrite);
  if ((ant7.LoopAnt==1) || (ant7.VLAnt==1) || (ant7.ATASAnt==1)) {
    myNex.writeNum("bt7.h", 40);
    if (ant7.LoopAnt==1) {
      myNex.writeStr("bc7.txt", LoopTag);
    } else {
      if (ant7.VLAnt==1) {
        myNex.writeStr("bc7.txt", VLTag);
      } else {
        myNex.writeStr("bc7.txt", ATASTag);
      }
    }
    myNex.writeStr("vis 17,1");
    } else {
      myNex.writeNum("bt7.h", 81);
    myNex.writeStr("vis 17,0");
  }
 } else {
  myNex.writeNum("bt7.h", 81);
   myNex.writeStr("tsw bt7,0");
   myNex.writeStr("bt7.txt", InacTag);
   myNex.writeNum("bt7.bco", 27469);
    myNex.writeStr("vis 17,0");
}

 if (ant8.active ==1) {
   myNex.writeStr("tsw bt8,1");
   myNex.writeNum("bt8.bco", 50712);
  strToWrite = ant8.etiquette;
  myNex.writeStr("bt8.txt", strToWrite);
  if ((ant8.LoopAnt==1) || (ant8.VLAnt==1) || (ant8.ATASAnt==1)) {
    myNex.writeNum("bt8.h", 40);
    if (ant8.LoopAnt==1) {
      myNex.writeStr("bc8.txt", LoopTag);
    } else {
      if (ant8.VLAnt==1) {
        myNex.writeStr("bc8.txt", VLTag);
      } else {
        myNex.writeStr("bc8.txt", ATASTag);
      }
    }
    myNex.writeStr("vis 18,1");
    } else {
      myNex.writeNum("bt8.h", 81);
    myNex.writeStr("vis 18,0");
  }
 } else {
  myNex.writeNum("bt8.h", 81);
   myNex.writeStr("tsw bt8,0");
   myNex.writeStr("bt8.txt", InacTag);
   myNex.writeNum("bt8.bco", 27469);
    myNex.writeStr("vis 18,0");
}

}
