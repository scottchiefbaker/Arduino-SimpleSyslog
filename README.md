# Arduino SimpleSyslog

Easily add web based remote syslog capabilities to your ESP32/ESP8266 projects.

## Installation

Clone this repo to your Arduino libraries directory. On Linux this is `~/Arduino/libraries/`.
Alternately you can just drop `SimpleSyslog.h` in the same directory as your `.ino`
script.

## Usage

Include the Simple syslog library and create a global `syslog` object with your environment settings:

```C++
#include <SimpleSyslog.h>

SimpleSyslog syslog("YourHostname", "YourAppName", "192.168.5.222");
```

Send a syslog message:

```
// Simple string syntax
syslog.printf(FAC_LOCAL7, PRI_INFO, "This is a simple LOCAL7.INFO syslog packet");

// Advanced printf() syntax supported also
syslog.printf(FAC_USER, PRI_DEBUG, "Uptime: %s", millis());
```

Valid facilities:
* `FAC_USER`
* `FAC_LOCAL0`
* `FAC_LOCAL1`
* `FAC_LOCAL2`
* `FAC_LOCAL3`
* `FAC_LOCAL4`
* `FAC_LOCAL5`
* `FAC_LOCAL6`
* `FAC_LOCAL7`

Valid severities:
* `PRI_EMERGENCY`
* `PRI_ALERT`
* `PRI_CRITICAL`
* `PRI_ERROR`
* `PRI_WARNING`
* `PRI_NOTICE`
* `PRI_INFO`
* `PRI_DEBUG`

## Based on

Borrowed from [jerryr/EspSyslog](https://github.com/jerryr/EspSyslog) and improved upon.
