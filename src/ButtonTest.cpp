#include <Arduino.h>
#include <Button.h>
#include <vector>

using namespace std;

vector<Button> buttons;
void setup()
{
	Serial.begin(115200);
	for (int i = 0; i < 32; i++)
	{
		buttons.push_back(Button(i));
	}
}

void loop()
{
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i].poll();
		if (buttons[i].isDepressing())
		{
			Serial.println(i);
		}
	}
	delay(1000);
}
