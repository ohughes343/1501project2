const int laser = 3;
const int button = 8;
const int led = 10;
const int sensor = A0;

int threshold = 700;


int sensorMax = 0;
  int sensorMin = 1023;
  int sensorValue = 0;

  
void setup() {
  pinMode(laser, OUTPUT);
  pinMode(button, INPUT);
  pinMode(sensor, INPUT);
  pinMode(led, OUTPUT);

  digitalWrite(led,HIGH);//turn on led1 to signal calibration period
   
  //calibrate during first five seconds
  while(millis() < 5000){
    sensorValue = analogRead(sensor);

    if(sensorValue > sensorMax){
        sensorMax = sensorValue;
      }
    if(sensorValue < sensorMin){
        sensorMin = sensorValue;
      }
    
    }

    digitalWrite(led, LOW);//signal end of calibration

    delay(1000);
  
  

}

void loop() {

   sensorValue = analogRead(sensor);
  sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 255); //apply calibration to sensor         map(value, fromLow, fromHigh, toLow, toHigh)
  sensorValue = constrain(sensorValue, 0, 255); //in case range is outside 0-255

  int reading = sensorValue; //take data from light sensor

  int threshold = 125;
 
  
  if(digitalRead(button) == HIGH){
    digitalWrite(laser,HIGH);
  }
  else{
     digitalWrite(laser,LOW);
    }


  if(reading > threshold){
    digitalWrite(led, HIGH);
    }
  else{(digitalWrite(led,LOW));
  }
}
