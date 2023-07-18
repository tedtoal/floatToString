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
  delay(100);
}
