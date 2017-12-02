/*
 * Code to control RC bot
 * By: Aryton Hoi
 */
#include <Servo.h>
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

//Set up NRF
RF24 radio(8,9); // CE, CSN
const byte address[6] = "00001";

//Setup L298
// Right Motor A
const int enA = 6;
const int in1 = 5;
const int in2 = 7;
// Left Motor B
const int enB = 3;
const int in3 = 2;
const int in4 = 4;

// Motor speed values - Start at zero
int MotorSpeed1 = 0;
int MotorSpeed2 = 0;

void setup()                                 
{ 
  Serial.begin(9600);
  
  //Begin wireless communication
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  //Set NRF as receiver
  radio.startListening();

  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Start with motors disabled and direction forward
  // Right Motor A
  digitalWrite(enA, LOW);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // Right Motor B
  digitalWrite(enB, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}  
 
void loop(){
  if(radio.available())
  {
      int transmit[3];            
      radio.read(&transmit, sizeof(transmit));

      //Right Motor 1
      if(transmit[0] < 450){
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        transmit[0] = transmit[0] - 450; // This produces a negative number
        transmit[0] = transmit[0] * -1;  // Make the number positive
        MotorSpeed1 = map(transmit[0], 0, 450, 0, 255);
        Serial.print(", ");
        analogWrite(enA, MotorSpeed1);
      }else if(transmit[0] > 560){
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        MotorSpeed1 = map(transmit[0], 560, 1023, 0, 255); 
        Serial.print(", ");
        analogWrite(enA, MotorSpeed1);
      }else{
        MotorSpeed1 = 0;
        analogWrite(enA, MotorSpeed1);
      }

      //Motor 2
      if(transmit[1] < 450){
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        transmit[1] = transmit[1] - 450; // This produces a negative number
        transmit[1] = transmit[1] * -1;  // Make the number positive
        MotorSpeed2 = map(transmit[1], 0, 450, 0, 255);
        analogWrite(enB, MotorSpeed1);
      }else if(transmit[1] > 560){
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        MotorSpeed2 = map(transmit[1], 560, 1023, 0, 255); 
        analogWrite(enB, MotorSpeed2);
      }else{
        MotorSpeed2 = 0;
        analogWrite(enB, MotorSpeed2);
      }
  }
    Serial.print(MotorSpeed1);
    Serial.print(", ");
    Serial.println(MotorSpeed2);
    delay(10);
}
  
