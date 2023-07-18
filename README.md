# floatToString

## Library for converting float values to strings

This library provides a C code function named floatToString() that converts a float (floating point) value to a string with specified number digits after the decimal point. It rounds the value to the nearest least significant digit.
This library makes it easy to use printf()-style function calls in your Arduino C++ code to print messages to the Arduino IDE serial monitor window or to other serial ports.

## Usage

Here is sample code showing how to use the function:

```
#include <monitor_printf.h>

// Set this to 1 to enable debug output to the serial monitor.
// Set this to 0 when releasing code to use without the IDE, USB port, and serial monitor.
#define USE_MONITOR_PORT 1

// Define the port to be used by the global instance named "the_serial_monitor".
#if USE_MONITOR_PORT
#define MONITOR_PORT &Serial  // Enable printf output to the serial monitor port identified by variable "Serial".
#else
#define MONITOR_PORT NULL     // Disable printf output when using WITHOUT the IDE, USB port, and serial monitor.
#endif

void setup() {
  monitor.begin(MONITOR_PORT, 115200);
  monitor.printf("MyProgram is running\n");
}
```

## Basics

The library consists of a .cpp/.h file pair that define a C++ class named `monitor_printf` whose member functions are used to initialize a serial port for printf output and to perform printfs to the port.

### Include file

To use the library, include the library header file in your code file:

```
  #include <monitor_printf.h>
```

This #include creates one global instance of the `monitor_printf` class, named **`the_monitor_printf`**. It

It also #defines the symbol **`monitor`** to equal `the_monitor_printf`. Either `the_monitor_printf` or `monitor` can be used to call `monitor_printf` member functions to do printfs to the serial monitor. For example:

```
  monitor.printf("Hello world!\n");  // ** preferred **

  the_monitor_printf.printf("Hello world!\n"); // ** optional **
```

Since `monitor` might possibly already be used elsewhere in your code, a method is provided to not define it. Simply define the symbol `DONT_DEFINE_monitor` before including the library header file, and then optionally #define a different short symbol name to use to do printfs:

```
// Skip defining 'monitor'.
#define DONT_DEFINE_monitor
#include <monitor_printf.h>

// Define something shorter than 'the_monitor_printf' to use, so we can do mon.printf(...);
#define mon the_monitor_printf
```

### Choosing a serial port OR no output

After the #include, it is recommended that you #define symbol USE_MONITOR_PORT equal to 1 when running the code with the IDE and serial monitor window, and to 0 when running it with no IDE, no USB port, and no serial monitor. After that #define, you should add a #if USE_MONITOR_PORT, and when it is 1, #define MONITOR_PORT to the address of the HardwareSerial variable for the serial port to be used (usually **`&Serial`**), then after a #else, #define it as NULL, with a final #endif. For example:

```
// Set this to 1 to enable debug output to the serial monitor.
// Set this to 0 when releasing code to use without the IDE, USB port, and serial monitor.
#define USE_MONITOR_PORT 1

// Define the port to be used by the global instance named "the_serial_monitor".
#if USE_MONITOR_PORT
#define MONITOR_PORT &Serial  // Enable printf output to the serial monitor port identified by variable "Serial".
#else
#define MONITOR_PORT NULL     // Disable printf output when using WITHOUT the IDE, USB port, and serial monitor.
#endif
```

The value **`MONITOR_PORT`** is used in the call to the monitor_printf `begin()` member function to properly initialize the object for running with or without the serial monitor.

**It is necessary to change the #define USE_MONITOR_PORT each time you switch between running with the Arduino IDE and serial monitor (defined as 1), versus without it (defined as 0).** The above example shows USE_MONITOR_PORT set to 1 for running with the IDE and serial monitor. When you change it to 0, this causes printf() calls to do nothing. You don't need to remove the printf calls from your code.

### Call member function `begin()` to initialize

The `monitor_printf` member function **`begin()`** initializes the class instance for printing, including initialization of the HardwareSerial object that communicates with the serial monitor window. Alternatively, `begin()` can disable the `printf()` function, used when running code without the USB port and IDE monitor window.

The `begin()` function MUST be called to initialize before printing, usually as the first thing in the **`setup()`** function. It has several arguments, all optional:

```
void begin(HardwareSerial* serial = NULL, unsigned long baud = 115200, byte config = SERIAL_8N1);
```

