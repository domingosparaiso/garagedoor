#pragma once

#define VERSION "0.01b"
// LED da placa para mostrar o status
#define LED_PIN 27
#define LED_LEVEL_ON HIGH
// relés conectados ao motor para abrir e fechar o portão
#define RELAY_OPEN 16
#define RELAY_CLOSE 17
#define RELAY_LIGHT 18
#define RELAY_LEVEL_ON LOW
#define TIMEOUT_LIGHT 900
// sensores de portão aberto e portão fechado
#define SENSOR_DOOR_OPEN 21
#define SENSOR_DOOR_CLOSED 22
#define SENSOR_LEVEL_ON LOW
#define LED_BUTTON 13
// opcional, botão físico para abrir a garagem sem o controle
#define GARAGE_BUTTON 23
#define INTERNAL_BUTTON 33
#define BUTTON_LEVEL_ON LOW
// tempo máximo que pode levar para abrir ou fechar a porta da garagem (em segundos)
#define TIMEOUT_OPEN_CLOSE 20
// tempo máximo que a porta da garagem pode ficar aberta (em segundos)
#define TIMEOUT_OPEN 300
// opcional, sensor de passagem pela porta da garagem
//#define SENSOR_DOOR 22
//#define DOOR_LEVEL_ON LOW

//-----------------------------------------------------
// tipos enumerados

#define STATE_INIT 0
#define STATE_CLOSING 1
#define STATE_CLOSED 2
#define STATE_OPENING 3
#define STATE_OPEN 4
#define STATE_STOP_CLOSE 5
#define STATE_STOP_OPEN 6
#define STATE_FAIL 7

#define SENSOR_MOVING 0
#define SENSOR_CLOSE 1
#define SENSOR_OPEN 2

#define OFF 0
#define ON 1
#define FLASH 2
#define INIT 3

//-----------------------------------------------------
// valores dos níveis deligados

#if LED_LEVEL_ON == LOW
#define LED_LEVEL_OFF HIGH
#else
#define LED_LEVEL_OFF LOW
#endif
#if RELAY_LEVEL_ON == LOW
#define RELAY_LEVEL_OFF HIGH
#else
#define RELAY_LEVEL_OFF LOW
#endif
#if SENSOR_LEVEL_ON == LOW
#define SENSOR_LEVEL_OFF HIGH
#else
#define SENSOR_LEVEL_OFF LOW
#endif
#if BUTTON_LEVEL_ON == LOW
#define BUTTON_LEVEL_OFF HIGH
#else
#define BUTTON_LEVEL_OFF LOW
#endif
#if DOOR_LEVEL_ON == LOW
#define DOOR_LEVEL_OFF HIGH
#else
#define DOOR_LEVEL_OFF LOW
#endif

//-----------------------------------------------------

#define CONSOLE_BAUD 115200
#define TIMEOUT_CONSOLE 5000
#define TIMEOUT_DEBOUNCE 200

// <EOF>