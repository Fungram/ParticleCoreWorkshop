// led.ino
// Copyright Fungram LLC, 2015.

// Setup D7 as output
int led_p = D7;
// Initialize the serial communication for console messages.
void setup() {
    pinMode(led_p, OUTPUT);
    Serial.begin(115200);
}

void loop() {
    Serial.println("Turning LED ON!");
    digitalWrite(led_p, HIGH);
    delay(1000);
    Serial.println("Turning LED OFF!");
    digitalWrite(led_p, LOW);
    delay(1000);
}