void loadEEPROM()
{
//  Serial.println("debut lecture eeprom");
  EEPROM.get(50, current_band);
  EEPROM.get(52, current_ant);

  EEPROM.get(100, ant1);
  EEPROM.get(136, ant2);
  EEPROM.get(172, ant3);
  EEPROM.get(208, ant4);
  EEPROM.get(244, ant5);
  EEPROM.get(280, ant6);
  EEPROM.get(316, ant7);
  EEPROM.get(352, ant8);
//  Serial.println("Fin lecture eeprom");

}

void saveEEPROM()
{
//  Serial.println("debut ecriture eeprom");

  EEPROM.put(50, current_band);
  EEPROM.put(52, current_ant);

  EEPROM.put(100, ant1);
  EEPROM.put(136, ant2);
  EEPROM.put(172, ant3);
  EEPROM.put(208, ant4);
  EEPROM.put(244, ant5);
  EEPROM.put(280, ant6);
  EEPROM.put(316, ant7);
  EEPROM.put(352, ant8);
//  Serial.println("Fin ecriture eeprom");

}
