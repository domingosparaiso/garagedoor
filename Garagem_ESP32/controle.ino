int state_machine = STATE_INIT;
unsigned long timeout_door = 0;
unsigned long timeout_debounce = 0;
bool pressed = false;
unsigned long timeout_debug = 0;

void relay_close() {
  digitalWrite(RELAY_CLOSE, RELAY_LEVEL_ON);
}

void relay_open() {
  digitalWrite(RELAY_OPEN, RELAY_LEVEL_ON);
}

void relay_stop() {
  digitalWrite(RELAY_OPEN, RELAY_LEVEL_OFF);
  digitalWrite(RELAY_CLOSE, RELAY_LEVEL_OFF);
}

void check_button() {
  #ifdef GARAGE_BUTTON
    if(digitalRead(GARAGE_BUTTON) == BUTTON_LEVEL_ON) {
      if(timeout_debounce < millis()) {
        timeout_debounce = millis() + TIMEOUT_DEBOUNCE;
        Serial.print(String("Botão pressionado: ") + garage_button());
      }
    }
  #endif
}

String garage_button() {
  led_control(LED_BUTTON, ON);
  pressed = true;
  if(state_machine == STATE_OPEN || state_machine == STATE_STOP_OPEN) return("Fechando garagem");
  if(state_machine == STATE_CLOSED || state_machine == STATE_STOP_CLOSE) return("Abrindo garagem");
  if(state_machine == STATE_OPENING || state_machine == STATE_CLOSING) return("Parando portão");
}

bool button_pressed() {
  if(pressed) {
    pressed = false;
    led_control(LED_BUTTON, OFF);
    return(true);
  } else {
    return(false);
  }
}

void garage_open() {
  timeout_door = millis() + (TIMEOUT_OPEN_CLOSE * 1000);
  state_machine = STATE_OPENING;
  relay_open();
}

void garage_close() {
  timeout_door = millis() + (TIMEOUT_OPEN_CLOSE * 1000);
  state_machine = STATE_CLOSING;
  relay_close();
}

int reed_sensor() {
  int sensor_open = digitalRead(SENSOR_DOOR_OPEN);
  int sensor_closed = digitalRead(SENSOR_DOOR_CLOSED);
  int reed_status = SENSOR_MOVING;
  if(sensor_open == SENSOR_LEVEL_ON and sensor_closed == SENSOR_LEVEL_OFF) reed_status = SENSOR_OPEN;
  if(sensor_open == SENSOR_LEVEL_OFF and sensor_closed == SENSOR_LEVEL_ON) reed_status = SENSOR_CLOSE;
  return(reed_status);
}

String sensor_read() {
  String sensor_open = "OFF";
  String sensor_closed = "OFF";
  if(digitalRead(SENSOR_DOOR_OPEN)==SENSOR_LEVEL_ON) sensor_open="ON";
  if(digitalRead(SENSOR_DOOR_CLOSED)==SENSOR_LEVEL_ON) sensor_closed="ON";
  return(String("Open: ") + sensor_open + String(", Close: ") + sensor_closed);
}

/*
void check_door() {
  #ifdef SENSOR_DOOR
    if(digitalRead(SENSOR_DOOR) == DOOR_LEVEL_ON) {
      if(state_machine == STATE_OPEN) timeout_door = millis() + (TIMEOUT_OPEN * 1000);
      if(state_machine == STATE_CLOSING) {
        relay_stop();
        state_machine = STATE_STOP_CLOSE;
      }
    }
  #endif
}
*/

void garage_state_machine() {
  check_button();
  // check_door();
  switch(state_machine) {
    case STATE_INIT:
      relay_stop();
      if(reed_sensor() == SENSOR_CLOSE) {
        state_machine = STATE_CLOSED;
      } else {
        if(timeout_door < millis()) {
          if(timeout_door == 0) relay_close();
          timeout_door = millis() + (TIMEOUT_OPEN_CLOSE * 1000);
        } else {
          state_machine = STATE_FAIL;
        }
      }
      break;
    case STATE_CLOSING:
      if(reed_sensor() == SENSOR_CLOSE) {
        relay_stop();
        state_machine = STATE_CLOSED;
      }
      if(button_pressed()) {
        relay_stop();
        state_machine = STATE_STOP_CLOSE;
      } else {
        if(timeout_door < millis()) {
          state_machine = STATE_FAIL;
        }
      }
      break;
    case STATE_CLOSED:
      if(button_pressed()) {
        garage_open();
      }
      break;
    case STATE_OPENING:
      if(reed_sensor() == SENSOR_OPEN) {
        relay_stop();
        state_machine = STATE_OPEN;
        timeout_door = millis() + (TIMEOUT_OPEN * 1000);
      }
      if(button_pressed()) {
        relay_stop();
        state_machine = STATE_STOP_OPEN;
      } else {
        if(timeout_door < millis()) {
          state_machine = STATE_FAIL;
        }
      }
      break;
    case STATE_OPEN:
      if(button_pressed()) {
        garage_close();
      }
      break;
    case STATE_STOP_CLOSE:
      if(button_pressed()) {
        garage_open();
      }
      break;
    case STATE_STOP_OPEN:
       if(button_pressed()) {
        garage_close();
      }
     break;
    case STATE_FAIL:
      if(button_pressed()) {
        garage_close();
      }
      activity(FLASH);
      delay(500);
      break;
  }
  if(timeout_debug < millis()) {
    int rs;
    timeout_debug = millis() + 1000;
    Serial.print("Button: ");
    Serial.print(button_pressed?"ON":"OFF");
    Serial.print(" Sensor: ");
    rs = reed_sensor();
    switch(rs) {
      case SENSOR_CLOSE:
        Serial.print("Fechado");
        break;
      case SENSOR_OPEN:
        Serial.print("Aberto");
        break;
      case SENSOR_MOVING:
        Serial.print("Movendo");
        break;
    }
    Serial.print(" State: ");
    switch(state_machine) {
      case STATE_INIT:
          Serial.print("Inicializando");
          break;
      case STATE_CLOSING:
          Serial.print("Fechando");
          break;
      case STATE_CLOSED:
          Serial.print("Fechado");
          break;
      case STATE_OPENING:
          Serial.print("Abrindo");
          break;
      case STATE_OPEN:
          Serial.print("Aberto");
          break;
      case STATE_STOP_CLOSE:
          Serial.print("Parou fechando");
          break;
      case STATE_STOP_OPEN:
          Serial.print("Parou abrindo");
          break;
      case STATE_FAIL:
          Serial.print("Falha");
          break;
    }
    Serial.println("\n------------------------------------------------------");
  }
}