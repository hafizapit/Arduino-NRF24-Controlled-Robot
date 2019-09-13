#include <SPI.h>
#include <nRF24L01.h> 
#include <RF24.h> //https://www.arduinolibraries.info/libraries/rf24

RF24 radio(7, 8);//CE,CSN

const byte rxAddr[6] = "00001";

int sendingdata[6];

void setup()
{
  Serial.begin(9600); //aktifkan serial monitor
  
  //tetapan utk komunikasi radio
  radio.begin();  //aktifkan modul pemancar
  radio.setPALevel(RF24_PA_LOW);
  radio.setAutoAck(false);
  radio.setRetries(15, 15);
  radio.openWritingPipe(rxAddr);
  
  radio.stopListening();

  delay(50);
}

void loop()
{
  int VRY = analogRead(A0); //Baca nilai analog joystick
  int VRX = analogRead(A1);
  
  sendingdata[0]=VRY;
  sendingdata[1]=VRX;
  
  radio.write( sendingdata, sizeof(sendingdata) );

  //untuk menyemak nilai bacaan joystick, boleh disemak pada serial monitor
  Serial.print("VRY =");
  Serial.println(sendingdata[0]);
  Serial.print("VRX =");
  Serial.println(sendingdata[1]);
  delay(50);
  
}
