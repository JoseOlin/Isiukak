# WireNoFreeze

This library is a more recent fork of the official [Arduino I²C Wire
Library](https://github.com/nobodyinperson/ArduinoCore-avr/tree/master/libraries/Wire)
with the changes introduced by [WSWire](https://github.com/steamfire/WSWireLib)
applied.

## Usefulness

Basically, if you (ab-)use the really strict and non-fault-tolerant I²C Bus by
using crappy or potentially too long wiring, the official [Arduino I²C Wire
Library](https://github.com/nobodyinperson/ArduinoCore-avr/tree/master/libraries/Wire)
might hang your sketch for good. This might even escalate to not even the
Watchdog being able to reset the Arduino! This is caused by pretty aggressive
`while`-loops in the `twi` interrupt routines not being exited. The approach of
the [WSWire Library](https://github.com/steamfire/WSWireLib) (of which this
library is an updated fork) was to add a safety-`break` out of these loops to
ensure that the code does not hang. See the documentation of the [WSWire
Library](https://github.com/steamfire/WSWireLib) for further explanation.

## Usage

Install this library as you would install any other library. Then replace every

```c++
#include <Wire.h>
```

in your code with this:

```c++
#include <WireNoFreeze.h>
```

## Reasons for forking

- more recent upstream codebase for the [Arduino I²C Wire
  Library](https://github.com/nobodyinperson/ArduinoCore-avr/tree/master/libraries/Wire)
  (version 1.0.0)
- Library directory structure usable with [PlatformIO](https://platformio.org)
- [ArduinoCore Repository](https://github.com/nobodyinperson/ArduinoCore-avr)
  included as [`git subtree`](https://git-scm.com/book/en/v1/Git-Tools-Subtree-Merging)
  for (hopefully) easier upstream merging

