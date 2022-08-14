# arcade-of-light
LED light strip based project for Blink 2019

# Setup
Dev setup to run/develop arcade of light.  There could be some things missing since we switched to PlatformIO halfway through the project. Please update if there are any additional setup steps. 

## IDE
Not totally sure if this is neccessary, but I'm like 90% sure you'll need to download Arduino and Arduino IDE for some reason. https://www.arduino.cc/en/Main/Software

Visual Studio with PlatformIO <br>
https://code.visualstudio.com/Download <br>
https://platformio.org/platformio-ide


## Libraries
Once PlatformIO is installed, you will need the following libraries:<br>
* FastLED - the most important one to know: https://github.com/FastLED/FastLED/wiki/Basic-usage
* Audio by Paul Stoffregen <br>
* SerialFlash also by Paul Stoffregen <br>

## Platform
Teensy, just go to Platform and install Teensy Platform.  For anythig specific to Teensy models, we are using Teensy 3.6.

## Serial Monitor
You probably want to be able to write logs and stuff for debugging.
Add the .platformio/scripts folder to your PATH. The .platformio folder should be in your C://user/{username} folder.  Serial Monitor should work now but I dont know i kind of forget pls update if you can confirm

# Project Structure
Ardiuno files consist of two methods: setup() and loop(). The setup method runs once when the program starts running.  Loop then loops infinitely until power is cut off.  This main file is in src/main.cpp.  All other classes are imported through .h header files. 

The four main classes are detailed in the next section, but in summary:
The game class holds all subclasses, logic, and states.  To initialize, it requires a Display object, which hold an array (or array of arrays) of CRGB objects.  The game takes in inputs from a Controls object and the draws them to the Display object using Animation objects.  Finally, display->Show() is called at the end of each loop to write to the LED strips.

Controls and animations are kept within their respective class folders, so that we can reuse them between different games.  Feel free to keep all your stuff in a specific folder though, PlatformIO lets you just do an include on any .h file in the library, just make sure not to reuse names.

# Classes
Each Game Requires the following classes:<br>
<details>
  <summary>1. Game</summary>

  ## Game Class 
  Holds all Game specific objects, subclasses, logic and game states, as well as method for setup and loop
  * Location: lib/games/game.h
  * Required Methods/ Members:
    * constructor - constructor is required to take in a display object
    * background -  Animation object for background
    * display - Display object for LED strip setup game will be running on
    * setup() - Method to run in the setup loop
    * loop() - Method to run in the main loop
</details>
<details>
  <summary>2. Display</summary>

  ## Display Class 
  Holds all LED strips as an array of arrays.  These are built and likely won't need much editing.
  * Location: lib/Displays/Display.h
  * Required Methods/ Members:
    * strip_count - number of strips, i.e. width of matrix
    * strip_length - how long the strips are
    * strips - Array of Arrays generated by NumStrips and strip_length
</details>
<details>
  <summary>3. Animation</summary>

  ## Animation Class 
  Draws animations to a display object
  * Location: lib/Animations/Animation.h
  * Required Methods/ Members:
    * drawy(display) - writes animation to a display
</details>
<details>
  <summary>4. Controls</summary>

  ## Controls Class 
  The wild child of the main classes.  Holds all Buttons/ Controllers, you can kinda do whatever with these but should all be set up. Does _not_ need to inheret from base Controls class.  Basically take what you want from the control library folder and Frankenstein yourself some controls.
  * Location: lib/Controls/Controls.h
  * Required Methods/ Members:
    * none, but you probably want like at least a button or something
  * Important Button Methods
    * 
</details>

