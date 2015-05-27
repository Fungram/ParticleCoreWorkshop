// led-btn-ldr.ino
// Copyright Fungram LLC, 2015.

int btn_p = D0;
int led_p = D1;
int ldr_p = A0;
// Initialize the serial communication for console messages.
void setup() {
    // Setup D0 (Pushbutton) as input and D1 (LED) as output
    // Setup A0 (Light Dependent Resistor) as input
    pinMode(ldr_p, INPUT);
    pinMode(btn_p, INPUT);
    pinMode(led_p, OUTPUT);
    Serial.begin(115200);
}

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
    // When the button is not depressed, the D0 input is LOW.
    // Keep the LED off while this happens.
    Serial.println("Button not active (not depressed)!");
    Serial.println("LED is OFF!");
    
    // Let us read the resitor value reported by the LDR (photo resistor)
    int ldr_val = analogRead(ldr_p);
    Serial.print("Photo resistor reading: ");
    Serial.println(ldr_val);
    
    // Depending on the LDR value read, turn the LED on with the appropriate
    // brightness.
    int led_bri_val = 255 - (ldr_val * 255)/ 4095;
    Serial.print("Setting LED brightness to: ");
    Serial.println(led_bri_val);

    // Even though the LED is conected to a digital (D1) pin, an analogWrite
    // will activate the PWM circuit on that pin to create a lower voltage
    // output to control the LED brightness.
    analogWrite(led_p, led_bri_val);
    delay(1000);
  }
}