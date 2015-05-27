// led-btn.ino
// Copyright Fungram LLC, 2015.

// The LED/Pushbutton pins
int btn_p = D0;
int led_p = D1;

// Setup
void setup() {
    // Setup D0 as input and D1 as output
    pinMode(btn_p, INPUT);
    pinMode(led_p, OUTPUT);
    // Initialize the serial communication for console messages.
    Serial.begin(115200);
}

// Forever loop
void loop() {
  // Read the button state on D0
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