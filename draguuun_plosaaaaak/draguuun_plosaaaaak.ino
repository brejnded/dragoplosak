/*buttons:
LB -> speed up LED sequence (DIP 1 active)
RB -> slow down LED sequence (DIP 1 active)

dip switches:
1 -> gradual LED sequence (controlled by buttons)
2 -> buzzer Star Wars theme song
3 -> all led fade effect
*/

#define RED_PIN 11
#define GREEN_PIN 10
#define BLUE_PIN 9
#define LED1 8
#define LED2 7
#define LED3 6
#define LED4 5
#define LED5 4
#define LED6 A1
#define LED7 A2
#define LED8 A3

const int ledPins[] = {LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8};
const int buttonPin1 = 2;
const int buttonPin2 = 3;
const int dipSwitchPin1 = A0;
const int dipSwitchPin2 = A6;
const int dipSwitchPin3 = A7;

int binaryCounter = 0;
int sequenceDelay = 50; // Initial delay between LED toggles (adjust for speed)
int bellPin = 12;

#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_B4 494

const int colors[][3] = {
    {255, 0, 0},  // Red
    {255, 165, 0}, // Orange
    {255, 255, 0}, // Yellow
    {0, 255, 0},   // Green
    {0, 255, 255}, // Cyan
    {0, 0, 255},   // Blue
    {128, 0, 128}, // Purple
    {255, 0, 255}  // Pink
};

void setup() {
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);
    for (int i = 0; i < 8; i++) {
        pinMode(ledPins[i], OUTPUT);
    }
    pinMode(bellPin, OUTPUT);

    pinMode(buttonPin1, INPUT_PULLUP);
    pinMode(buttonPin2, INPUT_PULLUP);

    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(BLUE_PIN, HIGH);
    for (int i = 0; i < 8; i++) {
        digitalWrite(ledPins[i], LOW);
    }
    digitalWrite(bellPin, HIGH);
}

void loop() {
    int switchState1 = analogRead(dipSwitchPin1);
    int switchState2 = analogRead(dipSwitchPin2);
    int switchState3 = analogRead(dipSwitchPin3);

    if (switchState1 < 500) { // Gradual LED sequence on DIP 1 press
        sequenceLoop();
    } else if (switchState2 < 500) { // Play Star Wars theme (DIP switch 2)
        playPiratesTheme();
    } else if (switchState3 < 500) { // Fade effect for all LEDs (DIP switch 3)
        fadingRainbow();
    }

    if (digitalRead(buttonPin1) == LOW && sequenceDelay > 10) { // Speed up button
        sequenceDelay -= 5; // Adjust speed increment as desired
    }

    if (digitalRead(buttonPin2) == LOW) { // Slow down button
        sequenceDelay += 10; // Adjust speed decrement as desired
    }
}
void playPiratesTheme() {
  // Pirates of the Caribbean theme (simplified version)

  // Introduction
  tone(bellPin, NOTE_D4, 250);
  delay(250);
  tone(bellPin, NOTE_E4, 250);
  delay(250);
  tone(bellPin, NOTE_F4, 250);
  delay(250);
  tone(bellPin, NOTE_E4, 250);
  delay(250);
  tone(bellPin, NOTE_D4, 250);
  delay(250);
  tone(bellPin, NOTE_C4, 500);
  delay(500);

  // Main melody
  tone(bellPin, NOTE_E4, 250);
  delay(250);
  tone(bellPin, NOTE_D4, 250);
  delay(250);
  tone(bellPin, NOTE_C4, 250);
  delay(250);
  tone(bellPin, NOTE_B4, 500);
  delay(500);

  tone(bellPin, NOTE_D4, 250);
  delay(250);
  tone(bellPin, NOTE_C4, 250);
  delay(250);
  tone(bellPin, NOTE_B4, 500);
  delay(500);
  tone(bellPin, NOTE_A4, 500);
  delay(500);

  tone(bellPin, NOTE_E4, 250);
  delay(250);
  tone(bellPin, NOTE_D4, 250);
  delay(250);
  tone(bellPin, NOTE_C4, 250);
  delay(250);
  tone(bellPin, NOTE_B4, 500);
  delay(500);

  // Repeat main melody
  tone(bellPin, NOTE_D4, 250);
  delay(250);
  tone(bellPin, NOTE_C4, 250);
  delay(250);
  tone(bellPin, NOTE_B4, 500);
  delay(500);
  tone(bellPin, NOTE_A4, 500);
  delay(500);

  tone(bellPin, NOTE_E4, 250);
  delay(250);
  tone(bellPin, NOTE_D4, 250);
  delay(250);
  tone(bellPin, NOTE_C4, 250);
  delay(250);
  tone(bellPin, NOTE_B4, 500);
  delay(500);

  // Outro
  tone(bellPin, NOTE_C4, 250);
  delay(250);
  tone(bellPin, NOTE_D4, 250);
  delay(250);
  tone(bellPin,  NOTE_E4, 250);
  delay(250);
  tone(bellPin,  NOTE_F4, 500);
  delay(500);
}

void sequenceLoop() {
  for (int i = 0; i < 8; i++) { // Forward sequence
    digitalWrite(ledPins[i], HIGH);
    delay(sequenceDelay);
    digitalWrite(ledPins[i], LOW);
  }

  // Optional short delay before reversing
  delay(sequenceDelay * 2);

  for (int i = 7; i >= 0; i--) { // Reverse sequence
    digitalWrite(ledPins[i], HIGH);
    delay(sequenceDelay);
    digitalWrite(ledPins[i], LOW);
  }
}

  void ledon() { // Turn on all LEDs
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
    for (int i = 0; i < 8; i++) {
        digitalWrite(ledPins[i], LOW);
    }
    delay(1000);
}

void ledoff() { // Turn off all LEDs
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(BLUE_PIN, HIGH);
    for (int i = 0; i < 8; i++) {
        digitalWrite(ledPins[i], HIGH);
    }
    delay(1000);
}

void fadingRainbow() { // Fading rainbow effect for all LEDs
    for (int i = 0; i < sizeof(colors) / sizeof(colors[0]); i++) {
        int nextColorIndex = (i + 1) % (sizeof(colors) / sizeof(colors[0]));

        for (int j = 0; j <= 255; j += 5) {
            analogWrite(RED_PIN, colors[i][0] + (colors[nextColorIndex][0] - colors[i][0]) * j / 255);
            analogWrite(GREEN_PIN, colors[i][1] + (colors[nextColorIndex][1] - colors[i][1]) * j / 255);
            analogWrite(BLUE_PIN, colors[i][2] + (colors[nextColorIndex][2] - colors[i][2]) * j / 255);
            delay(15);
        }
    }
}