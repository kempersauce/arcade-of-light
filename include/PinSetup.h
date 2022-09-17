/*
Pin numbers for teensy setup
*/

#pragma once

// LED STRIPS
#define LED_PIN_0 18
#define LED_PIN_1 19
#define LED_PIN_2 20
#define LED_PIN_3 21
#define LED_PIN_4 22
#define LED_PIN_5 23
#define LED_PIN_6 24
#define LED_PIN_7 25

// TODO: I just blindly addressed these - need to figure out actual pins
// Maybe we should put all the pins in their own namespaces
// instead of using #defines like this
#define LED_PIN_8 26
#define LED_PIN_9 27
#define LED_PIN_10 28
#define LED_PIN_11 29
#define LED_PIN_12 30
#define LED_PIN_13 31
#define LED_PIN_14 32
#define LED_PIN_15 33
#define LED_PIN_16 34
#define LED_PIN_17 35
#define LED_PIN_18 36
#define LED_PIN_19 37

// Controller pins
#define CONTROLLER_PIN_0 2
#define CONTROLLER_PIN_1 3
#define CONTROLLER_PIN_2 4
#define CONTROLLER_PIN_3 7

// BUTTONS
#define BUTTON_PIN_0 8
#define BUTTON_PIN_1 9
#define BUTTON_PIN_2 10
#define BUTTON_PIN_3 11
#define BUTTON_PIN_4 12
#define BUTTON_PIN_5 13
//#define BUTTON_PIN_6 30

// UP IS RIGHT 3
// Down IS LEFT 4
// LEFT is UP 2
// RIGHT IS DOWN 5

/*
  H2H Pin numbers
*/

// LED STRIPS
// #define H2H_LED_PIN_0 20
// #define H2H_LED_PIN_1 17
// #define H2H_LED_PIN_2 16
// #define H2H_LED_PIN_3 39
// #define H2H_LED_PIN_4 38
// #define H2H_LED_PIN_5 37
// #define H2H_LED_PIN_6 36
// #define H2H_LED_PIN_7 35

// BUTTONS

// Old button pins on the test bed
// #define H2H_BUTTON_PIN_0 2
// #define H2H_BUTTON_PIN_1 3
// #define H2H_BUTTON_PIN_2 4
// #define H2H_BUTTON_PIN_3 5
// #define H2H_BUTTON_PIN_4 8
// #define H2H_BUTTON_PIN_5 24
// #define H2H_BUTTON_PIN_6 25
// #define H2H_BUTTON_PIN_7 26
// #define H2H_BUTTON_PIN_8 27
// #define H2H_BUTTON_PIN_9 28
// #define H2H_BUTTON_PIN_10 29
// #define H2H_BUTTON_PIN_11 30
// #define H2H_BUTTON_PIN_12 31
// #define H2H_BUTTON_PIN_13 32
// #define H2H_BUTTON_PIN_14 33
// #define H2H_BUTTON_PIN_15 34

// Right to left (team A)
#define H2H_BUTTON_PIN_0 2
#define H2H_BUTTON_PIN_1 3
#define H2H_BUTTON_PIN_2 4
#define H2H_BUTTON_PIN_3 5
#define H2H_BUTTON_PIN_4 8
#define H2H_BUTTON_PIN_5 24
#define H2H_BUTTON_PIN_6 25
#define H2H_BUTTON_PIN_7 26

#define H2H_BUTTON_PIN_8 27
#define H2H_BUTTON_PIN_9 28
#define H2H_BUTTON_PIN_10 29
#define H2H_BUTTON_PIN_11 30
#define H2H_BUTTON_PIN_12 31
#define H2H_BUTTON_PIN_13 32
#define H2H_BUTTON_PIN_14 33
#define H2H_BUTTON_PIN_15 34

// AUDIO
// We dont have an audio volume pin....
#define AUDIO_VOLUME_PIN 13
