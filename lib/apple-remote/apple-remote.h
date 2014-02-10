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

/*
 * See:
 *  https://github.com/xiam/arduino-irdebug
 *  http://techdocs.altium.com/display/ADRR/NEC+Infrared+Transmission+Protocol
 *  http://en.wikipedia.org/wiki/Apple_Remote
* */

#include <irdebug.h>

#define APPLE_REMOTE_LEADER     9000, 4500  // 9ms mark + 4.5ms space
#define APPLE_REMOTE_B0         560,  560   // 560us mark + 560us space
#define APPLE_REMOTE_B1         560,  1690  // 560us mark + 1.69ms space
#define APPLE_REMOTE_STOP       560,  0     // 560us mark + stop
#define APPLE_REMOTE_RELEADER   9000, 2250  // 9ms mark + 2.25ms space

#define APPLE_REMOTE_H0         APPLE_REMOTE_B0, APPLE_REMOTE_B0, APPLE_REMOTE_B0, APPLE_REMOTE_B0  // 0x00
#define APPLE_REMOTE_H1         APPLE_REMOTE_B1, APPLE_REMOTE_B0, APPLE_REMOTE_B0, APPLE_REMOTE_B0  // 0x01
#define APPLE_REMOTE_H2         APPLE_REMOTE_B0, APPLE_REMOTE_B1, APPLE_REMOTE_B0, APPLE_REMOTE_B0  // 0x02
#define APPLE_REMOTE_H3         APPLE_REMOTE_B1, APPLE_REMOTE_B1, APPLE_REMOTE_B0, APPLE_REMOTE_B0  // 0x03
#define APPLE_REMOTE_H4         APPLE_REMOTE_B0, APPLE_REMOTE_B0, APPLE_REMOTE_B1, APPLE_REMOTE_B0  // 0x04
#define APPLE_REMOTE_H5         APPLE_REMOTE_B1, APPLE_REMOTE_B0, APPLE_REMOTE_B1, APPLE_REMOTE_B0  // 0x05
#define APPLE_REMOTE_H6         APPLE_REMOTE_B0, APPLE_REMOTE_B1, APPLE_REMOTE_B1, APPLE_REMOTE_B0  // 0x06
#define APPLE_REMOTE_H7         APPLE_REMOTE_B1, APPLE_REMOTE_B1, APPLE_REMOTE_B1, APPLE_REMOTE_B0  // 0x07
#define APPLE_REMOTE_H8         APPLE_REMOTE_B0, APPLE_REMOTE_B0, APPLE_REMOTE_B0, APPLE_REMOTE_B1  // 0x08
#define APPLE_REMOTE_H9         APPLE_REMOTE_B1, APPLE_REMOTE_B0, APPLE_REMOTE_B0, APPLE_REMOTE_B1  // 0x09
#define APPLE_REMOTE_HA         APPLE_REMOTE_B0, APPLE_REMOTE_B1, APPLE_REMOTE_B0, APPLE_REMOTE_B1  // 0x0A
#define APPLE_REMOTE_HB         APPLE_REMOTE_B1, APPLE_REMOTE_B1, APPLE_REMOTE_B0, APPLE_REMOTE_B1  // 0x0B
#define APPLE_REMOTE_HC         APPLE_REMOTE_B0, APPLE_REMOTE_B0, APPLE_REMOTE_B1, APPLE_REMOTE_B1  // 0x0C
#define APPLE_REMOTE_HD         APPLE_REMOTE_B1, APPLE_REMOTE_B0, APPLE_REMOTE_B1, APPLE_REMOTE_B1  // 0x0D
#define APPLE_REMOTE_HE         APPLE_REMOTE_B0, APPLE_REMOTE_B1, APPLE_REMOTE_B1, APPLE_REMOTE_B1  // 0x0E
#define APPLE_REMOTE_HF         APPLE_REMOTE_B1, APPLE_REMOTE_B1, APPLE_REMOTE_B1, APPLE_REMOTE_B1  // 0x0F

#define APPLE_CUSTOM_CODE       APPLE_REMOTE_HE, APPLE_REMOTE_HE, APPLE_REMOTE_H7, APPLE_REMOTE_H8  // 0xEE, 0X87

#define APPLE_REMOTE_MODEL      0xcf

