// #include <queue>

// using namespace std;

// class USBSerialReceiver
// {

//     queue<char *> outputQueue;

// public:
//     const static byte numChars = 32;

//     //char receivedChars[numChars];
//     char *inputBuffer;

//     int led;
//     int mostRecentUnreadMessage;
//     int newestMessage;

//     USBSerialReceiver()
//     {
//         inputBuffer = (char *)malloc(numChars);

//         led = 13; //TODO get rid of test output led code
//         pinMode(led, OUTPUT);
//         Serial.print("making a serial");
//     }

// public:
//     bool recvWithStartEndMarkers()
//     {

//         static boolean recvInProgress = false;
//         static byte ndx = 0;
//         char startMarker = '<';
//         char endMarker = '>';
//         char rc;

//         while (Serial.available() > 0)
//         {
//             digitalWrite(led, HIGH);
//             rc = Serial.read();
//             //Serial.println(rc);//<--prints raw input stream to serial interface, use for bugtesting
            
//             if (recvInProgress == true)
//             {
//                 if (rc != endMarker)
//                 {

//                     inputBuffer[ndx] = rc;
//                     ndx++;
//                     if (ndx >= numChars)
//                     {
//                         ndx = numChars - 1;
//                     }
//                 }
//                 else
//                 {
//                     inputBuffer[ndx] = '\0'; // terminate the string
//                     recvInProgress = false;
//                     ndx = 0;

//                     outputQueue.push(inputBuffer);
//                     inputBuffer = (char *)malloc(numChars);
//                 }
//             }

//             else if (rc == startMarker)
//             {

//                 recvInProgress = true;
//             }
//         }

//         return hasMessages();
//         digitalWrite(led, LOW);
//     }

//     bool hasMessages()
//     {
//         return !outputQueue.empty();
//     }

//     bool getNextMessage(char *readLocation)
//     {

//         bool readMessage = false;

//         if (!outputQueue.empty())
//         {
//             readMessage = true;
//             char *messageLocation = outputQueue.front();
//             outputQueue.pop();

//             strcpy(readLocation, messageLocation);
//             free(messageLocation);
//         }

//         return readMessage;
//     }
// };