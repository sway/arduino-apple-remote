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

// The following include depends on https://github.com/xiam/arduino-irdebug
#include <apple-remote.h>

void setup()
{
  Serial.begin(9600);
  Serial.println("This library makes a IR LED emit codes used by the Apple Remote.");
}

void loop()
{

  // This example uses an Apple TV receiver.

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