The first argument, **`serial`**, is normally set to **`MONITOR_PORT`**, the #define described above. This causes `serial` to be **`&Serial`** when running with the USB port connected to the Arduino IDE, or to be **`NULL`** when running without the serial port and IDE.

The second and third arguments, **`baud`** and **`config`**, are only used by `begin()` when `MONITOR_PORT` is *not* NULL. In that case, `begin()` calls the serial port's own `begin()` function to initialize serial communications, using `baud` and `config` to set serial speed and data/parity/stop bits. You should set `baud` to the serial port speed you want to use, or omit the argument to use the default setting of 115,200 bps speed. Typically `config` is omitted to use its default of `SERIAL_8N1`.

If `MONITOR_PORT` is `NULL`, this *disables the printf() function, so when it is called it does nothing*. When you are running your code outside the Arduino IDE, with no USB port and no serial monitor, it is **crucial that `MONITOR_PORT` (and therefore the `serial` argument) be set to `NULL`**. Otherwise, your code will hang when it tries to initialize a non-existent serial port. This is why it is recommended that you define `USE_MONITOR_PORT` at the top of the file where it is easily visible to help remind you to change it whenever you switch between running with the IDE and without it, followed by a define of `MONITOR_PORT` to the appropriate value depending on how `USE_MONITOR_PORT` is set.

In summary, the call to `begin()` will typically look like this if you want to run the serial port at 9600 bps:

```
void setup() {
  monitor.begin(MONITOR_PORT, 9600);
}
```

### Call member function `printf()` to print

The `monitor_printf` member function **`printf()`** prints a character string to the serial monitor window, using a standard printf-style format string to control the formatting of the text, and with optional arguments that contain values to be printed or are arguments used by format string "% specifiers".

The ``printf()`` member function uses an internal C++ library function (``vsnprintf()``) to format your text string for output. It uses the ``format`` argument you specify, plus any additional arguments that follow it as needed to process the printf() "%-specifiers".

Here is an example that includes both the initialization call to `begin()` and two calls to `printf()`:

```
void setup() {
  monitor.begin(MONITOR_PORT, 9600);
  monitor.printf("MyProgram is running\n");
}

void loop() {

int x = 123;
long Z = 123456789;
char c = 'A';
char* p = "Goodbye";

monitor.printf("Value of x: %d   Z: %ld   c: %c   p: %s\n", x, Z, c, p);
delay(1000);
```

The first call to `printf()` inside the `setup()` function shows a simple printf call to print a string followed by a newline character to start a new line on the serial monitor.

The second call inside the `loop()` function is a more complex printf call that uses **%-specifiers** to print integer (%d), long integer (%ld), character (%c), and string (%s) values. The actual variables containing those values are specified as additional arguments following the format string, in the same order as they appear in the "%-specifiers".

If you don't have a good working knowledge of "%-specifiers", including features such as field width and justification, it is recommended that you look them up and study them a bit. As an example, the specifier "%-25s" prints a string left-justified (the '-' sign) in a field 25 characters wide. As another example, arguments `("%*d", K, i)` prints integer in a field whose width is given by integer K (the '*' says to look for an argument to specify the field width).

Although most standard printf() functionality should be present, I've noticed that **%u** is missing (use **`%d`** instead, not ideal but it often works for most cases).

Also, something often of great importance that is typically missing is the ability to format and print ``float`` and ``double`` values. These are apparently disabled in standard versions of Arduino libraries, but can be enabled through some mechanism that I have not yet figured out. If you need to print floating point values, you may want to use my **``floatToString``** library.

## Additional details for those interested

### Using more instances of the serial_monitor class for other serial ports

The above descriptions implied that the serial_monitor class specifically uses the `Serial` object, which is the standard serial port object used to communicate with the IDE's serial monitor window. However, the `monitor_printf` class actually allows any serial port to be used, so long as the port's variable is an instance of class `HardwareSerial` (or a class derived from it). The `HardwareSerial` class is defined in the standard Arduino library to encompass the functionality needed for a serial port, and the standard `Serial` object is an instance of the `HardwareSerial` class.

If you are using a microcomputer with hardware that supports multiple serial ports, there is a good chance that the Arduino run-time code defines a variable for each one, all derived from `HardwareSerial`. Often these variables are named `Serial1`, `Serial2`, etc. You can try putting one of those variables in your code and checking to see if the code compiles to find out if it is there or not. Right-clicking on a such a system variable within the IDE and choosing "Go to Definition" opens the file where the variable is defined, and this is often useful to see how it is defined and what class it is.

