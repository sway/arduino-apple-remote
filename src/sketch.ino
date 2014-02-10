/*
  Copyright (c) 2014 José Carlos Nieto, https://menteslibres.net/xiam

  Permission is hereby granted, free of charge, to any person obtaining
  a copy of this software and associated documentation files (the
  "Software"), to deal in the Software without restriction, including
  without limitation the rights to use, copy, modify, merge, publish,
  distribute, sublicense, and/or sell copies of the Software, and to
  permit persons to whom the Software is furnished to do so, subject to
  the following conditions:

  The above copyright notice and this permission notice shall be
  included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

// Depends on https://github.com/xiam/arduino-irdebug
#include <apple-remote.h>

#define SIGNAL_MAX_LENGTH 70

void setup() {
  Serial.begin(9600);
  Serial.println("Apple Remote for Arduino.");
}

void example_receive_signals() {
  unsigned int signal[SIGNAL_MAX_LENGTH];
  bool captured;
  int code;

  captured = irdebug_capture_signal(signal, SIGNAL_MAX_LENGTH);

  if (captured) {
    irdebug_print_signal(signal);
    code = apple_remote_match(signal);

    switch (code) {
      case APPLE_REMOTE_MENU:
        Serial.println("[menu]");
        break;
      case APPLE_REMOTE_RIGHT:
        Serial.println("[right]");
        break;
      case APPLE_REMOTE_LEFT:
        Serial.println("[left]");
        break;
      case APPLE_REMOTE_UP:
        Serial.println("[up]");
        break;
      case APPLE_REMOTE_DOWN:
        Serial.println("[down]");
        break;
      case APPLE_REMOTE_PLAY:
        Serial.println("[play]");
        break;
      case APPLE_REMOTE_CENTER:
        Serial.println("[center]");
        break;
      case APPLE_REMOTE_REPEAT:
        Serial.println("[repeat]");
        break;
      default:
        Serial.println("[?]");
    }
  }
}

void example_emit_signals() {

  // Getting to the main menu.
  Serial.println("Sending signal: menu.");
  apple_remote_menu();
  delay(100);

  // Sending repeat code to scalate to the main menu.
  Serial.println("Sending signal: repeat.");
  apple_remote_repeat();
  delay(100);
  apple_remote_repeat();
  delay(100);
  apple_remote_repeat();

  delay(2000);

  // Entering "movies"

  Serial.println("Sending signal: center.");
  apple_remote_center();
  delay(2000);

  // Top-paid first movie.
  Serial.println("Sending signal: down.");
  apple_remote_down();
  delay(2000);

  // Selecting movie.
  Serial.println("Sending signal: center.");
  apple_remote_center();
  delay(2000);

  // Lanching preview.
  Serial.println("Sending signal: play.");
  apple_remote_play();
  delay(10000);

  // Pausing preview.
  Serial.println("Sending signal: play.");
  apple_remote_play();
  delay(2000);

  // Resuming preview.
  Serial.println("Sending signal: play.");
  apple_remote_play();
  delay(5000);

  // Ok, going up again.
  Serial.println("Sending signal: menu.");
  apple_remote_menu();
  delay(2000);

  // Moving right, rent ot buy it?
  Serial.println("Sending signal: right.");
  apple_remote_right();
  delay(2000);

  // Nope, just playing.
  Serial.println("Sending signal: left.");
  apple_remote_left();
  delay(2000);

  Serial.println("Sending signal: down.");
  apple_remote_down();
  delay(2000);

  Serial.println("Sending signal: up.");
  apple_remote_up();
  delay(2000);

  Serial.println("Sending signal: play.");
  apple_remote_play();
  delay(10000);

  Serial.println("Waiting a minute.");

  delay(10000);
}

void loop() {
  // This example receives and decodes Apple Remote signals.
  example_receive_signals();

  // This example emits Apple Remote codes to an AppleTV receiver.
  //example_emit_signals();
}
