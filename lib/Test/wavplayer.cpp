//working audio example

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

AudioPlaySdWav           playSdWav1;
AudioPlaySdWav           playSdWav2;
AudioPlaySdWav           playSdWav3;
AudioPlaySdWav           playSdWav4;
AudioOutputI2S           i2s1;
AudioConnection          patchCord1(playSdWav1, 0, i2s1, 0);
AudioConnection          patchCord2(playSdWav2, 0, i2s1, 1);
AudioConnection          patchCord3(playSdWav3, 0, i2s1, 2);
AudioConnection          patchCord4(playSdWav4, 0, i2s1, 3);
AudioControlSGTL5000     sgtl5000_1;

// Use these with the Teensy Audio Shield
//This uses the audio shield's card reader
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

class Button {
//Arduino pin button is connected to
int _pin;
public:
    //Constructor
    Button(int);
    //Functions
    /**Reads the current state of the button
     * @return - HIGH(1/pressed) or LOW(0/unpressed)
     * */
    int read()
    {
    return digitalRead(_pin);
    }
};
/**
 * Button Constructor
 * @pin number of pin buton is connected to
 */
Button::Button(int pin)
    {
        pinMode(pin, INPUT);
        _pin = pin;
    }

Button ABut(24); //Buttons go here
Button BBut(25);
Button CBut(26);
Button DBut(27);
Button EBut(28);
Button FBut(29);


void setup() {
  Serial.begin(9600);
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(.5);
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
  delay(1000);
}

void loop() {
 // if (playSdWav1.isPlaying() == false) {
  if (ABut.read() == HIGH){
      playSdWav2.play("Guycey1.wav");
    Serial.println("Button A Pressed");
    delay(500);
  }
  if (BBut.read() == HIGH){
    playSdWav1.play("WEEK1.WAV");
    Serial.println("Button B Pressed");
    delay(500);
  }
  if (CBut.read() == HIGH){
    playSdWav1.play("WEEK2.WAV");
    Serial.println("Button C Pressed");
    delay(500);
  }
  if (DBut.read() == HIGH){
    playSdWav1.play("WEEK3.WAV");
    Serial.println("Button D Pressed");
    delay(500);
  }
  if (EBut.read() == HIGH){
    playSdWav1.play("WEEK4.WAV");
    Serial.println("Button E Pressed");
    delay(500);
  }
  if (FBut.read() == HIGH){
    playSdWav1.play("Gladiat.wav");
    Serial.println("Button F Pressed");
    delay(500);
  }
//  }
}
