// Copyright Fungram LLC, 2015.
// Setup D1 as output
int led_p = D1;

// Current State of LED
int ledState = TRUE;

// Function to toggle the state of the LED
// Does not use any arguments in the current implementation
// 
int toggleLight(String args)
{
  ledState = ledState==TRUE?FALSE:TRUE;
  if(ledState)
  {
    digitalWrite(led_p, HIGH);
  }
  else
  {
    digitalWrite(led_p, LOW);
  }
  return ledState;
}


void setup() {
  pinMode(led_p, OUTPUT);
  // Initialize the serial communication for console messages.
  Serial.begin(115200);
  
  Spark.variable("lights", &ledState, INT);
  Spark.function("toggleLight", toggleLight);

  digitalWrite(led_p, HIGH);
  ledState = TRUE;

}

void loop() {

}