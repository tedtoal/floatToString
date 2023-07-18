/*
  floatToString.h - A function to convert a floating point value f into a string
  S (of size n) with digitsAfterDP digits after the decimal point, with least
  significant digit rounded appropriately.
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
#ifndef floatToString_h
#define floatToString_h

#include <Arduino.h>

/**************************************************************************/
/*!
  @brief    Convert float value to a string.
  @param    f               Floating point value to convert.
  @param    S               Buffer large enough to hold result string with nul.
  @param    n               sizeof(S).
  @param    digitsAfterDP   Number of digits to include after the decimal point,
                            can be negative to make digits before the decimal
                            point be 0, e.g. -1 means first digit before is 0.
  @returns                  S.
  @note     If the resulting string is longer than n-1 characters, the remaining
            characters are discarded and not stored in S.
  @note     In many architectures, a float value is a 4-byte value with a 23-bit
            mantissa, which is good for accurately representing 5 to 6
            significant digits.
*/
/**************************************************************************/
extern char* floatToString(float f, char* S, size_t n, int digitsAfterDP);

#endif // floatToString_h
