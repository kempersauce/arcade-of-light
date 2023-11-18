/* MIDI Input Test - for use with Teensy or boards where Serial is separate from MIDI
 * As MIDI messages arrive, they are printed to the Arduino Serial Monitor.
 *
 * Where MIDI is on "Serial", eg Arduino Duemilanove or Arduino Uno, this does not work!
 *
 * This example code is released into the public domain.
 */
 
#include <MIDI.h>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial4, MIDI);

void setup() {
  MIDI.begin(MIDI_CHANNEL_OMNI);
  Serial.begin(57600);
  Serial.println("MIDI SEND TEST");
}

unsigned long t=0;

void playMidiNote(int channel, int note, int velocity, int note_on_length, int note_off_length) {
  Serial.println(String("Note On: ch=") + channel + ", note=" + note + ", velocity=" + velocity);
  MIDI.sendNoteOn(note, velocity, channel);
  delay(note_on_length);
  Serial.println(String("Note Off: ch=") + channel + ", note=" + note + ", velocity=" + velocity);
  MIDI.sendNoteOff(note, velocity, channel);
  delay(note_off_length);
}

void loop() {
  int type, note, note1, note2, velocity, channel, d1, d2;
  note = 48;
  velocity = 70;
  channel = 1;
  note1 = 52;
  note2 = 55;
  int note_on_length = 100;
  int note_off_length = 200;


  
  playMidiNote(1, 48, 70, note_on_length, note_off_length);
  playMidiNote(1, 52, 50, note_on_length, note_off_length);
  playMidiNote(1, 55, 50, note_on_length, note_off_length);
  playMidiNote(1, 59, 50, note_on_length, note_off_length);
  playMidiNote(1, 60, 50, note_on_length, note_off_length);
  playMidiNote(1, 59, 50, note_on_length, note_off_length);
  playMidiNote(1, 55, 50, note_on_length, note_off_length);
  playMidiNote(1, 52, 50, note_on_length, note_off_length);
  
}