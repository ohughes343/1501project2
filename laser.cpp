const int machine = 3;
const int missle = 4;
const int machinebutton = 6;
const int misslebutton = 7;
const int speaker = 8;
const int led1 = 9;
const int led2 = 10;
const int led3 = 11;
const int sensor = A0;

int threshold = 700;
int sensorMax = 0;
int sensorMin = 1023;
int sensorValue = 0;

int timeOf = 0;
int timeNow = 0;
int timeSince = 0;

//bool fire(bool a);
void hit();

void setup() {
  pinMode(machine, OUTPUT);
  pinMode(missle, OUTPUT);
  pinMode(machinebutton, INPUT);
  pinMode(misslebutton, INPUT);
  pinMode(speaker, OUTPUT);
  pinMode(sensor, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  digitalWrite(led1, HIGH);//turn on White to signal calibration period
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  while(millis() < 5000){
    sensorValue = analogRead(sensor); //calibrate during first five seconds
    if(sensorValue > sensorMax){
        sensorMax = sensorValue;
      }
    if(sensorValue < sensorMin){
        sensorMin = sensorValue;
      }
    }
    digitalWrite(led1, LOW);//signal end of calibration
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
}

void loop() {
  sensorValue = analogRead(sensor);
  sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 255); //apply calibration to sensor         map(value, fromLow, fromHigh, toLow, toHigh)
  sensorValue = constrain(sensorValue, 0, 255); //in case range is outside 0-255

  int reading = sensorValue; //take data from light sensor

  int threshold = 140;
 
  if(digitalRead(misslebutton) == HIGH){  //if missle button is pressed
    timeNow = millis();
    timeSince = timeNow - timeOf; // time since last shot = now - last shot
    if(timeSince >= 2000){ //if 2 seconds since last fire
      fireMissle(true); //call fctn fire with successful param 
    }
    else{
      fireMissle(false); //call ftcn w/ fail param
    }
  }
  else{
     digitalWrite(machine, LOW);
    }

  if(digitalRead(machinebutton) == HIGH){ //if machine gun is fired
     fireMachine(true);
  }
  else{
     fireMachine(false);
    }
    
  if(reading > threshold){
    //Oh no you got hit
    hit();
    }
  else{
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }
}

void fireMachine(bool a){
  if(a == true){
    //make noise of shooting
    tone(speaker,400,30);
    digitalWrite(machine, HIGH);
    delay(300);
    digitalWrite(machine, LOW);
    delay(300);
    
  }
  else{
    digitalWrite(machine, LOW);
    }
  
}

void fireMissle(bool a){
  if(a == true){
    tone(speaker, 100, 300);
    digitalWrite(missle, HIGH);
    delay(300);
    digitalWrite(missle, LOW);
    timeOf = millis();
    }
  else{
    //Make sad noise
    tone(speaker, 123, 1230);
    //tone(speaker, 100, 1230);
    //tone(speaker, 80, 1230);
    digitalWrite(led1, HIGH); //cooldown sequence for missle
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    delay(500);
    digitalWrite(led3, LOW);
    delay(500);
    digitalWrite(led2, LOW);
    delay(500);
    digitalWrite(led1, LOW);
  }
}

void hit(){
  //play sad music
  for(int i = 0; i < 10; i++){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    delay(100);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    delay(100);
  }
}
