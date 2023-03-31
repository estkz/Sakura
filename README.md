# Sakura
The line-following robot made for Arduino, equipped to traverse a parkour made of lines with ease

Sakura live got released to public on 27-3-2022!

/*                                                         +-----+
*                             +----[PWR]-------------------| USB |--+
*                             |                            +-----+  |
*                             |         GND/RST2  [ ][ ]            |
*                             |       MOSI2/SCK2  [ ][ ]  A5/SCL[ ] |   C5 
*                             |          5V/MISO2 [ ][ ]  A4/SDA[ ] |   C4 
*                             |                             AREF[ ] |
*                             |                              GND[ ] |
*                             | [ ]N/C                    SCK/13[ ] | - Direction Motor B
*                             | [ ]IOREF                 MISO/12[ ] | - Direction Motor A
*                             | [ ]RST                   MOSI/11[ ]~| - PWM Motor B
*                             | [ ]3V3    +---+               10[ ]~| - TCRT5000 Sensor 1
*                             | [ ]5v    -| A |-               9[ ]~| - Echo pin of the ultrasonic sensor
*                             | [ ]GND   -| R |-               8[ ] | - Trigger pin of the ultrasonic sensor
*                             | [ ]GND   -| D |-                    |
*                             | [ ]Vin   -| U |-               7[ ] | - TCRT5000 Sensor 2
*                             |          -| I |-               6[ ]~| - TCRT5000 Sensor 3
*   current sensing motor A - | [ ]A0    -| N |-               5[ ]~| - TCRT5000 Sensor 4
*   current sensing motor B - | [ ]A1    -| O |-               4[ ] | - TCRT5000 Sensor 5
*                             | [ ]A2     +---+           INT1/3[ ]~| - PWM Motor A
*                             | [ ]A3                     INT0/2[ ] |
*                             | [ ]A4/SDA  RST SCK MISO     TX>1[ ] | - SERIAL TX
*                             | [ ]A5/SCL  [ ] [ ] [ ]      RX<0[ ] | - SERIAL RX
*                             |            [ ] [ ] [ ]              |
*                             |  UNO_R3    GND MOSI 5V  ____________/
*                              \_______________________/
*/
