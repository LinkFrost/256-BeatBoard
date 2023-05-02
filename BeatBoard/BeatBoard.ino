#define BUTTON_ONE 13
#define BUTTON_TWO 14
#define BUZZER_ONE 15
#define BUZZER_TWO 12

void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTON_ONE, INPUT_PULLUP);
  pinMode(BUTTON_TWO, INPUT_PULLUP);
  pinMode(BUZZER_ONE, OUTPUT);
  pinMode(BUZZER_TWO, OUTPUT);

  Serial.begin(9600);
}

unsigned long debounceTime = 200;

unsigned long lastDebounceTime = 0;
unsigned long lastDebounceTime2 = 0;

void loop() {
  // put your main code here, to run repeatedly:
  if(millis() - lastDebounceTime > debounceTime && digitalRead(BUTTON_ONE) == 0) {
    tone(BUZZER_ONE, 698);
    lastDebounceTime = millis();
  } else if (digitalRead(BUTTON_ONE) == 1) {
    tone(BUZZER_ONE, 0);
  }

  // if(millis() - lastDebounceTime2 > debounceTime && digitalRead(BUTTON_TWO) == 0) {
  //   tone(BUZZER_TWO, 1975);
  //   lastDebounceTime2 = millis();
  // } else if (digitalRead(BUTTON_TWO) == 1) {
  //   tone(BUZZER_TWO, 0);
  // }
}
