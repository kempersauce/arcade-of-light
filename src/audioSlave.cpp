// #include <Arduino.h>
// #include <KemperSerialReceiver.h>

// #include <Audio.h>
// #include <Wire.h>
// #include <SPI.h>
// #include <SD.h>
// #include <SerialFlash.h>

// AudioControlSGTL5000 sgtl5000_1;
// AudioOutputI2S i2s1;

// // Use these with the Teensy Audio Shield
// //This uses the audio shield's card reader
// #define SDCARD_CS_PIN    10
// #define SDCARD_MOSI_PIN  7
// #define SDCARD_SCK_PIN   14

// AudioPlaySdWav           playSdWav1;

// AudioConnection          patchCord1(playSdWav1, 0, i2s1, 0);

// KemperSerialReceiver serialReceiver[4]{
// 	KemperSerialReceiver(Serial1),
// 	KemperSerialReceiver(Serial2),
// 	KemperSerialReceiver(Serial3),
// 	KemperSerialReceiver(Serial4)
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

// 	playSdWav1.play("HUMANITY.WAV");
// }

// void loop()
// {
// 	for (int i = 0; i < 4; i++)
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

// 			playSdWav1.play(output);

// 			Serial.println("Done");
// 		}
// 	}
// }
