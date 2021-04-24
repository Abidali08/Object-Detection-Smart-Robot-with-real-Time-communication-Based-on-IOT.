#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
ESP8266WebServer server(80);

//const char* ssid = "AbidAliHunzai"; //Enter Wi-Fi SSID
//const char* password =  "34616458"; //Enter Wi-Fi
const char* ssid = "UODSRS"; //Enter Wi-Fi SSID
const char* password =  "123456789"; //Enter Wi-Fi

String serialData = "";
String page = "";
//String data = "";

//Enter the static ip that you want to set
IPAddress ip(192, 168, 1, 195);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

void setup() {
  Serial.begin(9600);

  //Configuring the WI-FI with the specified static IP.
  WiFi.config(ip, gateway, subnet);

  connectWiFi();

  server.on("/data.txt", []() {
    server.send(200, "text/html", serialData);
  });

  server.on("/", []() {
    page = "<h1 style=\"color:red;\">Obstacle Alert</h1> <h1 id=\"data\">""</h1>\r\n";
    page += "<script>\r\n";
    page += "var x = setInterval(function() {loadData(\"data.txt\",updateData)}, 1000);\r\n";
    page += "function loadData(url, callback){\r\n";
    page += "var xhttp = new XMLHttpRequest();\r\n";
    page += "xhttp.onreadystatechange = function(){\r\n";
    page += " if(this.readyState == 4 && this.status == 200){\r\n";
    page += " callback.apply(xhttp);\r\n";
    page += " }\r\n";
    page += "};\r\n";
    page += "xhttp.open(\"GET\", url, true);\r\n";
    page += "xhttp.send();\r\n";
    page += "}\r\n";
    page += "function updateData(){\r\n";
    page += " document.getElementById(\"data\").innerHTML = this.responseText;\r\n";
    page += "}\r\n";
    page += "</script>\r\n";
    server.send(200, "text/html", page);
  });

  server.on("/automatic", HTTP_GET, Auto);
  server.on("/manual", HTTP_GET, Manual);
  server.on("/forward", HTTP_GET, MotorForward);
  server.on("/backward", HTTP_GET, MotorBackward);
  server.on("/left", HTTP_GET, TurnLeft);
  server.on("/right", HTTP_GET, TurnRight);
  server.on("/stop", HTTP_GET, MotorStop);

  server.begin();
}
void loop() {
  server.handleClient();

  if (Serial.available())
    serialData = Serial.readString();
}

void connectWiFi()
{
  WiFi.begin(ssid, password);
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    delay(300);
  }
  delay(5000);
}

/********************************************* BACKWARD *****************************************************/
void MotorBackward(void)
{
  Serial.write("b");
}

/********************************************* TURN LEFT *****************************************************/
void TurnLeft(void)
{
  Serial.write("l");
}

/********************************************* TURN RIGHT *****************************************************/
void TurnRight(void)
{
  Serial.write("r");
}

/********************************************* FORWARD *****************************************************/
void MotorForward(void)
{
  Serial.write("f");
}

/********************************************* STOP *****************************************************/
void MotorStop(void)
{
  Serial.write("s");
}

void Auto(void)
{
  Serial.write("a");
  server.send(200, "text/plain", "OK");
}

void Manual(void)
{
  Serial.write("m");
}
