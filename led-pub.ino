// led-pub.ino
// Copyright Fungram LLC, 2015.

// Setup D7 as output
int led_p = D7;

int i = 0;

void eventHandler(const char *event, const char *data)
{
  i++;
  Serial.print(i);
  Serial.print(". ");
  Serial.print(event);
  Serial.print("--> data: ");
  if (data)
    Serial.println(data);
  else
    Serial.println("NULL");
}

// Initialize the serial communication for console messages.
void setup() {
    pinMode(led_p, OUTPUT);
    Serial.begin(115200);

    Spark.subscribe("LO-TMP-WARNING", eventHandler);
    Spark.subscribe("HI-TMP-WARNING", eventHandler);
}

void loop() {
    Serial.println("Turning LED ON!");
    digitalWrite(led_p, HIGH);
    Spark.publish("LED-ON-STATUS");
    delay(1000);
    Serial.println("Turning LED OFF!");
    digitalWrite(led_p, LOW);
    Spark.publish("LED-OFF-STATUS");
    delay(1000);
}