#if APPLE_REMOTE_MODEL == 0xcf
  #define APPLE_REMOTE_ID               APPLE_REMOTE_HF, APPLE_REMOTE_HC          // 0xCF
  #define APPLE_REMOTE_BUTTON_MENU      APPLE_REMOTE_H2, APPLE_REMOTE_H0          // 0x02
  #define APPLE_REMOTE_BUTTON_RIGHT     APPLE_REMOTE_H7, APPLE_REMOTE_H0          // 0x07
  #define APPLE_REMOTE_BUTTON_LEFT      APPLE_REMOTE_H8, APPLE_REMOTE_H0          // 0x08
  #define APPLE_REMOTE_BUTTON_UP        APPLE_REMOTE_HB, APPLE_REMOTE_H0          // 0x0B
  #define APPLE_REMOTE_BUTTON_DOWN      APPLE_REMOTE_HD, APPLE_REMOTE_H0          // 0x0D
  #define APPLE_REMOTE_BUTTON_PLAY      APPLE_REMOTE_HE, APPLE_REMOTE_H5          // 0x5E
  #define APPLE_REMOTE_BUTTON_CENTER    APPLE_REMOTE_HD, APPLE_REMOTE_H5          // 0x5D
#elif APPLE_REMOTE_MODEL == 0xa7
  #define APPLE_REMOTE_ID               APPLE_REMOTE_H7, APPLE_REMOTE_HA          // 0xA7
  #define APPLE_REMOTE_BUTTON_MENU      APPLE_REMOTE_H3, APPLE_REMOTE_H0          // 0x03
  #define APPLE_REMOTE_BUTTON_RIGHT     APPLE_REMOTE_H6, APPLE_REMOTE_H0          // 0x06
  #define APPLE_REMOTE_BUTTON_LEFT      APPLE_REMOTE_H9, APPLE_REMOTE_H0          // 0x09
  #define APPLE_REMOTE_BUTTON_UP        APPLE_REMOTE_HA, APPLE_REMOTE_H0          // 0x0A
  #define APPLE_REMOTE_BUTTON_DOWN      APPLE_REMOTE_HC, APPLE_REMOTE_H0          // 0x0C
  #define APPLE_REMOTE_BUTTON_PLAY      APPLE_REMOTE_HF, APPLE_REMOTE_H5          // 0x5F
  #define APPLE_REMOTE_BUTTON_CENTER    APPLE_REMOTE_HC, APPLE_REMOTE_H5          // 0x5C
#endif

#define APPLE_REMOTE_SIGNAL(code) {APPLE_REMOTE_LEADER, APPLE_CUSTOM_CODE, code, APPLE_REMOTE_ID, APPLE_REMOTE_STOP }

#define APPLE_REMOTE_MENU   0
#define APPLE_REMOTE_RIGHT  1
#define APPLE_REMOTE_LEFT   2
#define APPLE_REMOTE_UP     3
#define APPLE_REMOTE_DOWN   4
#define APPLE_REMOTE_PLAY   5
#define APPLE_REMOTE_CENTER 6
#define APPLE_REMOTE_REPEAT 7

#define APPLE_REMOTE_SIGNALS (APPLE_REMOTE_REPEAT + 1)

#define APPLE_REMOTE_KHZ    38

static unsigned int apple_remote_signal[APPLE_REMOTE_SIGNALS][68] = {
  APPLE_REMOTE_SIGNAL(APPLE_REMOTE_BUTTON_MENU),
  APPLE_REMOTE_SIGNAL(APPLE_REMOTE_BUTTON_RIGHT),
  APPLE_REMOTE_SIGNAL(APPLE_REMOTE_BUTTON_LEFT),
  APPLE_REMOTE_SIGNAL(APPLE_REMOTE_BUTTON_UP),
  APPLE_REMOTE_SIGNAL(APPLE_REMOTE_BUTTON_DOWN),
  APPLE_REMOTE_SIGNAL(APPLE_REMOTE_BUTTON_PLAY),
  APPLE_REMOTE_SIGNAL(APPLE_REMOTE_BUTTON_CENTER),
  {APPLE_REMOTE_RELEADER, APPLE_REMOTE_STOP},
};

void apple_remote_send(int code) {
  irdebug_send(apple_remote_signal[code], APPLE_REMOTE_KHZ);
}

void apple_remote_menu() {
  apple_remote_send(APPLE_REMOTE_MENU);
}

void apple_remote_right() {
  apple_remote_send(APPLE_REMOTE_RIGHT);
}

void apple_remote_left() {
  apple_remote_send(APPLE_REMOTE_LEFT);
}

void apple_remote_up() {
  apple_remote_send(APPLE_REMOTE_UP);
}

void apple_remote_down() {
  apple_remote_send(APPLE_REMOTE_DOWN);
}

void apple_remote_play() {
  apple_remote_send(APPLE_REMOTE_PLAY);
}

void apple_remote_center() {
  apple_remote_send(APPLE_REMOTE_CENTER);
}

void apple_remote_repeat() {
  apple_remote_send(APPLE_REMOTE_REPEAT);
}

int apple_remote_match(unsigned int *signal) {
  int i;
  for (i = 0; i < APPLE_REMOTE_SIGNALS; i++) {
    if (irdebug_match_signal(apple_remote_signal[i], signal, 280) == true) {
      return i;
    }
  };
  return -1;
}
