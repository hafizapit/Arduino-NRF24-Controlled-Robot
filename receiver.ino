/*
 * Code Modified By: Mohamad Hafiz Bin Ahmad
 * Email: hafiz_apik99@yahoo.com
 * Youtube: https://www.youtube.com/channel/UC15t8HwKsRL2lTeP8uZlUjQ
*/

#include <SPI.h>
#include <RF24.h> //https://www.arduinolibraries.info/libraries/rf24
#include <CytronMotorDriver.h> //https://github.com/CytronTechnologies/CytronMotorDriver

RF24 radio(7, 8);// CE, CSN

const byte rxAddr[6] = "00001";

int joystick[6];

// tetapan motor driver.
CytronMD motor1(PWM_PWM, 3, 4);   // PWM 1A = Pin 3, PWM 1B = Pin 4. Kalau motor pusing terbalik, tukarkan PWM 1A = Pin 4, PWM 1B = Pin 3
CytronMD motor2(PWM_PWM, 5, 6); // PWM 2A = Pin 5, PWM 2B = Pin 6. Kalau motor pusing terbalik, tukarkan PWM 2A = Pin 6,PWM 2B = Pin 5

void setup() 
{
   for(int i = 2; i<=4; i++)
   {
    pinMode(i,OUTPUT);
  }

  //setup utk komunikasi radio
  while (!Serial);
  Serial.begin(9600); //aktifkan serial monitor
  
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.setAutoAck(false);
  radio.openReadingPipe(0, rxAddr);
  
  radio.startListening();
  
  delay(50);
}

void loop() 
{
 if (radio.available())//semak samada ada data utk diterima
  {
    bool done = false;
         while (!done)
        { 
          
          radio.read( joystick, sizeof(joystick) );//membaca nilai yg dihantar oleh pemancar
          done = true; 

          Serial.print("VRY ="); //untuk menyemak nilai bacaan joystick, boleh disemak pada serial monitor
          Serial.println(joystick[0]);
          Serial.print("VRX =");
          Serial.println(joystick[1]);

       if(joystick[0]==0)// jika joystick ditolak sepenuhnya keatas, nilai ialah 0
         {        
           Serial.println("Forward");
           motor1.setSpeed(255);   // Motor 1 runs forward at 100% speed.
           motor2.setSpeed(255);  // Motor 2 runs forward at 100% speed.
          /*
           * anda boleh mengubah nilai PWM daripada 0-1023
           * jika robot tidak berjalan lurus walaupun nilai PWM yg sama, cuba ubah nilai PWM hingga robot berjalan lurus
          */
          
        }
      
        else if(joystick[0]==1023) //jika joystick ditolak sepenuhnya kebawah, nilai ialah 1023
         { 
          
        Serial.println("backward");
        motor1.setSpeed(-255);   // Motor 1 runs backward at 100% speed.
        motor2.setSpeed(-255);  // Motor 2 runs backward at 100% speed.
        
        }
      
         else if(joystick[1]==1023) //jika joystick ditolak sepenuhnya ke kanan, nilai ialah 1023
         { 
          
        Serial.println("right");
        motor1.setSpeed(255);   // Motor 1 runs forward at 50% speed.
        motor2.setSpeed(0);  // Motor 2 stops
        
        }
      
         else if(joystick[1]==0) //jika joystick ditolak sepenuhnya ke kiri, nilai ialah 0
         { 
          
        Serial.println("left");
        motor1.setSpeed(0);   // Motor 1 stops.
        motor2.setSpeed(255);  // Motor 2 runs forward at 50% speed.
        
        }
        
        else // joystick berada di tengah
        {
        Serial.println("stop");
        motor1.setSpeed(0);   
        motor2.setSpeed(0);   
        }

        }
  }
  
  else
    {
      Serial.println("Data not received");
      
    }
  
  delay(50);
}
