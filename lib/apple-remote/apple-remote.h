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

#define APPLE_REMOTE_LEADER    9000, 4500  // 9ms mark + 4.5ms space
#define APPLE_REMOTE_B0        560,  560   // 560us mark + 560us space
#define APPLE_REMOTE_B1        560,  1690  // 560us mark + 1.69ms space
#define APPLE_REMOTE_STOP      560,  0     // 560us mark + stop
#define APPLE_REMOTE_REPEAT    9000, 2250  // 9ms mark + 2.25ms space

#define APPLE_REMOTE_H0    APPLE_REMOTE_B0, APPLE_REMOTE_B0, APPLE_REMOTE_B0, APPLE_REMOTE_B0  // 0x00
#define APPLE_REMOTE_H1    APPLE_REMOTE_B1, APPLE_REMOTE_B0, APPLE_REMOTE_B0, APPLE_REMOTE_B0  // 0x01
#define APPLE_REMOTE_H2    APPLE_REMOTE_B0, APPLE_REMOTE_B1, APPLE_REMOTE_B0, APPLE_REMOTE_B0  // 0x02
#define APPLE_REMOTE_H3    APPLE_REMOTE_B1, APPLE_REMOTE_B1, APPLE_REMOTE_B0, APPLE_REMOTE_B0  // 0x03
#define APPLE_REMOTE_H4    APPLE_REMOTE_B0, APPLE_REMOTE_B0, APPLE_REMOTE_B1, APPLE_REMOTE_B0  // 0x04
#define APPLE_REMOTE_H5    APPLE_REMOTE_B1, APPLE_REMOTE_B0, APPLE_REMOTE_B1, APPLE_REMOTE_B0  // 0x05
#define APPLE_REMOTE_H6    APPLE_REMOTE_B0, APPLE_REMOTE_B1, APPLE_REMOTE_B1, APPLE_REMOTE_B0  // 0x06
#define APPLE_REMOTE_H7    APPLE_REMOTE_B1, APPLE_REMOTE_B1, APPLE_REMOTE_B1, APPLE_REMOTE_B0  // 0x07
#define APPLE_REMOTE_H8    APPLE_REMOTE_B0, APPLE_REMOTE_B0, APPLE_REMOTE_B0, APPLE_REMOTE_B1  // 0x08
#define APPLE_REMOTE_H9    APPLE_REMOTE_B1, APPLE_REMOTE_B0, APPLE_REMOTE_B0, APPLE_REMOTE_B1  // 0x09
#define APPLE_REMOTE_HA    APPLE_REMOTE_B0, APPLE_REMOTE_B1, APPLE_REMOTE_B0, APPLE_REMOTE_B1  // 0x0A
#define APPLE_REMOTE_HB    APPLE_REMOTE_B1, APPLE_REMOTE_B1, APPLE_REMOTE_B0, APPLE_REMOTE_B1  // 0x0B
#define APPLE_REMOTE_HC    APPLE_REMOTE_B0, APPLE_REMOTE_B0, APPLE_REMOTE_B1, APPLE_REMOTE_B1  // 0x0C
#define APPLE_REMOTE_HD    APPLE_REMOTE_B1, APPLE_REMOTE_B0, APPLE_REMOTE_B1, APPLE_REMOTE_B1  // 0x0D
#define APPLE_REMOTE_HE    APPLE_REMOTE_B0, APPLE_REMOTE_B1, APPLE_REMOTE_B1, APPLE_REMOTE_B1  // 0x0E
#define APPLE_REMOTE_HF    APPLE_REMOTE_B1, APPLE_REMOTE_B1, APPLE_REMOTE_B1, APPLE_REMOTE_B1  // 0x0F

#define APPLE_CUSTOM_CODE     APPLE_REMOTE_HE, APPLE_REMOTE_HE, APPLE_REMOTE_H7, APPLE_REMOTE_H8  // 0xEE, 0X87
#define APPLE_REMOTE_ID       APPLE_REMOTE_H7, APPLE_REMOTE_HA          // 0XA7

#define APPLE_REMOTE_BUTTON_MENU     APPLE_REMOTE_H3, APPLE_REMOTE_H0          // 0x03
#define APPLE_REMOTE_BUTTON_PLAY     APPLE_REMOTE_HF, APPLE_REMOTE_H5          // 0x5F
#define APPLE_REMOTE_BUTTON_CENTER   APPLE_REMOTE_HC, APPLE_REMOTE_H5          // 0x5C
#define APPLE_REMOTE_BUTTON_UP       APPLE_REMOTE_HA, APPLE_REMOTE_H0          // 0x0A
#define APPLE_REMOTE_BUTTON_LEFT     APPLE_REMOTE_H9, APPLE_REMOTE_H0          // 0x09
#define APPLE_REMOTE_BUTTON_RIGHT    APPLE_REMOTE_H6, APPLE_REMOTE_H0          // 0x06
#define APPLE_REMOTE_BUTTON_DOWN     APPLE_REMOTE_HC, APPLE_REMOTE_H0          // 0x0C

#define APPLE_REMOTE_SIGNAL(x) {APPLE_REMOTE_LEADER, APPLE_CUSTOM_CODE, x, APPLE_REMOTE_ID, APPLE_REMOTE_STOP }

void apple_remote_menu() {
  static unsigned int signal[] = APPLE_REMOTE_SIGNAL(APPLE_REMOTE_BUTTON_MENU);
  irdebug_send(signal, 38);
}

void apple_remote_right() {
  static unsigned int signal[] = APPLE_REMOTE_SIGNAL(APPLE_REMOTE_BUTTON_RIGHT);
  irdebug_send(signal, 38);
}

