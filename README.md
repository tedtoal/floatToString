# floatToString

## Library for converting float values to strings

This library provides a C code function named floatToString() that converts a float (floating point) value to a string with specified number digits after the decimal point. It rounds the value to the nearest least significant digit.
This library makes it easy to use printf()-style function calls in your Arduino C++ code to print messages to the Arduino IDE serial monitor window or to other serial ports.

## Usage

Here is sample code showing how to use the `floatToString()` function. It uses the `monitor_printf` library also to printf to the serial monitor window.

```
#include <floatToString.h>
#include <monitor_printf.h>

void setup() {
  monitor.begin(&Serial, 115200);
  for (int digitsAfterDP = -1; digitsAfterDP <= 6; digitsAfterDP++) {
    char S[15];
    float pi = 3.141592654;
    floatToString(pi, S, sizeof(S), digitsAfterDP)
    monitor.printf("Pi is %s (rounded to %d digits after the decimal point)\n",
      S, digitsAfterDP);
  }
}

void loop() {
  delay(100);
}
```

The `floatToString()` function has this declaration:

```
char* floatToString(float f, char* S, size_t n, int digitsAfterDP);
```

The argument `f` is the float value to convert to a string, `S` is a character buffer big enough to hold the result, `n` is simply `sizeof(S)`, and `digitsAfterDP` is the number of digits you want after the decimal place. It can be 0 for no digits after the dp, and it can even be negative. For example, -2 means that the last two digits just left of the decimal point are to be 0 after rounding the next digit up (and the number must be at >99 or < -99). 

The function returns the value of `S`, which allows a call to the function to be used as an argument to a function, such as for a printf %s-specifier's value.

Note: In many architectures, a float value is a 4-byte value with a 23-bit mantissa, which is good for accurately representing 5 to 6 significant digits.

## Contact

If you find a problem, please submit an issue report [here](https://github.com/tedtoal/floatToString/issues/new/choose).

You can contact me (the author) at [ted@tedtoal.net](ted@tedtoal.net)
