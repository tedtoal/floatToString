/*
  floatToString.cpp - A function to convert a floating point value f into a
  string S (of size n) with digitsAfterDP digits after the decimal point, with
  least significant digit rounded appropriately.
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
#include <stdlib.h>
#include <stdio.h>
#include "floatToString.h"

char* floatToString(float f, char* S, size_t n, int digitsAfterDP) {
  if (digitsAfterDP == 0)
    snprintf(S, n, "%d", (int) (f + (f < 0 ? -0.5 : 0.5)));
  else if (digitsAfterDP < 0) {
    int i;
    for (i = 0; i < -digitsAfterDP && abs(f) >= 10; i++) f /= 10;
    char fmt[10]; // "%d%02d"
    sprintf(fmt, "%%d%%0%dd", i);
    snprintf(S, n, fmt, (int) (f + (f < 0 ? -0.5 : 0.5)), 0);
  } else {
    int M = (int) f;
    f = abs(f - (float) M);
    for (int i = digitsAfterDP; i > 0; i--) f *= 10;
    int E = (int) (f + 0.5);
    char fmt[10]; // "%d.%05d"
    sprintf(fmt, "%%d.%%0%dd", digitsAfterDP);
    snprintf(S, n, fmt, M, E);
  }
  return(S);
}

// -------------------------------------------------------------------------
