#include <ESP8266WiFi.h>
int gpio_num;
const char* ssid = "12345678";
const char* password = "12345678";
  String s;
WiFiServer server(80);
void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(2, OUTPUT); 
  digitalWrite(2, 0);
  
  pinMode(0, OUTPUT);
  digitalWrite(0, 0);
    
  pinMode(5, OUTPUT);
  digitalWrite(5, 0); 
   
  pinMode(16, OUTPUT);
  digitalWrite(16, 0);  
  
  pinMode(4, OUTPUT);
  digitalWrite(4, 0);
  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  int val;
  if (req.indexOf("/gpio2/0") != -1){
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n<h1>CONNECTED<br> gpio2 off </h1><br><h6>from esp 8255";
    val = 0;
    gpio_num=2;
  }
  else if (req.indexOf("/gpio2/1") != -1){
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n<h1>CONNECTED<br> gpio2 on </h1><br><h6>from esp 8255";
    val = 1;
    gpio_num=2;
  }

 else if (req.indexOf("/gpio0/1") != -1){
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n<h1>CONNECTED<br> gpio0 on </h1><br><h6>from esp 8255";
    val = 1;
    gpio_num=0;
  }
 else if (req.indexOf("/gpio0/0") != -1){
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n<h1>CONNECTED<br> gpio0 off </h1><br><h6>from esp 8255";
    val = 0;
    gpio_num=0;
  }
 else if (req.indexOf("/gpio16/1") != -1){
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n<h1>CONNECTED<br> gpio16 on </h1><br><h6>from esp 8255";
    val = 1;
    gpio_num=16;
  }
 else if (req.indexOf("/gpio16/0") != -1){
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n<h1>CONNECTED<br> gpio16 off </h1><br><h6>from esp 8255";
    val = 0;
    gpio_num=16;
  }
 else if (req.indexOf("/gpio5/1") != -1){
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n<h1>CONNECTED<br> gpio5 on </h1><br><h6>from esp 8255";
    val = 1;
    gpio_num=5;
  }
 else if (req.indexOf("/gpio5/0") != -1){
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n<h1>CONNECTED<br> gpio5 off </h1><br><h6>from esp 8255";
    val = 0;
    gpio_num=5;
  }
 else if (req.indexOf("/gpio4/1") != -1){
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n<h1>CONNECTED<br> gpio4 on </h1><br><h6>from esp 8255";
    val = 1;
    gpio_num=4;
  }
 else if (req.indexOf("/gpio4/0") != -1){
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n<h1>CONNECTED<br> gpio4 off </h1><br><h6>from esp 8255";
    val = 0;
    gpio_num=4;
  }
  else{
    Serial.println("invalid request");
    client.stop();
    return;
  }

  digitalWrite(gpio_num, val);

  client.flush();
  
// s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n<h1>CONNECTED</h1><br><h6>from esp 8255";
//  s += (val)?"high":"low";
//  s += "<br><a href=\"/gpio2/0\">turn off gpio2</a>";
//  s+="<br><a href=\"/gpio2/1\">turn on gpio2</a><br>";
//  s+="<a href=\"/gpio0/0\">turn off gpio0</a><br><a href=\"/gpio0/1\">turn on gpio0</a></html>\n";
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");
}
