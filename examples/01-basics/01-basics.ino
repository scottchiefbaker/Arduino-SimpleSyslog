#include <SimpleSyslog.h>

#if defined(ESP8266)
	#include <ESP8266WiFi.h>
#elif defined(ESP32)
	#include <WiFi.h>
#endif

// Hostname and AppName are sent in the syslog packet
SimpleSyslog syslog("YourHostname", "YourAppName", "192.168.5.222");

void setup() {
	Serial.begin(115200);

	int ok = init_wifi("YourSSID", "Password");

	// Send a LOCAL7.INFO level syslog message
	syslog.printf(FAC_LOCAL7, PRI_INFO, "Connected to WiFi!");

	// Note:
	// FAC_USER, and FAC_LOCAL0 through FAC_LOCAL7 are valid facilities
	// PRI_EMERGENCY, PRI_ALERT, PRI_CRITICAL, PRI_ERROR, PRI_WARNING, PRI_NOTICE, PRI_INFO, and PRI_DEBUG are valid
}

void loop() {
	// Send a USER.WARNING level syslog message
	syslog.printf(FAC_USER, PRI_WARNING, "Looping around... Uptime: %0.1f minutes", millis() / (float)60000);

	delay(20000);
}

int init_wifi(const char* ssid, const char* password) {
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);

	int start = millis();

	Serial.print("\r\nConnecting to WiFi ");
	while (WiFi.status() != WL_CONNECTED) {
		Serial.print('.');
		if (millis() - start > 30000) {
			Serial.println("\r\nWiFi taking too long, not waiting anymore");
			return 0;
		}
		delay(1000);
	}

	Serial.print("\r\nIP : ");
	Serial.println(WiFi.localIP());
	Serial.printf("MAC: %s\r\n", WiFi.macAddress().c_str());

	return 1;
}
