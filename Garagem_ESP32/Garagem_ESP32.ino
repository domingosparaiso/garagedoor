#include <WiFi.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include "Garagem.h"
  
WebServer server(80);
bool console_ok = false;

bool console_init() {
  long timeout = millis() + TIMEOUT_CONSOLE;
  Serial.begin(CONSOLE_BAUD);
  while (!Serial && millis() < timeout);
  console_ok = (!Serial)?false:true;
  return(console_ok);
}

void console_log(String msg) {
  activity(FLASH);
  if(console_ok) Serial.print(msg);
}

// Change status LED (usually onboard LED)
void activity(int mode) {
  #ifdef LED_PIN
    led_control(LED_PIN, mode);
  #endif
}

void buttonled(int mode) {
  led_control(LED_BUTTON, mode);
}

void led_control(int led_pin, int mode) {
  switch(mode) {
    case INIT:
      pinMode(led_pin, OUTPUT);
      break;
    case ON:
      // Turn LED ON
      digitalWrite(led_pin, LED_LEVEL_ON);
      break;
    case OFF:
      // Turn LED OFF
      digitalWrite(led_pin, LED_LEVEL_OFF);
      break;
    case FLASH:
      // Change LED (ON/OFF)
      digitalWrite(led_pin, !digitalRead(led_pin));
      break;
  }
}

void setup() {
  activity(INIT);
  delay(2000);
  console_init();
  delay(500);  
  console_log("\nPower ON\n");
  connect_wifi();
  server_setup();
  console_log("System ready!\n");
  activity(OFF);
}

void loop() {
  // loop do webserver
  server_loop();
  // loop da máquina de estado
  garage_state_machine();
}

