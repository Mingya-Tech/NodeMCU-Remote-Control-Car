/*
 *  
 */

#include <ESP8266WiFi.h>

const char* ssid = "wifi-ssid";
const char* password = "wifi-pswd";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Match the request
  if (req.indexOf("/ahead") != -1) {
    move_ahead();
  }
  else if (req.indexOf("/back") != -1) {
    move_back();
  }
  else if (req.indexOf("/left") != -1) {
    turn_left();
  }
  else if (req.indexOf("/right") != -1) {
    turn_right();
  }
  else if (req.indexOf("/stop") != -1) {
    stop_motor();
  }

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
  String res = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE html><html><style>body{text-align:center;}table{margin:auto;}button{width:160px;height:160px;}</style><script>function move(direction){console.log(direction);var xmlhttp=new XMLHttpRequest();xmlhttp.open(\"GET\",\"/\"+direction,true);xmlhttp.send();}</script><h3>NodeMCU Car Controller</h1><table><tr><td>1</td><td><button onclick=\"move(\'ahead\')\">up</button></td><td>3</td></tr><tr><td><button onclick=\"move(\'left\')\">left</button></td><td><button onclick=\"move(\'stop\')\">stop</button></td><td><button onclick=\"move(\'right\')\">right</button></td></tr><tr><td>7</td><td><button onclick=\"move(\'back\')\">down</button></td><td>9</td></tr></table></html>";
  client.print(res);
  delay(1);
  Serial.println("Client disonnected");
}

void move_ahead() {
  Serial.println("moving ahead...");
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
}

void move_back() {
  Serial.println("moving back...");
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
}

void turn_right() {
  Serial.println("turning right...");
  digitalWrite(D1, HIGH);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
}

void turn_left() {
  Serial.println("turning left...");
  digitalWrite(D1, LOW);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
}

void stop_motor() {
  Serial.println("Stopping...");
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
}
