#ifndef SIMPLE_SYSLOG_H
#define SIMPLE_SYSLOG_H

#define SIMPLE_SYSLOG_VERSION "0.1.1"

#if defined(ESP8266)
	#include <ESP8266WiFi.h>
#elif defined(ESP32)
	#include <WiFi.h>
#else
	#error SimpleSyslog requires an ESP board. Disabling for non-supported board
#endif

// Syslog reference: https://www.dl8rds.de/index.php/Arduino_Syslog_Client_Library

#include <Arduino.h>
#include <WiFiUdp.h>

#define MAX_PACKET_SIZE 256

#define PRI_EMERGENCY 0
#define PRI_ALERT     1
#define PRI_CRITICAL  2
#define PRI_ERROR     3
#define PRI_WARNING   4
#define PRI_NOTICE    5
#define PRI_INFO      6
#define PRI_DEBUG     7

#define FAC_USER   1
#define FAC_LOCAL0 16
#define FAC_LOCAL1 17
#define FAC_LOCAL2 18
#define FAC_LOCAL3 19
#define FAC_LOCAL4 20
#define FAC_LOCAL5 21
#define FAC_LOCAL6 22
#define FAC_LOCAL7 23

class SimpleSyslog {
	WiFiUDP SimpleSyslog_udp;

	public:
		SimpleSyslog(const char* hostname, const char* app, const char* server, uint16_t port = 514) {
			this->_hostname = hostname;
			this->_app      = app;
			this->_server   = server;
			this->_port     = port;
		}

		void printf(uint8_t facility, uint8_t severity, char* format, ...) {
			// The PRI value is an integer number which calculates by the following metric:
			uint8_t priority = (8 * facility) + severity;

			// Get the variadic params from this function
			va_list args;
			va_start(args, format);
			char buf[128];
			vsnprintf(buf, 128, format, args);
			va_end(args);

			// This is a unit8 instead of a char because that's what udp.write() wants
			uint8_t buffer[MAX_PACKET_SIZE];
			int len = snprintf((char*)buffer, MAX_PACKET_SIZE, "<%d>%s %s: %s", priority, _hostname, _app, buf);

			// Send the raw UDP packet
			SimpleSyslog_udp.beginPacket(_server, _port);
			SimpleSyslog_udp.write(buffer, len);
			SimpleSyslog_udp.endPacket();
		}

	private:
		const char* _hostname;
		const char* _app;
		const char* _server;
		uint16_t _port;
};
#endif
