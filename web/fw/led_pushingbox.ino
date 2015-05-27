// Copyright Fungram LLC, 2015.

// Your secret DevID from PushingBox.com. 
// You can use multiple DevID  on multiple Pin if you want
const char * DEVID1 = "vFFCCD4BBADE09AB";         
const char * serverName = "api.pushingbox.com"; 

TCPClient client;


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
  sendToPushingBox(DEVID1);
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
// Function to send a mesage to pushing box server
// This message is a simple http request. 
// note that there is no encryption for this message
// pay attention to that when going to production

void sendToPushingBox(const char * devid)
{
  Serial.print("closing... ");
  client.stop();
  Serial.print("connecting... ");
  if (client.connect(serverName, 80)) {
    Serial.println("connected");
    client.print("GET /pushingbox?devid=");
    client.print(devid);
    // Arguments that can be used in 
    // pushingbox messages. 
    client.print("&lightState=");
    client.print(ledState);


    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(serverName);
    client.println("User-Agent: Spark");
    //client.println("Connection: close");
    client.println();
    client.flush();
    while (!client.available()) SPARK_WLAN_Loop();
    while (client.available()) {
      char c = client.read();
      Serial.print(c);
    }
    Serial.println();
    delay(150);
    while(client.available()) client.read();
    Serial.println();
  }
}