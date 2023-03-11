# Arduino SimpleSyslog

Easily add web based remote syslog capabilities to your ESP32/ESP8266 projects.

## Installation

Clone this repo to your Arduino libraries directory. On Linux this is `~/Arduino/libraries/`.
Alternately you can just drop `SimpleSyslog.h` in the same directory as your `.ino`
script.

## Usage

Include the SimpleSyslog library and create a global `syslog` object with your environment settings:

```C++
#include <SimpleSyslog.h>

SimpleSyslog syslog("ArduinoHostname", "ArduinoApp", "192.168.5.222");
```

Send a syslog message:

```C++
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

## Configuring `rsyslog` to receive messages

You will need to configure your `/etc/rsyslog.conf` to accept incoming UDP syslog
messages. Add these lines to your config and restart `rsyslog`

```
$ModLoad imudp
$UDPServerRun 514
```

You may want to configure a specific rule to handle your messages:

```
# /etc/rsyslog.d/arduino.conf
template(name="arduino" type="string" string="/var/log/arduino.log")

if ($syslogfacility-text == "local7" or $syslogfacility-text == "user") then {
    action(type="omfile" DynaFile="arduino" FileCreateMode="0644")
    stop
}
```

## Based on

Borrowed from [jerryr/EspSyslog](https://github.com/jerryr/EspSyslog) and improved upon.
