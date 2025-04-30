#include "ssid.h"

void connect_wifi() {
  console_log("Configure WiFi into AP mode...");
  IPAddress ip(192, 168, 1, 80);
  IPAddress gateway(192, 168, 1, 80);
  IPAddress subnet(255, 255, 255, 0);
  console_log(" [OK]\n");
  console_log("SSID: ");
  console_log(DEFAULT_AP_SSID);
  console_log("\nPassword: ");
  console_log(DEFAULT_AP_PASS);
  console_log("\nStart WiFi into AP Mode...");
  while(!WiFi.softAP(DEFAULT_AP_SSID, DEFAULT_AP_PASS)) {
    console_log("Error... try again in 10s\n");
    delay(10000);
  }
  WiFi.softAPConfig(ip, gateway, subnet);
  console_log("\nConnected: [192.168.1.80]... [OK]\n");
}
