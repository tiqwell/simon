const int LED_PINS[] = {6, 8, 10, 12};
const int BUTTON_PINS[] = {5, 7, 9, 11};

int sequence[100];
int sequenceLength = 0;

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], LOW);
  }
  
  for (int i = 0; i < 4; i++) {
    pinMode(BUTTON_PINS[i], INPUT_PULLUP);
  }

  randomSeed(analogRead(0));
  generateSequence();
}

void loop() {
  playSequence();

  for (int i = 0; i < sequenceLength; i++) {
    int buttonPressed = waitForButtonPress();
    if (buttonPressed != sequence[i]) {
      gameOver();
      generateSequence();
      return;
    }
  }

  displaySuccess();
  generateSequence();
}

void generateSequence() {
  sequenceLength = 0;
  for (int i = 0; i < 4; i++) {
    sequence[i] = random(4);
    sequenceLength++;
    delay(500);
  }
}

void playSequence() {
  for (int i = 0; i < sequenceLength; i++) {
    digitalWrite(LED_PINS[sequence[i]], HIGH);
    delay(500);
    digitalWrite(LED_PINS[sequence[i]], LOW);
    delay(500);
  }
}

int waitForButtonPress() {
  int buttonPressed = -1;
  while (buttonPressed == -1) {
    for (int i = 0; i < 4; i++) {
      if (digitalRead(BUTTON_PINS[i]) == LOW) {
        buttonPressed = i;
        delay(200);
        break;
      }
    }
  }
  return buttonPressed;
}

void displaySuccess() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(LED_PINS[i], HIGH);
  }
  delay(1000);
  for (int i = 0; i < 4; i++) {
    digitalWrite(LED_PINS[i], LOW);
  }
}

void gameOver() {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      digitalWrite(LED_PINS[j], HIGH);
    }
    delay(500);
    for (int j = 0; j < 4; j++) {
      digitalWrite(LED_PINS[j], LOW);
    }
    delay(500);
  }
}
