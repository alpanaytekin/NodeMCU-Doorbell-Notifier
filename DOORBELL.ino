#include <ESP8266WiFi.h>
/*#include <WiFiClientSecure.h>*/
#include <WiFiClient.h>
#include <Pushsafer.h>

// Initialize Wifi connection to the router
char ssid[] = "######";     // your network SSID (name)
char password[] = "######"; // your network key

// Pushsafer private or alias key
#define PushsaferKey "######"

/*WiFiClientSecure client;*/
WiFiClient client;
Pushsafer pushsafer(PushsaferKey, client);
const int analogInPin = A0;  // ESP8266 Analog Pin ADC0 = A0
int sensorValue = 0;  // value read from the pot

void setup() {
  Serial.begin(115200);

  // internal flash düğmesi
  pinMode(0, INPUT_PULLUP);
  pinMode(0, INPUT);

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  pushsafer.debug = true;
  Serial.println("Device Online");
  // client.stop();
}

void door(){
  struct PushSaferInput doorbell;
  doorbell.message = "DOOR BELL RANG!";
  doorbell.title = "";
  doorbell.sound = "8";
  doorbell.vibration = "0";
  doorbell.icon = "1";
  doorbell.iconcolor = "#FFCCCC";
  doorbell.priority = "0";
  doorbell.device = "a";
  doorbell.url = "";
  doorbell.urlTitle = "";
  doorbell.picture = "";
  doorbell.picture2 = "";
  doorbell.picture3 = "";
  doorbell.time2live = "";
  doorbell.retry = "";
  doorbell.expire = "";
  doorbell.answer = "";
  Serial.println(pushsafer.sendEvent(doorbell));
}

void loop() {
  
  sensorValue = analogRead(analogInPin);
  if (sensorValue > 100) {
    door();
    delay(4000);
  }  
  delay(200);
}
