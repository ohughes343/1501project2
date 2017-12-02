const int deathTimer = 2000;
int timeOfDeath = 0;
int currentTime = 0;
int buttonState;
const int led1 = 12;
const int led2 = 8;
const int led3 = 7;
const int button = A0;

int lives = 3;

bool readyfctn(int a);

void setup() {
  pinMode(button, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
}

void loop() {
  while(lives > 0){
    if(timeOfDeath==0||(timeOfDeath + 2000 <= millis())){
      buttonState = digitalRead(button);
      if(buttonState == 1){
        lives--;
        timeOfDeath = millis();
      }
    }
    if(lives == 2){
      digitalWrite(led1, LOW);
    }
    if(lives == 1){
      digitalWrite(led2, LOW);
    }
    if(lives == 0){
      digitalWrite(led3, LOW);
    }
  }
}

/*
bool readyfctn(int a){
  currentTime = millis();
  if(currentTime - a > timeOfDeath){
    return true;
  }else{
    return false;
  }
}
*/

