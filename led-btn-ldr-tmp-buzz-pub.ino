// led-btn-ldr-tmp-buzz-pub.ino
// Copyright Fungram LLC, 2015.

// Setup D0 as input and D1 as output
// Setup D7 as an input (jumper)
int btn_p   = D0;
int led_p   = D1;
int buzz_p  = D2;
int ldr_p   = A0;
int tmp_p   = A7;
int jmpr_p  = D7;

int i = 0;

void eventHandler(const char *event, const char *data)
{
  i++;
  Serial.print(i);
  Serial.print(". ");
  Serial.print(event);
  Serial.print(" --> data: ");
  if (data)
    Serial.println(data);
  else
    Serial.println("NULL");
}

// Initialize the serial communication for console messages.
void setup() {
  // Setup input/output pins
  pinMode(tmp_p,   INPUT);
  pinMode(ldr_p,   INPUT);
  pinMode(btn_p,   INPUT);
  pinMode(led_p,   OUTPUT);
  pinMode(buzz_p,  OUTPUT);
  pinMode(jmpr_p,  INPUT);
  // Serial setup
  Serial.begin(115200);

  // Subscribe for LED status announcements  
  Spark.subscribe("LED", eventHandler);
}

// Function to blink the LED
void blink_led(int blink_dur) {
  Serial.print("Blinking the LED with blink duration (msec): ");
  Serial.println(blink_dur);
  digitalWrite(led_p, HIGH);
  delay(blink_dur);
  digitalWrite(led_p, LOW);
  delay(blink_dur);
}

// Function to blink the buzzer
void beep_buzzer(int beep_dur) {
  Serial.print("Make the buzzer beep with beep duration (msec): ");
  Serial.println(beep_dur);
  digitalWrite(buzz_p, HIGH);
  delay(beep_dur);
  digitalWrite(buzz_p, LOW);
  delay(beep_dur);
}

void loop() {
  // Read the button state on D1
  int buttonState = digitalRead(btn_p);
  // If the button is depressed, the logic
  // input will be HIGH. Keep the LED blinking.
  if (buttonState == HIGH) {
    Serial.println("Button active (depressed)!");
    blink_led(1000);
  } else {
    // When the button is not depressed, the D1 input is LOW.
    // Keep the LED off while this happens.
    Serial.println("Button not active (not depressed)!");
    
    // Control the LED brightness only if D7 is HIGH
    if (digitalRead(jmpr_p) == HIGH)
    {
      // Let us read the resitor value reported by the LDR (photo resistor)
      int ldr_val = analogRead(ldr_p);
      Serial.print("Photo resistor reading: ");
      Serial.println(ldr_val);
    
      // Depending on the LDR value read, turn the LED on with the appropriate
      // brightness.
      int led_bri_val = 255 - (ldr_val * 255)/ 4095;
      Serial.print("Setting LED brightness to: ");
      Serial.println(led_bri_val);
      analogWrite(led_p, led_bri_val);

      // Delay the loop for 1 sec
      delay(1000);
    } else { // Control the LED based on the temperature
      // Read in the temperature value
      uint16_t tmp_reading = analogRead(tmp_p);
      Serial.print("Temperature reading: ");
      Serial.println(tmp_reading);
      double voltage     = (tmp_reading * 3.3) / 4096;
      double temperature = (voltage - 0.5) * 100;
      Serial.print("Ambient temperature is: ");
      Serial.println(temperature);
      
      // Assume LED blinks at the rate of 1 per sec (1 sec ON, 1 sec OFF) at 20 deg C
      // Change the blink rate (slow if colder, fast if hotter) by 50 msec for each deg C change
      int blink_duration = 1000 - 50 * round(temperature - 20);
      if (blink_duration >= 0) {
        blink_led(blink_duration);
        if (temperature > 26) {
          beep_buzzer(blink_duration);
          Spark.publish("LO-TMP-WARNING", "26 deg C");
        }
      } else {
        // Leave the LED ON and delay for half a second before looping around
        digitalWrite(led_p, HIGH);
        digitalWrite(buzz_p, HIGH);
        Spark.publish("HI-TMP-WARNING", "40 deg C");
        delay(1000);
      }
    }
  }
}