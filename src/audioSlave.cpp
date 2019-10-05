#include <Arduino.h>
#include <KemperSerialReceiver.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>



// Use these with the Teensy Audio Shield
//This uses the audio shield's card reader


AudioPlaySdWav           playSdWav1;
AudioPlaySdWav           playSdWav2;
AudioPlaySdWav			 playSdWav3;
AudioPlaySdWav			 playSdWav4;
AudioPlaySdWav           playSdWavBG;
AudioOutputI2S           audioOutput;


AudioConnection          patchCord1(playSdWav1, 0, audioOutput, 1);
AudioConnection          patchCord2(playSdWav2, 0, audioOutput, 2);
AudioConnection          patchCord3(playSdWav3, 0, audioOutput, 3);
AudioConnection          patchCord4(playSdWav4, 0, audioOutput, 4);

AudioConnection          patchCord5(playSdWavBG, 0, audioOutput, 0);

AudioControlSGTL5000 sgtl5000_1;

char* lastOutput1;
char* lastOutput2;

#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

KemperSerialReceiver serialReceiver[2]{
	// KemperSerialReceiver(&Serial1),
	// KemperSerialReceiver(&Serial2),
	// KemperSerialReceiver(&Serial3),
	KemperSerialReceiver(&Serial4),
	KemperSerialReceiver(&Serial5)
};



void setup()
{
	Serial.begin(115200);
	AudioMemory(16);
	sgtl5000_1.enable();
	sgtl5000_1.volume(1);
	SPI.setMOSI(SDCARD_MOSI_PIN);
	SPI.setSCK(SDCARD_SCK_PIN);
	if (!(SD.begin(SDCARD_CS_PIN)))
	{
		while (1)
		{
			Serial.println("Unable to access the SD card");
			delay(500);
		}
	}
	playSdWav1.play("HUMANITY.WAV");
	delay(5000);
    //playSdWavBG.play("MAMBO5.WAV");
	Serial.println("starting the loop");
}

void stopChannel(int i)
{
	switch (i)
	{
		case 0:
			playSdWavBG.stop();
		break;

		case 1:
			playSdWav1.stop();
		break;

		case 2:
			playSdWav2.stop();
		break;

		case 3:
			playSdWav3.stop();
		break;

		case 4:
			playSdWav4.stop();
		break;
	}

	

}

void playBG(const char* fileName)
{
    if(!playSdWavBG.isPlaying())
    {
        playSdWavBG.play(fileName);
    }
}

void loop()
{
    //playBG("GYCYCHIP.WAV");
	for (int i = 0; i < 2; i++)
	{
		serialReceiver[i].recvWithStartEndMarkers();
		while (serialReceiver[i].hasMessages())
		{
			char output[32];
			serialReceiver[i].getNextMessage(output);
			Serial.print("playing from serial");
			Serial.print(i + 1);
			Serial.print(": ");
			Serial.println(output);
            if(!playSdWav1.isPlaying())
            {
			    playSdWav1.play(output);
                Serial.println("channel 1 playing");
				lastOutput1 = output;
            }
            else if(!playSdWav2.isPlaying() 
			&& output != lastOutput1)
            {
                playSdWav2.play(output);
                Serial.println("channel 2 playing");
            }
            else
            {
                Serial.println("all channels occupied");
            }
            

			
			Serial.println("Done");
		}
	}
}

