/*
* Code for controller
* By: Aryton Hoi
*/
#include <Servo.h>
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

//Setup NRF
RF24 radio(7,8); // CE, CSN
const byte address[6] = "00001";

//Setup joysticks
const int joy1 = A0;//blue
const int joy2 = A1;//black
//Setup joystick position values (middle position)
int joy1Pos;
int joy2Pos;

//Setup buttons
const int button1 = A2;
int button1State;

//Setup vibrator
const int vibrator = 9;
int vibstate;

void setup()
{
  Serial.begin(9600);
  
  //Start wireless communication
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  //Set NRF as transmitter
  radio.stopListening();

  //setup button pins
  pinMode(button1, INPUT); 
  //Setup vibrator pins
  pinMode(vibrator, OUTPUT);

}
void loop()
{
  //Read joystick positions
  joy1Pos = analogRead(joy2); //change to joy1
  joy2Pos = analogRead(joy2);

  button1State = digitalRead(button1);
  if(button1State == 1){
    digitalWrite(vibrator, HIGH);
  }else{
    digitalWrite(vibrator, LOW);
  }
  //format and transmit input data
  int transmit[3] = {joy1Pos, joy2Pos, button1State};
  radio.write(&transmit, sizeof(transmit));
  Serial.print(transmit[0]);
  Serial.print(", ");
  Serial.print(transmit[1]);
  Serial.print(", ");
  Serial.println(transmit[2]);
  
//Serial.println(button1State);
  delay(10);
}

