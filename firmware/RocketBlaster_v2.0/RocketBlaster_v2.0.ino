#include "SoftwareSerial.h"
#include "DFPlayer.h"
#define Start_Byte     0x7E
#define Version_Byte   0xFF
#define Command_Length 0x06
#define End_Byte       0xEF
#define Acknowledge    0x00

const byte rxPin = 11;
const byte txPin = 10;
const byte relayPin = 8;
const byte switchPin = 9;
const byte safetyPin = 7;
const byte ledPin = 13;
DFPlayer player(11, 10);
 
void setup () 
{
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(switchPin, INPUT);
  pinMode(safetyPin, INPUT);
  Serial.begin(9600);
  
  digitalWrite(relayPin, HIGH);

  // Send request for initialization parameters
  player.initialize();
  
  // Set sound to 30 of 48
  player.volumeSet(0x1E);
  
  Serial.println("Setup complete");
  
  // LED indicator for "ready" status
  indicate_ready();
}
 
void loop () 
{
  bool safety = false;
  bool launch = false;

  if(digitalRead(switchPin) == HIGH && digitalRead(safetyPin) == HIGH)
  {
    if(player.serial.available()>=10)
    {
      Serial.println("Launch sequence start");
      launch_sequence();
    }
    else
    {
      Serial.println("Busy, try again later...");
      // LED indicator for "busy" status
      indicate_busy();
    }
  }
}

void launch_sequence()
{
  digitalWrite(ledPin, HIGH);
  
  // Play track 2
  player.track(0, 2);
  delay(11000);
  
  // Pause track
  Serial.println("Pausing");
  player.pause();
  
  // Relay activate (launch)
  Serial.println("Launching");
  digitalWrite(relayPin, LOW);
  delay(300);
  
  // Relay deactivate
  digitalWrite(relayPin, HIGH);
  
  // Continue track
  player.play();
  delay(2600);
  
  // Stop play
  Serial.println("Stopping");
  player.stop();
  
  digitalWrite(ledPin, LOW);
}

void indicate_ready()
{
  for(byte i=0; i<5; i++)
    {
      digitalWrite(ledPin, HIGH);
      delay(250);
      digitalWrite(ledPin, LOW);
      delay(250);
    }
}

void indicate_busy()
{
  for(byte i=0; i<3; i++)
    {
      digitalWrite(ledPin, HIGH);
      delay(500);
      digitalWrite(ledPin, LOW);
      delay(500);
    }
}
