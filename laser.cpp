const int laser = 3;
const int button = 7;
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
  pinMode(laser, OUTPUT);
  pinMode(button, INPUT);
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

  int threshold = 125;
 
  if(digitalRead(button) == HIGH){  //if button is pressed
    timeNow = millis();
    timeSince = timeNow - timeOf; // time since last shot = now - last shot
    if(timeSince >= 2000){ //if 2 seconds since last fire
      fire(true); //call fctn fire with successful param 
    }
    else{
      fire(false); //call ftcn w/ fail param
    }
  }
  else{
     digitalWrite(laser, LOW);
    }
    
  if(reading > threshold){
    //Oh no you got 
    hit();
    }
  else{
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }
}

void fire(bool a){
  if(a == true){
    //make noise of shooting
    tone(speaker,400,300);
    digitalWrite(laser, HIGH);
    delay(300);
    digitalWrite(laser, LOW);
    timeOf = millis();
  }
  else{
    //Make sad noise
    tone(speaker, 123, 1230);
    //tone(speaker, 100, 1230);
    //tone(speaker, 80, 1230);
    digitalWrite(led1, HIGH);
    delay(500);
    digitalWrite(led1, LOW);
    
  }
}

void hit(){
  //play sad music
  for(int i = 0; i < 10; i++){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    delay(100);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    delay(100);
  }
}