void apple_remote_left() {
  static unsigned int signal[] = APPLE_REMOTE_SIGNAL(APPLE_REMOTE_BUTTON_LEFT);
  irdebug_send(signal, 38);
}

void apple_remote_up() {
  static unsigned int signal[] = APPLE_REMOTE_SIGNAL(APPLE_REMOTE_BUTTON_UP);
  irdebug_send(signal, 38);
}

void apple_remote_down() {
  static unsigned int signal[] = APPLE_REMOTE_SIGNAL(APPLE_REMOTE_BUTTON_DOWN);
  irdebug_send(signal, 38);
}

void apple_remote_play() {
  static unsigned int signal[] = APPLE_REMOTE_SIGNAL(APPLE_REMOTE_BUTTON_PLAY);
  irdebug_send(signal, 38);
}

void apple_remote_center() {
  static unsigned int signal[] = APPLE_REMOTE_SIGNAL(APPLE_REMOTE_BUTTON_CENTER);
  irdebug_send(signal, 38);
}

void apple_remote_repeat() {
  static unsigned int signal[] = {
    APPLE_REMOTE_REPEAT,
    APPLE_REMOTE_STOP
  };
  irdebug_send(signal, 38);
}

/*
// Those were the original readings found with irdebug.h.

// Menu
int signal[] = {
  9032, 4492

  532, 596
  516, 1700
  516, 1684
  552, 1688

  528, 604
  524, 1692
  528, 1704
  516, 1700

  516, 1700
  536, 1688
  528, 1688
  528, 584

  548, 600
  508, 604
  532, 596
  516, 1700

  516, 1700
  536, 1688
  528, 600
  528, 584

  528, 604
  508, 620
  516, 596
  516, 612

  516, 1700
  516, 1708
  508, 1708
  528, 600

  528, 584
  528, 604
  532, 1684
  532, 1716

  520, 0};

// play pause
int signal[] = {
  9024, 4512

  512, 608
  528, 1696
  524, 1692
  524, 1712

  508, 616
  512, 1704
  532, 1688
  528, 1696

  524, 1712
  504, 1712
  524, 1696
  528, 592

  528, 592
  532, 588
  532, 592
  528, 1696

  540, 1660
  540, 1712
  544, 1676
  548, 1668

  548, 1672
  548, 580
  540, 1676
  540, 584

  540, 1676
  548, 1688
  548, 1668
  548, 576

  548, 580
  540, 580
  540, 1676
  544, 1692

  548, 0};

// Center
int signal[] = {
  9104, 4436

  592, 528
  592, 1628
  596, 1620
  600, 1636

  600, 512
  608, 1628
  592, 1624
  592, 1628

  600, 1616
  616, 1608
  600, 1632
  612, 476

  628, 528
  592, 528
  612, 516
  600, 1620

  596, 524
  580, 540
  672, 1548
  600, 1624

  612, 1608
  680, 424
  608, 1644
  668, 452

  584, 1636
  616, 1608
  700, 1520
  592, 528

  612, 512
  608, 512
  600, 1620
  596, 1656

  580, 0};

// Up
int signal[] = {
  9084, 4432

  628, 492
  616, 1608
  600, 1636
  600, 1584

  668, 476
  592, 1644
  576, 1644
  592, 1624

  600, 1620
  600, 1616
  620, 1608
  732, 404

  596, 512
  608, 512
  612, 508
  620, 1600

  616, 504
  600, 1636
  584, 520
  620, 1608

  592, 528
  680, 440
  612, 492
  628, 496

  704, 1548
  600, 1620
  600, 1624
  576, 544

  596, 528
  592, 528
  592, 1628
  596, 1636

  600, 0};


// Left
int signal[] = {
  9092, 4428

  600, 528
  600, 1620
  600, 1620
  600, 1628

  596, 512
  612, 1624
  592, 1632
  600, 1620

  600, 1624
  596, 1620
  600, 1624
  612, 512

  592, 528
  592, 528
  600, 524
  580, 1644

  596, 1628
  580, 540
  600, 528
  592, 1624

  596, 528
  592, 492
  636, 524
  596, 488

  636, 1616
  600, 1620
  600, 1624
  612, 512

  608, 512
  612, 508
  596, 1624
  616, 1636

  584, 0};

// Right
int signal[] = {
  9092, 4428

  600, 528
  600, 1624
  600, 1608
  596, 1628

  612, 508
  596, 1628
  600, 1624
  584, 1640

  600, 1612
  592, 1632
  592, 1632
  608, 512

  600, 524
  564, 544
  600, 524
  616, 1600

  616, 512
  596, 1632
  592, 1624
  596, 528

  600, 524
  600, 520
  600, 524
  596, 492

  636, 1604
  616, 1612
  596, 1628
  612, 512

  600, 520
  584, 524
  600, 1624
  600, 1640

  600, 0};

// Down

int signal[] = {
  9108, 4416

  608, 512
  596, 1640
  592, 1628
  600, 1616

  600, 524
  616, 1600
  600, 1624
  612, 1624

  576, 1644
  600, 1620
  596, 1620
  600, 520

  600, 528
  596, 528
  592, 496
  624, 1628

  652, 468
  600, 504
  616, 1620
  600, 1620

  616, 504
  600, 528
  612, 508
  596, 528

  608, 1608
  600, 1636
  584, 1636
  580, 544

  584, 520
  620, 508
  596, 1608
  644, 1624

  584, 0};

// Repeat

int signal[] = {
  9064, 2204
  612, 0};


*/
