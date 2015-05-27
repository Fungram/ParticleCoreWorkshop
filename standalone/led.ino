// led.ino
// Copyright Fungram LLC, 2015.

// The LED pin
int led_p = D7;

// Setup
void setup() {
    // Setup D7 as output
    pinMode(led_p, OUTPUT);

    // Initialize the serial communication for console messages.
    Serial.begin(115200);
}

// The forever loop
void loop() {
    // Let us log some messages about what we are going to do
    Serial.println("Turning LED ON!");

    // Turn the LED on
    digitalWrite(led_p, HIGH);

    // Wait for 1 sec
    delay(1000);

    // More log messages
    Serial.println("Turning LED OFF!");

    // Turn the LED off
    digitalWrite(led_p, LOW);

    // Another 1 sec delay
    delay(1000);
}