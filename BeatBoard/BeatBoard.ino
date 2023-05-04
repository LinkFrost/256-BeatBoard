#define BUTTON_ONE 13
#define LED 12
#define BUZZER_ONE 15

void setup() {
  Serial.begin(9600);
  // initialize the piezo as output:
  pinMode(BUZZER_ONE, OUTPUT);  
  // initialize the pushbutton pin as an input:
  pinMode(BUTTON_ONE, INPUT_PULLUP);
  // initialize the led pin as an output:
  pinMode(LED, OUTPUT);
}
unsigned long debounceTime = 200;

unsigned long lastDebounceTime = 0;
unsigned long lastDebounceTime2 = 0;
void loop(){
  // read the state of the pushbutton value:
  if(millis() - lastDebounceTime > debounceTime && digitalRead(BUTTON_ONE) == 1) {
    digitalWrite(LED, HIGH);
    tone(BUZZER_ONE,400,200);
    delay(500);
  } else if (digitalRead(BUTTON_ONE) == 0) {
    digitalWrite(LED, LOW);
    tone(BUZZER_ONE, 0);
  }
}