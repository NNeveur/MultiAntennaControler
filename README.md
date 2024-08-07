# Multi Antennas Switcher and Controler
 Controler to switch from up to 8 Antennas types MagLoop, VariLenght (Poorman StepR) Slopper and Dipole, and Modules control for them.
 
 Main controler is a Teensy 4.0 with a Nextion tactil screen and a rotary encoder.
 
 It talk to Antenna control module via a RS485 bus with a 12v supply tru a RJ45 and network cable ( preferably sheilded) pair 1 =+12V pair 2 = RS485 A pair 3 = RS485 B pair 4 = Ground
 
 It also have a TTL RS232 CAT Radio control, I2C if need, Frequency counter to read Frequency from sampled TX and Standing wave Bridge Forward / Reverse
 
 Everything Customiable, from naming tag antenna, to type of antenna and what band covered by it.
 
 Antenna selection can be manualy selected or fully automated from reading CAT or Frequency counter.
 
 When an antenna is selected, antenna switcher relay is activated and also power to it RS485 is given.
 
 So Antenna Module control is powered.
 
 Typical Antenna Module controle is a Arduino Nano based with is RS485 interface and a 5v regulated supply for 12V
 
 The Magnetic Loop Antenna module control have Sparkfun.com Big Easy Step motor driver.
 
 Mag Loop Controler software is greatly inspired by Loftur TF3LJ/VE2AO Mag Loop Controler
 
 The VariLength (Poorman StepR) Antenna module control have one or two L298N DC motor driver and one or two photo counter for a wheel counter to count length of the wire.
 
 I have couple of boards in production, I need to do hardware debuging
 
 Software for Main Controler (Teensy) is not fully done.
 
 Prototype
 ![AntSwproto1](https://github.com/user-attachments/assets/e4569b35-5414-409a-beb9-1ca9d276e5d4)

 ![AntSwproto2](https://github.com/user-attachments/assets/b6593467-0b5f-463d-9579-c6f4afa6e730)

![MainControl](https://github.com/user-attachments/assets/b221a1fb-7753-4c5d-a02f-8de5f6859774)
![SetupControl](https://github.com/user-attachments/assets/cce99413-3a82-4369-b0eb-89f44497b111)

