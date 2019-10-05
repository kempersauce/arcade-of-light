// #include <Arduino.h>
// #include <KemperSerialReceiver.h>

// #include <Audio.h>
// #include <Wire.h>
// #include <SPI.h>
// #include <SD.h>
// #include <SerialFlash.h>



// // Use these with the Teensy Audio Shield
// //This uses the audio shield's card reader


// const int numAudioPlayers = 5;
// AudioPlaySdWav           playSdWav1;
// AudioPlaySdWav           playSdWav2;
// AudioPlaySdWav			 playSdWav3;
// AudioPlaySdWav			 playSdWav4;
// AudioPlaySdWav           playSdWavBG;

// AudioOutputI2S           audioOutput;

// AudioPlaySdWav audioPlayers[5] = {
// 	playSdWav1,
// 	playSdWav2,
// 	playSdWav3,
// 	playSdWav4,
// 	playSdWavBG
// };

// AudioConnection          patchCord1(audioPlayers[0], 0, audioOutput, 0);
// AudioConnection          patchCord2(audioPlayers[1], 0, audioOutput, 1);
// AudioConnection          patchCord3(audioPlayers[2], 0, audioOutput, 2);
// AudioConnection          patchCord4(audioPlayers[3], 0, audioOutput, 3);

// AudioConnection          patchCord5(audioPlayers[4], 0, audioOutput, 5);

// AudioControlSGTL5000 sgtl5000_1;


// bool audioPlayerIsPlaying[numAudioPlayers];
// String lastOutputFileName[numAudioPlayers];

// #define SDCARD_CS_PIN    10
// #define SDCARD_MOSI_PIN  7
// #define SDCARD_SCK_PIN   14

// KemperSerialReceiver serialReceiver[2]{
// 	// KemperSerialReceiver(&Serial1),
// 	// KemperSerialReceiver(&Serial2),
// 	// KemperSerialReceiver(&Serial3),
// 	KemperSerialReceiver(&Serial4),
// 	KemperSerialReceiver(&Serial5)
// };



// void setup()
// {
// 	Serial.begin(115200);
// 	AudioMemory(16);
// 	sgtl5000_1.enable();
// 	sgtl5000_1.volume(1);
// 	SPI.setMOSI(SDCARD_MOSI_PIN);
// 	SPI.setSCK(SDCARD_SCK_PIN);
// 	if (!(SD.begin(SDCARD_CS_PIN)))
// 	{
// 		while (1)
// 		{
// 			Serial.println("Unable to access the SD card");
// 			delay(500);
// 		}
// 	}
// 	audioPlayers[4].play("BOOM.WAV");
// 	delay(5000);
//     //playSdWavBG.play("MAMBO5.WAV");
// 	Serial.println("starting the loop");

// 	for(int i=0; i++; i<numAudioPlayers)
// 	{
// 		audioPlayerIsPlaying[i] = false;
// 	}
// }

// //use this to stop a channel from playing a wav
// void stopPlayer(int i)
// {
// 	if(i<numAudioPlayers)
// 	{
// 		audioPlayers[i].stop();
// 		audioPlayerIsPlaying[i] = false;
// 		Serial.println("Player " + (String)i + ": STOPPED");
// 	}
// }

// void startPlayer(int i, const char* fileName)
// {
// 	if(i<numAudioPlayers)
// 	{
// 		audioPlayers[i].stop();
// 		audioPlayerIsPlaying[i] = false;

// 		lastOutputFileName[i] = (String)fileName;
		
// 		Serial.println("Player " + (String)i + ": START FILE: " + (String)fileName);
// 	}
// }

// void play(const char* fileName)
// {	
// 	for(int i=0; i<numAudioPlayers; i++)
// 	{
// 		if(!audioPlayerIsPlaying[i])
// 		{
// 			audioPlayers[i].play(fileName);
// 			audioPlayerIsPlaying[i] = true;
// 		}
// 	}
// }

// void playBG(const char* fileName)
// {
//     if(!playSdWavBG.isActive())
//     {
//         playSdWavBG.play(fileName);
//     }
// }

// void checkPlayers()
// {
// 	for(int i=0; i<numAudioPlayers; i++)
// 	{
// 		if(!audioPlayers[i].isPlaying())
// 		{
// 			audioPlayerIsPlaying[i] = false;
// 		}
// 	}
// }

// void playWav(const char* fileName)
// {
// 	for(int i=0; i<numAudioPlayers; i++)
// 	{
// 		if(!audioPlayerIsPlaying[i])
// 		{
// 			for(int i=0; i<numAudioPlayers; i++)
// 			{
// 				if((String)fileName != lastOutputFileName[i])
// 				{
// 					audioPlayers[i].play(fileName);
// 				}
// 			}
// 		}
// 	}
// }

// void loop()
// {
//     //playBG("GYCYCHIP.WAV");
// 	for (int i = 0; i < 2; i++)
// 	{
// 		serialReceiver[i].recvWithStartEndMarkers();
// 		while (serialReceiver[i].hasMessages())
// 		{
// 			char output[32];
// 			serialReceiver[i].getNextMessage(output);
// 			Serial.print("playing from serial");
// 			Serial.print(i + 1);
// 			Serial.print(": ");
// 			Serial.println(output);

//             playWav(output);
            

			
// 			Serial.println("Done");
// 		}
// 	}
// 	checkPlayers();
// }

