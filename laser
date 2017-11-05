const int laser = 3;
const int button = 8;
const int led = 10;
const int sensor = A0;

int threshold = 500;

void setup() {
  pinMode(laser, OUTPUT);
  pinMode(button, INPUT);
  pinMode(sensor, INPUT);
  pinMode(led, OUTPUT);
  

}

void loop() {
 
  
  if(digitalRead(button) == HIGH){
    digitalWrite(laser,HIGH);
  }
  else{
     digitalWrite(laser,LOW);
    }


  if(analogRead(sensor) > threshold){
    digitalWrite(led, HIGH);
    }
}
