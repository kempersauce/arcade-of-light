
#include <string>
#include <queue>

class KemperSerialTransmitter
{

public:
	HardwareSerial serial;
	const static byte numChars = 32;

	KemperSerialTransmitter(HardwareSerial &serialRef){
	  serial.begin(9600);
	}
    void sendMessage(String msg)
    {
      int msgLength = msg.length();
      {
        if(msgLength > numChars)
        {
          return;
        }
        else
        {
          String finalMsg = "<"+msg+">";
          serial.print(finalMsg);
        }
      }
    }

};
