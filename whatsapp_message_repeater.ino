#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <UrlEncode.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// +international_country_code + phone number
// Netherlands +316, example: +316912345678
String phoneNumber = "YOUR_NUMBER";
String apiKey = "YOUR_API_KEY";

int i = 1;


void sendMessage(String message) {

  // Data to send with HTTP POST
  String url = "http://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);
  WiFiClient client;
  HTTPClient http;
  http.begin(client, url);

  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  // Send HTTP POST request
  int httpResponseCode = http.POST(url);
  if (httpResponseCode == 200) {

  } else {
    Serial.println("Error sending the message");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }

  // Free resources
  http.end();
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  // i stand for the amount of messages to send
  while (i <= 5) {

    // Send Message to Whatsapp
    sendMessage("YOUR_MESSAGE");

    delay(7000);

    Serial.println("");
    Serial.print("Message ");
    Serial.print(i);
    Serial.println(" sent successfully");

    // Delay in milliseconds
    delay(20000);

    ++i;
  }
}