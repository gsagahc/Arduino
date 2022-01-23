/*
 * Example for how to use SinricPro Switch device:
 * - setup a switch device
 * - handle request using callback (turn on/off builtin led indicating device power state)
 * - send event to sinricPro server (flash button is used to turn on/off device manually)
 * 
 * If you encounter any issues:
 * - check the readme.md at https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md
 * - ensure all dependent libraries are installed
 *   - see https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md#arduinoide
 *   - see https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md#dependencies
 * - open serial monitor and check whats happening
 * - check full user documentation at https://sinricpro.github.io/esp8266-esp32-sdk
 * - visit https://github.com/sinricpro/esp8266-esp32-sdk/issues and check for existing issues or open a new one
 */

// Uncomment the following line to enable serial debug output
#define ENABLE_DEBUG

#ifdef ENABLE_DEBUG
       #define DEBUG_ESP_PORT Serial
       #define NODEBUG_WEBSOCKETS
       #define NDEBUG
#endif 

#include <Arduino.h>
#ifdef ESP32
  #include <WiFi.h>
//  #define RELAY_PIN_1 12
//  #define RELAY_PIN_2 14
#else
  #include <ESP8266WiFi.h>
  #define RELAY_PIN_1 4
  #define RELAY_PIN_2 14
#endif
#include "fauxmoESP.h"

#include "SinricPro.h"
#include "SinricProSwitch.h"

#define WIFI_SSID         "SAGAHC"    
#define WIFI_PASS         "02178162401"
#define APP_KEY           "9dc885ca-4547-4b4f-9833-76f3409a40bb"      // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "b344d81f-20b9-443c-86cb-562547245ca4-2b280270-643d-4fb9-9ed9-2d148b89617b"   // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"
#define SWITCH_ID         "5e089bba7734eb47dbccc96e"    // Should look like "5dc1564130xxxxxxxxxxxxxx"
#define BAUD_RATE         115200                // Change baudrate to your need

#define BTN_FLASH 0
const int RELAY1 =5;
bool myPowerState = false;
bool ligado = false;
unsigned long lastBtnPress = 0;

/* bool onPowerState(String deviceId, bool &state) 
 *
 * Callback for setPowerState request
 * parameters
 *  String deviceId (r)
 *    contains deviceId (useful if this callback used by multiple devices)
 *  bool &state (r/w)
 *    contains the requested state (true:on / false:off)
 *    must return the new state
 * 
 * return
 *  true if request should be marked as handled correctly / false if not
 */
bool onPowerState(const String &deviceId, bool &state) {
  Serial.printf("Device %s turned %s (via SinricPro) \r\n", deviceId.c_str(), state?"on":"off");
  myPowerState = state;
  digitalWrite(LED_BUILTIN, myPowerState?LOW:HIGH);
  return true; // request handled properly
}

void handleButtonPress() {
  unsigned long actualMillis = millis(); // get actual millis() and keep it in variable actualMillis
  /* if (ligado==true){
     Serial.print("Desliguei");
     digitalWrite(RELAY1, HIGH); // if myPowerState indicates device turned on: turn on led (builtin led uses inverted logic: LOW = LED ON / HIGH = LED OFF)
     ligado=false;
   }else{
     Serial.print("Liguei");
     digitalWrite(RELAY1, LOW); // if myPowerState indicates device turned on: turn on led (builtin led uses inverted logic: LOW = LED ON / HIGH = LED OFF)
     ligado=true;
   }*/
  if (digitalRead(BTN_FLASH) == LOW && actualMillis - lastBtnPress > 1000)  { // is button pressed (inverted logic! button pressed = LOW) and debounced?
    if (myPowerState==true){
        Serial.printf("Entrei aqui1\r\n");  
       digitalWrite(RELAY1, HIGH); // if myPowerState indicates device turned on: turn on led (builtin led uses inverted logic: LOW = LED ON / HIGH = LED OFF)
    }
    if (myPowerState==false){
       Serial.printf("Entrei aqui2\r\n");  
       digitalWrite(RELAY1, LOW); // if myPowerState indicates device turned on: turn on led (builtin led uses inverted logic: LOW = LED ON / HIGH = LED OFF)
    }
    if (myPowerState) {     // flip myPowerState: if it was true, set it to false, vice versa
      myPowerState = false;
    } else {
      myPowerState = true;
    }
    digitalWrite(LED_BUILTIN, myPowerState?LOW:HIGH); // if myPowerState indicates device turned on: turn on led (builtin led uses inverted logic: LOW = LED ON / HIGH = LED OFF)
    Serial.printf("Entrei aqui3\r\n");  
      
    // get Switch device back
    SinricProSwitch& mySwitch = SinricPro[SWITCH_ID];
    // send powerstate event
    mySwitch.sendPowerStateEvent(myPowerState); // send the new powerState to SinricPro server
    Serial.printf("Device %s turned %s (manually via flashbutton)\r\n", mySwitch.getDeviceId(), myPowerState?"on":"off");

    lastBtnPress = actualMillis;  // update last button press variable
  } 
}

// setup function for WiFi connection
void setupWiFi() {
  Serial.printf("\r\n[Wifi]: Connecting");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf(".");
    delay(250);
  }
  IPAddress localIP = WiFi.localIP();
  Serial.printf("connected!\r\n[WiFi]: IP-Address is %d.%d.%d.%d\r\n", localIP[0], localIP[1], localIP[2], localIP[3]);
  Serial.printf("Entrei aqui 0\r\n");
}

// setup function for SinricPro
void setupSinricPro() {
  // add device to SinricPro
  SinricProSwitch& mySwitch = SinricPro[SWITCH_ID];

  // set callback function to device
  mySwitch.onPowerState(onPowerState);

  // setup SinricPro
  SinricPro.onConnected([](){ Serial.printf("Connected to SinricPro\r\n"); }); 
  SinricPro.onDisconnected([](){ Serial.printf("Disconnected from SinricPro\r\n"); });
  SinricPro.begin(APP_KEY, APP_SECRET);
}

// main setup function
void setup() {
  pinMode(BTN_FLASH, INPUT_PULLUP); // GPIO 0 as input, pulled high
  pinMode(LED_BUILTIN, OUTPUT); // define LED GPIO as output
  digitalWrite(LED_BUILTIN, HIGH); // turn off LED on bootup
  pinMode(RELAY1, OUTPUT);
  digitalWrite(RELAY1, HIGH);
  Serial.begin(BAUD_RATE); Serial.printf("\r\n\r\n");
  setupWiFi();
  setupSinricPro();
}

void loop() {
  handleButtonPress();
  SinricPro.handle();
}
