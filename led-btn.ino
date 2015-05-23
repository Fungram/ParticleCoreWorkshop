// led-btn.ino
// Copyright Fungram LLC, 2015.

// Setup D0 as input and D1 as output
int btn_p = D0;
int led_p = D1;
// Initialize the serial communication for console messages.
void setup() {
    pinMode(btn_p, INPUT);
    pinMode(led_p, OUTPUT);
    Serial.begin(115200);
}

void loop() {
  // Read the button state on D1
  int buttonState = digitalRead(btn_p);
  // If the button is depressed, the logic
  // input will be HIGH. Keep the LED blinking.
  if (buttonState == HIGH) {
    Serial.println("Button active (depressed)!");
    Serial.println("Turning LED ON!");
    digitalWrite(led_p, HIGH);
    delay(1000);
    Serial.println("Turning LED OFF!");
    digitalWrite(led_p, LOW);
    delay(1000);
  } else {
    // When the button is not depressed, the D1 input is LOW.
    // Keep the LED off while this happens.
    Serial.println("Button not active (not depressed)!");
    Serial.println("LED is OFF!");
    delay(1000);
  }
}