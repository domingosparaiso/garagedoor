#include "html.h"
unsigned long timeout_light = 0;

String garage_light() {
  if(digitalRead(RELAY_LIGHT) == RELAY_LEVEL_ON) {
    digitalWrite(RELAY_LIGHT, RELAY_LEVEL_OFF);
    return("Apagando a luz");
  }
  digitalWrite(RELAY_LIGHT, RELAY_LEVEL_ON);
  timeout_light = millis() + TIMEOUT_LIGHT * 1000;
  return("Acendendo a luz");
}

void light_on() {
  digitalRead(RELAY_LIGHT) == RELAY_LEVEL_ON;
}

void light_off() {
  digitalRead(RELAY_LIGHT) == RELAY_LEVEL_OFF;
}

// Webserver setup
void server_setup() {
  server.on("/garage", []() {
    activity(FLASH);
    send_result_text(garage_button());
  });
  server.on("/light", []() {
    activity(FLASH);
    send_result_text(garage_light());
  });  
  server.on("/status", []() {
    switch(state_machine) {
        case STATE_INIT:
            send_result_text("Inicializando");
            break;
        case STATE_CLOSING:
            send_result_text("Fechando");
            break;
        case STATE_CLOSED:
            send_result_text("Fechado");
            break;
        case STATE_OPENING:
            send_result_text("Abrindo");
            break;
        case STATE_OPEN:
            send_result_text("Aberto");
            break;
        case STATE_STOP_CLOSE:
            send_result_text("Parou fechando");
            break;
        case STATE_STOP_OPEN:
            send_result_text("Parou abrindo");
            break;
        case STATE_FAIL:
            send_result_text("Falha");
            break;
    }
  });  
  server.on("/test", []() {
    server.send(200, "text/html", testHtml);
  });
  server.on("/open", []() {relay_open(); send_result_text("OK");} );
  server.on("/close", []() {relay_close(); send_result_text("OK");} );
  server.on("/on", []() {light_on(); send_result_text("OK");} );
  server.on("/off", []() {light_off(); send_result_text("OK");} );
  server.on("/sensor", []() {send_result_text(sensor_read());} );
  server.onNotFound([]() {
    server.send(401, "text/plain", "Page not found.");
  });
  server.begin();
  console_log("Server setup... [OK]\n");
}

// Send a result to browser as json
void send_result_text(String result) {
  server.send(200, "text/plain", result);
}

// Webserver loop
void server_loop() {
  // handle webserver clients
  server.handleClient();
  if(timeout_light > 0 && timeout_light < millis()) {
    digitalWrite(RELAY_LIGHT, RELAY_LEVEL_OFF);
    timeout_light = 0;
  }
}