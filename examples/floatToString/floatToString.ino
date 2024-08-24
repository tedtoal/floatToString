/*
  floatToString.ino - A program to test floatToString() and show how to use it.
  Created by Ted Toal, July 17, 2023.
  Released into the public domain.


  Software License Agreement (BSD License)

  Copyright (c) 2023 Ted Toal
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
  1. Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.
  2. Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.
  3. Neither the name of the copyright holders nor the
  names of its contributors may be used to endorse or promote products
  derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <Arduino.h>
#include <floatToString.h>
#include <monitor_printf.h>

void setup() {
  monitor.begin(&Serial, 115200);
  monitor.printf("Hello floating world!\n");
  monitor.printf("sizeof(float) = %d\n", sizeof(float));
  monitor.printf("A 4-byte 32-bit float has 23 bits of mantissa\n");
  monitor.printf("23 bits is good for representing about 6 to 7 significant digits accurately.\n");
  monitor.printf("Print 182.7364 with different # digits after dp:\n");
  float f = 182.7364;
  char S[15];
  for (int j = 0; j < 2; j++) {
  monitor.printf("   4 digits after dp: %s\n", floatToString(f, S, sizeof(S), 4));
  monitor.printf("   3 digits after dp: %s\n", floatToString(f, S, sizeof(S), 3));
  monitor.printf("   2 digits after dp: %s\n", floatToString(f, S, sizeof(S), 2));
  monitor.printf("   1 digits after dp: %s\n", floatToString(f, S, sizeof(S), 1));
  monitor.printf("   0 digits after dp: %s\n", floatToString(f, S, sizeof(S), 0));
  monitor.printf("   -1 digits after dp: %s\n", floatToString(f, S, sizeof(S), -1));
  monitor.printf("   -2 digits after dp: %s\n", floatToString(f, S, sizeof(S), -2));
  monitor.printf("   -3 digits after dp: %s\n", floatToString(f, S, sizeof(S), -3));
  monitor.printf("\n");
  f = -f;
  if (j == 0)
    monitor.printf("Now print -182.7364 with different # digits after dp:\n");
  }
  monitor.printf("Pi is equated to 3.141592654 here\n");
  monitor.printf("Expect inaccuracy beyond the 5th or 6th decimal point:\n");
  float pi = 3.141592654;
  for (int digitsAfterDP = -1; digitsAfterDP <= 6; digitsAfterDP++)
    monitor.printf("Pi is %s (rounded to %d digits after the decimal point)\n",
      floatToString(pi, S, sizeof(S), digitsAfterDP), digitsAfterDP);
}

void loop() {
  delay(1000);
}