The `serial` argument to the `begin()` member function can be something other than `MONITOR_PORT`. To use a `monitor_printf` instance for doing printfs to some other serial port, you define a new instance and then call its `begin()` function, passing it the address of that port. For example, to use both the normal `monitor` variable with the serial port variable `Serial` and to use port `Serial2` with a second `monitor_printf` instance named `ser2`:

```
#include <monitor_printf.h>

// Set this to 1 to enable debug output to the serial monitor.
// Set this to 0 when releasing code to use without the IDE, USB port, and serial monitor.
#define USE_MONITOR_PORT 1

// Define the port to be used by the global instance named "the_serial_monitor".
#if USE_MONITOR_PORT
#define MONITOR_PORT &Serial  // Enable printf output to the serial monitor port identified by variable "Serial".
#else
#define MONITOR_PORT NULL     // Disable printf output when using WITHOUT the IDE, USB port, and serial monitor.
#endif

// A monitor_printf instance for using port Serial2.
monitor_printf ser2;

void setup() {
  monitor.begin(MONITOR_PORT, 115200);
  monitor.printf("MyProgram is running\n");

  ser2.begin(&Serial2, 9600);
}

void loop() {
  ...
  // Print string S to Serial2 with value i.
  ser2.printf("%s %d", S, i);
  ...
}
```

You might also want to use another serial port but **not use the serial port connected to the serial monitor window.** To NOT define the global instance variable 'the_monitor_printf', #define DONT_DEFINE_the_monitor_printf before including the library header file. You should ALSO #define DONT_DEFINE_monitor. For example:

```
// Skip defining 'monitor'.
#define DONT_DEFINE_monitor
// Skip defining 'the_monitor_printf'.
#define DONT_DEFINE_the_monitor_printf
#include <monitor_printf.h>

// A monitor_printf instance for using port Serial2.
monitor_printf ser2;

void setup() {
  ser2.begin(&Serial2, 9600);
}

void loop() {
  ...
  // Print string S to Serial2 with value i.
  ser2.printf("%s %d", S, i);
  ...
}
```

The `monitor_printf` class C++ **constructor** function has one optional argument: a pointer to the `HardwareSerial` instance to use with the port. If the argument is omitted, NULL is used and then the serial port is specified when `begin()` is called. You can use the constructor argument to specify the serial port to be used with the instance, INSTEAD OF specifying it in the `begin()` call. In that case, there are no arguments  to the `begin()` call (`serial` defaults to NULL and other arguments are not used). This is almost the same as the previous example, *except the `begin()` function skips port initialization. You must initialize the serial port yourself.* For example:

```
// Skip defining 'monitor'.
#define DONT_DEFINE_monitor
// Skip defining 'the_monitor_printf'.
#define DONT_DEFINE_the_monitor_printf
#include <monitor_printf.h>

// A monitor_printf instance for using port Serial2.
monitor_printf ser2(&Serial2);

void setup() {
  // Initialize Serial2 port.
  Serial2.begin(9600);
  // Initialize ser2 for printf to Serial2.
  ser2.begin();
}

void loop() {
  ...
  // Print string S to Serial2 with value i.
  ser2.printf("%s %d", S, i);
  ...
}
```

### Buffer size grows automatically or is changed with `setBufSize()`

The ``printf()`` member function formats the string to be output into a buffer, then writes the string to the output using the `Serial.write()` function. An initial buffer is automatically allocated, and if that initial buffer is not big enough for the character string you are printing, the printf() member function automatically reallocates the buffer to a larger size that will hold it. It currently never reduces the buffer size, but if for some reason you wanted to do that, you can do it like this:

```
// Output a very long string.
monitor.printf("very long string....");
// Reallocate buffer to a small one. It will grow as needed.
monitor.setBufSize(20);
```

This uses the ``setBufSize()`` member function, which frees the existing buffer, if any, then allocates a new buffer
of the specified size. It is used by ``begin()`` and ``printf()`` when buffer allocation is needed.

## Contact

If you find a problem, please submit an issue report [here](https://github.com/tedtoal/monitor_printf/issues/new/choose).

You can contact me (the author) at [ted@tedtoal.net](ted@tedtoal.net)
