#pragma once

#include <string>
#include <queue>

class DigitalTransmitter
{
public:
	int pin;

	DigitalTransmitter(int pinNo = 13)
	{
		pin = pinNo;
		pinMode(pin,OUTPUT);
	}


    void sendHigh()
    {
		digitalWrite(led, HIGH); 
    }
};