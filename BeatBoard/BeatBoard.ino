#include <stdio.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>

#define buttonArray A13
#define BUZZER A5
#define playButton 0
#define recordButton 34
#define neoPixelRing 25

#define ringshow_noglitch() {delay(1);ring.show();delay(1);ring.show();}

#define C 523
#define C_S 554
#define D 587
#define D_S 622
#define E 659
#define F 698
#define F_S 740
#define G 784
#define G_S 831
#define A 880
#define A_S 932
#define B 988

Adafruit_SSD1306 lcd(128, 64);
Adafruit_NeoPixel ring = Adafruit_NeoPixel(16, neoPixelRing, NEO_GRB + NEO_KHZ800);

int pianoButtonValue = 0;
int recordingTime = 0;
int recordMode = 0;
int i = 0;

long previousRecordClickTime = 0;
long previousDebounceTime = 0;

struct recordedNoteObj {
  int note = 0;
  unsigned long timePlayed;
  bool flag = 0;
};

struct recordedNoteObj recording[500];
struct recordedNoteObj recordedNote;
struct recordedNoteObj emptyNote;

void playNote(int note) {
  tone(BUZZER, note, 100);
  delay(25);
}

void recordNote(int note) {
  if(recordMode == 1) {
    if(recordedNote.flag == 0) {
      recordingTime = millis();
    }

    if(emptyNote.flag == 1) {
      emptyNote.timePlayed = millis() - emptyNote.timePlayed;
      emptyNote.flag = 0;
      emptyNote.note = 0;
      
      addToRecording(emptyNote);
    }

    recordedNote.note = note;
    recordedNote.flag = 1;  
  }
}

void displayNote(int note) {
  lcd.clearDisplay();
  lcd.setCursor(0,0); 

  char printString[20] = "";

  int numPixels = 0;

  switch(note) {
    case C:
      numPixels = 1;
      sprintf(printString, "C: %d Hz", note);
      break;
    case C_S:
      numPixels = 3;
      sprintf(printString, "C#: %d Hz", note);
      break;
    case D:
      numPixels = 5;
      sprintf(printString, "D: %d Hz", note);
      break;
    case D_S:
      numPixels = 6;
      sprintf(printString, "D#: %d Hz", note);
      break;
    case E:
      numPixels = 7;
      sprintf(printString, "E: %d Hz", note);
      break;
    case F:
      numPixels = 8;
      sprintf(printString, "F: %d Hz", note);
      break;
    case F_S:
      numPixels = 9;
      sprintf(printString, "F#: %d Hz", note);
      break;
    case G:
      numPixels = 10;
      sprintf(printString, "G: %d Hz", note);
      break;
    case G_S:
      numPixels = 11;
      sprintf(printString, "G#: %d Hz", note);
      break;
    case A:
      numPixels = 12;
      sprintf(printString, "A: %d Hz", note);
      break;
    case A_S:
      numPixels = 14;
      sprintf(printString, "A#: %d Hz", note);
      break;
    case B:
      numPixels = 16;
      sprintf(printString, "B: %d Hz", note);
      break;
    case 0:
      numPixels = 0;
      sprintf(printString, "0 Hz");
  }

  lcd.print(printString);
  lcd.setCursor(0, 18);
  
  if(recordMode == 0) {
    sprintf(printString, "Record:Off");
  } else {
    sprintf(printString, "Record:On");    
  }

  lcd.print(printString);
  lcd.display(); 

  pixelNote(numPixels);  
}

void pixelNote(int numPixels) {
  if(numPixels == 0) {
    ring.clear();
    ringshow_noglitch();
    return;
  }

  for(int j = 0; j <= numPixels; j++) {
    ring.setPixelColor(j, 0x0000FF);
  }

  for(int j = numPixels + 1; j < ring.numPixels(); j++) {
    ring.setPixelColor(j, 0);
  }

  ringshow_noglitch();
}

void runNote(int note) {
  playNote(note);
  recordNote(note);
  displayNote(note);
}

void addToRecording(struct recordedNoteObj newNote){
  if(i == 500)
    return;

  struct recordedNoteObj copy;

  copy.note = newNote.note;
  copy.timePlayed = newNote.timePlayed;

  recording[i] = copy;

  i += 1;  
}

void playRecording() {
  for(int j = 1; j < 500; j++) {
    tone(BUZZER, recording[j].note, recording[j].timePlayed);
    displayNote(recording[j].note);
    delay(recording[j].timePlayed);
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(BUZZER, OUTPUT);
  pinMode(playButton, INPUT_PULLUP);
  pinMode(recordButton, INPUT_PULLUP);

  lcd.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  lcd.clearDisplay();
  lcd.setTextColor(WHITE);
  lcd.setTextSize(2);
  lcd.setCursor(0,0); 
  lcd.display(); 

  ring.begin();
  ring.setBrightness(32);
  ring.clear(); 
  ring.setPixelColor(0,0);
  ringshow_noglitch(); 
}

void loop() {
  Serial.print("recordMode: ");
  Serial.println(recordMode);

  if(digitalRead(recordButton) == 0 && (millis() - previousDebounceTime) > 25) {
    recordMode = 1 - recordMode;
    previousDebounceTime = millis();
  }

  pianoButtonValue = analogRead(buttonArray);  

  Serial.print("buttonValue: ");
  Serial.println(pianoButtonValue);

  delay(75);

  // Button 1
  if(pianoButtonValue >= 400 && pianoButtonValue <= 510) {
    runNote(C);
  }

  // Button 2
  if(pianoButtonValue >= 1180 && pianoButtonValue <= 1225) {
    runNote(C_S);
  }

  // Button 3
  if(pianoButtonValue >= 550 && pianoButtonValue <= 600) {
    runNote(D);
  }

  // Button 4
  if(pianoButtonValue >= 985 && pianoButtonValue <= 1015) {
    runNote(D_S);
  }

  // Button 5
  if(pianoButtonValue >= 685 && pianoButtonValue <= 715) {
    runNote(E);
  }

  // Button 6
  if(pianoButtonValue >= 630 && pianoButtonValue <= 655) {
    runNote(F);
  }

  // Button 7
  if(pianoButtonValue >= 915 && pianoButtonValue <= 945) {
    runNote(F_S);
  }

  // Button 8
  if(pianoButtonValue >= 820 && pianoButtonValue <= 845) {
    runNote(G);
  }

  // Button 9
  if(pianoButtonValue >= 2425 && pianoButtonValue <= 2465) {
    runNote(G_S);
  }

  // Button 10
  if(pianoButtonValue >= 1480 && pianoButtonValue <= 1510) {
    runNote(A);
  }

  // Button 11
  if(pianoButtonValue >= 2000 && pianoButtonValue <= 2040) {
    runNote(A_S);
  }

  // Button 12
  if(pianoButtonValue >= 1870 && pianoButtonValue <= 1900) {
    runNote(B);
  }

  if(pianoButtonValue == 0) {
    displayNote(0);

    if(recordedNote.flag != 0){
      recordedNote.timePlayed = millis() - recordingTime;
      addToRecording(recordedNote);
    }

    recordedNote.flag = 0;
    recordedNote.note = 0;

    if(emptyNote.flag == 0){
      emptyNote.flag = 1;
      emptyNote.timePlayed = millis();
    }

    recordingTime = millis();
  }

  if(digitalRead(playButton) == 0) {
    playRecording();
  }
}