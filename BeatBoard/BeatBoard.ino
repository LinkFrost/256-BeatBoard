#define BUTTON 13
#define BUZZER 15

void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);
}

unsigned long debounceTime = 200;
unsigned long lastDebounceTime = 0;

void loop() {
  // put your main code here, to run repeatedly:
  if(millis() - lastDebounceTime > debounceTime && digitalRead(BUTTON) == 0) {
      // Serial.println("HERE");
      tone(BUZZER, 698, 500);
      // digitalWrite(BUZZER, HIGH);
      lastDebounceTime = millis();
    }

    // if(digitalRead(BUTTON) == LOW) {
    //   digitalWrite(BUZZER, LOW);
    // }
  

  // noTone(BUZZER);
}
