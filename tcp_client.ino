
#include <SPI.h>
#include <WiFi101.h>

char ssid[] = "YOUR_SSID";
char pass[] = "YOUR_PASSWORD";

int status = WL_IDLE_STATUS;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to WiFi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // you're connected now, so print out the data:
  Serial.print("You're connected to the network");
  printWiFiData();
  connectToTCPServer();

}

void loop() {
  sendMessage("Hola soy Arduino");
  delay(10000);
  readMessagesFromServer();
  checkClientConnection();
}

void printWiFiData() 
{
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}


WiFiClient client;
IPAddress server(130,61,99,169);
bool isConnected = false;

void connectToTCPServer()
{
  while(!isConnected) {
    if (client.connect(server, 10000)) {
        Serial.println("connected");
        isConnected = true;
    }
  }
}

void sendMessage(String str)
{
  if(isConnected)
  {
     unsigned int strLength = str.length() + 1;
     char msg[strLength]; 
     str.toCharArray(msg, strLength);
     msg[strLength] = '\0';
     client.write(msg, strLength);
     Serial.println("\nMessage sent: " + str);
  }
}

void readMessagesFromServer()
{
  if(isConnected)
  {
    String response;
    while(client.available()) {
      char c = client.read();
     response += c;
    }

    Serial.println("Message recived: " + response);
  }
}

void checkClientConnection()
{
  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    for(;;)
      ;
  }
}
