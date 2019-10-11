#include <Arduino.h>
#include <KemperSerialReceiver.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <string>
#include <iostream>



// Use these with the Teensy Audio Shield
//This uses the audio shield's card reader


AudioPlaySdWav           playSdWav1;
AudioPlaySdWav           playSdWav2;
AudioPlaySdWav			 playSdWav3;
AudioPlaySdWav			 playSdWav4;

AudioPlaySdWav           playSdWavBG;

AudioOutputI2S           audioOutput;

const int numPlayers = 4;
bool isPlaying[numPlayers+1];

AudioMixer4 mixer1;
AudioMixer4 mixer2;
AudioMixer4 bgMixer;
AudioMixer4 effectMixer;
AudioMixer4 mixMaster;

// Sound effect channels to mixers
AudioConnection          patchCord1a(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord1b(playSdWav1, 1, mixer1, 1);
AudioConnection          patchCord2a(playSdWav2, 0, mixer1, 2);
AudioConnection          patchCord2b(playSdWav2, 1, mixer1, 3);
AudioConnection          patchCord3a(playSdWav3, 0, mixer2, 0);
AudioConnection          patchCord3b(playSdWav3, 1, mixer2, 1);
AudioConnection          patchCord4a(playSdWav4, 0, mixer2, 2);
AudioConnection          patchCord4b(playSdWav4, 1, mixer2, 3);
// Sound effects to single mixer
AudioConnection          patchCordEffects1a(mixer1, 0, effectMixer, 0);
AudioConnection          patchCordEffects1b(mixer1, 1, effectMixer, 1);
AudioConnection          patchCordEffects2a(mixer2, 0, effectMixer, 2);
AudioConnection          patchCordEffects2b(mixer2, 1, effectMixer, 3);
// Background Sound Effects to Background Mixer
AudioConnection          patchCordBG1a(playSdWavBG, 0, bgMixer, 0);
AudioConnection          patchCordBG1b(playSdWavBG, 1, bgMixer, 1);
// Effects and Background to Master Mixer
AudioConnection          patchCordToMaster1a(effectMixer, 0, mixMaster, 0);
AudioConnection          patchCordToMaster1b(effectMixer, 1, mixMaster, 1);
AudioConnection          patchCordToMaster2a(bgMixer, 0, mixMaster, 2);
AudioConnection          patchCordToMaster2b(bgMixer, 1, mixMaster, 3);
// Master Mixer out
AudioConnection          patchCordOut1a(mixMaster, 0, audioOutput, 0);
AudioConnection          patchCordOut1b(mixMaster, 1, audioOutput, 1);

AudioControlSGTL5000 sgtl5000_1;

char* lastOutput1;
char* lastOutput2;
std::string backgroundName;
bool hasBackGround = false;
bool hasNewBackGround = false;
bool backgroundIsPlaying = false;
unsigned long backgroundStartMillis;
unsigned long backgroundLengthMillis = 1000;
unsigned long backgroundCheckWait = 1000;
float mixerGain = 0.7;

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

void stopChannel(int i)
{
	switch (i)
	{
		case 0:
			playSdWavBG.stop();
			Serial.println("BACKGROUND: STOPPED");
			Serial.println("========================================");
		break;

		case 1:
			playSdWav1.stop();
			Serial.println("CHANNEL  " + (String)i + ": STOPPED");
			Serial.println("========================================");
		break;

		case 2:
			playSdWav2.stop();
			Serial.println("CHANNEL  " + (String)i + ": STOPPED");
			Serial.println("========================================");
		break;

		case 3:
			playSdWav3.stop();
			Serial.println("CHANNEL  " + (String)i + ": STOPPED");
			Serial.println("========================================");
		break;

		case 4:
			playSdWav4.stop();
			Serial.println("CHANNEL  " + (String)i + ": STOPPED");
			Serial.println("========================================");
		break;
	}
}
void startBGChannel(std::string fileName)
{
	char convertedFileName[12];
	strcpy(convertedFileName, fileName.c_str());
	playSdWavBG.play(convertedFileName);
	Serial.println("CHANNEL: BACKGROUND");
	Serial.println("FILE:    " + (String)convertedFileName);
	Serial.println("========================================");
}

void startChannel(int i, const char* fileName)
{
	switch (i)
	{
		case 0:
			playSdWavBG.play(fileName);
			Serial.println("CHANNEL: BACKGROUND");
			Serial.println("FILE:    " + (String)fileName);
			Serial.println("========================================");
		break;

		case 1:
			playSdWav1.play(fileName);
			// Serial.println("CHANNEL: " + (String)i);
			// Serial.println("FILE:    " + (String)fileName);
			// Serial.println("========================================");
		break;

		case 2:
			playSdWav2.play(fileName);
			Serial.println("CHANNEL: " + (String)i);
			Serial.println("FILE:    " + (String)fileName);
			Serial.println("========================================");
		break;

		case 3:
			playSdWav3.play(fileName);
			Serial.println("CHANNEL: " + (String)i);
			Serial.println("FILE:    " + (String)fileName);
			Serial.println("========================================");
		break;

		case 4:
			playSdWav4.play(fileName);
			Serial.println("CHANNEL: " + (String)i);
			Serial.println("FILE:    " + (String)fileName);
			Serial.println("========================================");
		break;
	}
}

void backgroundTimeCheck()
{
	unsigned long currentTime = millis();
	unsigned long timeElapsed = currentTime - backgroundStartMillis;
	if(timeElapsed>backgroundCheckWait)
	{
		if(!playSdWavBG.isPlaying())
		{
			backgroundIsPlaying = false;
			//hasNewBackGround = true;
			Serial.println("BG checkWait: " + (String)backgroundCheckWait);
			Serial.println("BG Elapsed:   " + (String)timeElapsed);
			Serial.println("BG isPlaying: " + (String)backgroundIsPlaying);
			Serial.println("===============================");
		}
	}
}


void playBG()
{
    if(!backgroundIsPlaying && hasBackGround)
    {
        startBGChannel(backgroundName);
		backgroundIsPlaying = true;
		backgroundStartMillis = millis();
		backgroundLengthMillis = playSdWavBG.lengthMillis();
		//hasNewBackGround = false;
    }
	else if(backgroundIsPlaying)
	{
		backgroundLengthMillis = playSdWavBG.lengthMillis();
		backgroundTimeCheck();
	}
}


void setBG(char* fileName)
{
	playSdWavBG.stop();
	backgroundIsPlaying = false;
	hasBackGround = true;
	backgroundName = fileName;
	Serial.println((String)backgroundName.c_str());
	Serial.println("BG STATUS: " + (String)playSdWavBG.isPlaying());
	playBG();
	// startChannel(0, background);
}

void playWav(const char* fileName)
{
	// if(!playSdWav1.isPlaying())
	// {
	// 	startChannel(1, fileName);
	// }
	// else if(!playSdWav2.isPlaying())
	// {
	// 	startChannel(2, fileName);
	// }
	// else 
	if(!playSdWav3.isPlaying())
	{
		startChannel(3, fileName);
	}
	else if(!playSdWav4.isPlaying())
	{
		startChannel(4, fileName);
	}
	else
	{
		startChannel(3, fileName);
		Serial.println("OVERWRITE==OVERWRITE==OVERWRITE");
	}
	
}
//=============================================================================//
//SETUP AND LOOP
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
    
    mixMaster.gain(0, 0.5);
    mixMaster.gain(1, 0.5);
    mixer1.gain(0,mixerGain);
    mixer1.gain(1,mixerGain);
    mixer1.gain(2,mixerGain);
    mixer1.gain(3,mixerGain);
    mixer2.gain(0,mixerGain);
    mixer2.gain(1,mixerGain);
    mixer2.gain(2,mixerGain);
    mixer2.gain(3,mixerGain);
    effectMixer.gain(0,mixerGain);
    effectMixer.gain(1,mixerGain);
    effectMixer.gain(2,mixerGain);
    effectMixer.gain(3,mixerGain);
    bgMixer.gain(0,mixerGain);
    bgMixer.gain(1,mixerGain);
    bgMixer.gain(2,mixerGain);
    bgMixer.gain(3,mixerGain);



	playWav("FUEL100.WAV");
	delay(50);
	playWav("FUEL50.WAV");
	//delay(5000);

    //setBG("<MOONJAZZ.WAV>");

    //playSdWavBG.play("BOOM.WAV");
	Serial.println("starting the loop");
}

void channelChecker(char* message)
{
	char channelChar = message[0];
	char channelNum = channelChar - '0';
	char isStart = message[1];
	if(channelNum == 1 || channelNum == 2)
	{
		char* trimmedOutput = message;
		trimmedOutput++;
		trimmedOutput++;
		if(isStart == '1')
		{
			startChannel(channelNum, trimmedOutput);
		}else if(isStart == '0')
		{
			stopChannel(channelNum);
		}
	}
	else if(channelNum == 9)
	{
		char* trimmedOutput = message;
		trimmedOutput++;
		setBG(trimmedOutput);
	}
	else
	{
		playWav(message);
	}
}

void loop()
{
    playBG();
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
			char channelChar = output[0];
			char channelNum = channelChar - '0';
			char isStart = output[1];
			channelChecker(output);
		}
	}
}
