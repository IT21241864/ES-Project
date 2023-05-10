#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "~yuw~";
const char* password = "it123456";

ESP8266WebServer server(80); //initializing web server

//Web interface
void handleRoot() {  
  server.send(200, "text/html", "<center><h1>Hello from ESP8266!</h1><p><a href=\"/open\"><button>Open Lid</button></a> <br> <br> <a href=\"/close\"><button>Close Lid</button></a></p> <br> <br> <a href=\"/auto\"><button>Auto Mode</button></a></p></center>");
}

void handleOpen() {
  Serial.write('1');
  server.send(200, "text/html", "<center><h1>Smart Pet Feeder</h1><p><a href=\"/open\"><button>Open Lid</button></a> <br> <br> <a href=\"/close\"><button>Close Lid</button></a></p> <br> <br> <a href=\"/auto\"><button>Auto Mode</button></a></p></center>");
}

void handleClose() {
  Serial.write('0');
  server.send(200, "text/html", "<center><h1>Smart Pet Feeder</h1><p><a href=\"/open\"><button>Open Lid</button></a> <br> <br> <a href=\"/close\"><button>Close Lid</button></a></p> <br> <br> <a href=\"/auto\"><button>Auto Mode</button></a></p></center>");
}

void handleAuto() {
  Serial.write('2');
  server.send(200, "text/html", "<center><h1>Smart Pet Feeder</h1><p><a href=\"/open\"><button>Open Lid</button></a> <br> <br> <a href=\"/close\"><button>Close Lid</button></a></p> <br> <br> <a href=\"/auto\"><button>Auto Mode</button></a></p></center>");
}

void setup() {
  Serial.begin(9600); //serial communication baud rate

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/open", handleOpen);
  server.on("/close", handleClose);
  server.on("/auto", handleAuto);

  server.begin(); //begin serial communication
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient(); //start the server
}