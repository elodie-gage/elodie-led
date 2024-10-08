#include <WiFi.h>
#include <WiFiUdp.h>

#include <FastLED.h>
#define NUM_LEDS 240
#define LED_PIN 23

const char* ssid = "ngauruhoe";
const char* password = "frootjuus";

// uint8_t packetBuffer[255]; //buffer to hold incoming packet

WiFiUDP Udp;

CRGB leds[NUM_LEDS];

unsigned long lastpacket;

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network
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
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // print the received signal strength:

  long rssi = WiFi.RSSI();

  Serial.print("signal strength (RSSI):");

  Serial.print(rssi);

  Serial.println(" dBm");

  Serial.println("Starting to listen to UDP packets...");


  Udp.begin(8976);

  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);

  lastpacket = 0;
}




void loop() {


  int packetSize = Udp.parsePacket();

  if (packetSize) {

    // Serial.print("Received packet of size ");

    // Serial.println(packetSize);

    unsigned long thispacket = micros();
    unsigned long elapsed = (thispacket - lastpacket) / 1000;
    lastpacket = thispacket;
    if (elapsed > 1000) {elapsed = 1000;}

    Serial.print("elapsed:");
    Serial.println(elapsed);
    

    // read the packet into packetBufffer

    int len = Udp.read((uint8_t*)leds, NUM_LEDS*3);

    // int ledindex = 0;

    // while (len > (ledindex*3)+2) {
    //   leds[ledindex] = CRGB(
    //     packetBuffer[(ledindex*3)+0], 
    //     packetBuffer[(ledindex*3)+1], 
    //     packetBuffer[(ledindex*3)+2]);
    //   ledindex++;
    // }

    FastLED.show();
  }

}