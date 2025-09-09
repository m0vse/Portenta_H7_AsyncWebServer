/****************************************************************************************************************************
  Async_HttpBasicAuth.ino - Dead simple AsyncWebServer for STM32 LAN8720 or built-in LAN8742A Ethernet

  For Portenta_H7 (STM32H7) with Vision-Shield Ethernet or Murata WiFi

  Portenta_H7_AsyncWebServer is a library for the Portenta_H7 with Vision-Shield Ethernet or Murata WiFi

  Based on and modified from ESPAsyncWebServer (https://github.com/me-no-dev/ESPAsyncWebServer)
  Built by Khoi Hoang https://github.com/khoih-prog/Portenta_H7_AsyncWebServer
  Licensed under GPLv3 license
 *****************************************************************************************************************************/

#if !( defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_GIGA) )
	#error For Portenta_H7 only
#endif

#define _PORTENTA_H7_AWS_LOGLEVEL_     1

#define USE_ETHERNET_PORTENTA_H7        true

#include <Portenta_Ethernet.h>
#include <Ethernet.h>
#warning Using Portenta_Ethernet lib for Portenta_H7.

#include <Portenta_H7_AsyncWebServer.h>

// Enter a MAC address and IP address for your controller below.
#define NUMBER_OF_MAC      20

byte mac[][NUMBER_OF_MAC] =
{
	{ 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x01 },
	{ 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x02 },
	{ 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x03 },
	{ 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x04 },
	{ 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x05 },
	{ 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x06 },
	{ 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x07 },
	{ 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x08 },
	{ 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x09 },
	{ 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x0A },
	{ 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x0B },
	{ 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x0C },
	{ 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x0D },
	{ 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x0E },
	{ 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x0F },
	{ 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x10 },
	{ 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x11 },
	{ 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x12 },
	{ 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x13 },
	{ 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x14 },
};
// Select the IP address according to your local network
IPAddress ip(192, 168, 2, 232);

AsyncWebServer    server(80);

const char* www_username = "admin";
const char* www_password = "portenta";

void setup()
{
	Serial.begin(115200);

	while (!Serial && millis() < 5000);

	delay(200);

	Serial.print("\nStart Async_HTTPBasicAuth on ");
	Serial.print(BOARD_NAME);
	Serial.print(" with ");
	Serial.println(SHIELD_TYPE);
	Serial.println(PORTENTA_H7_ASYNC_TCP_VERSION);
	Serial.println(PORTENTA_H7_ASYNC_WEBSERVER_VERSION);

	///////////////////////////////////

	// start the ethernet connection and the server
	// Use random mac
	uint16_t index = millis() % NUMBER_OF_MAC;

	// Use Static IP
	//Ethernet.begin(mac[index], ip);
	// Use DHCP dynamic IP and random mac
	Ethernet.begin(mac[index]);

	if (Ethernet.hardwareStatus() == EthernetNoHardware)
	{
		Serial.println("No Ethernet found. Stay here forever");

		while (true)
		{
			delay(1); // do nothing, no point running without Ethernet hardware
		}
	}

	if (Ethernet.linkStatus() == LinkOFF)
	{
		Serial.println("Not connected Ethernet cable");
	}

	Serial.print(F("Using mac index = "));
	Serial.println(index);

	Serial.print(F("Connected! IP address: "));
	Serial.println(Ethernet.localIP());

	///////////////////////////////////

	server.on("/", HTTP_GET, [](AsyncWebServerRequest * request)
	{
		if (!request->authenticate(www_username, www_password))
		{
			return request->requestAuthentication();
		}

		request->send(200, "text/plain", "Login OK");
	});


	server.begin();

	Serial.print(F("Async_HttpBasicAuth started @ IP : "));
	Serial.println(Ethernet.localIP());

	Serial.print(F("Open http://"));
	Serial.print(Ethernet.localIP());
	Serial.println(F("/ in your browser to see it working"));

	Serial.print(F("Login using username = "));
	Serial.print(www_username);
	Serial.print(F(" and password = "));
	Serial.println(www_password);
}

void heartBeatPrint()
{
	static int num = 1;

	Serial.print(F("."));

	if (num == 80)
	{
		Serial.println();
		num = 1;
	}
	else if (num++ % 10 == 0)
	{
		Serial.print(F(" "));
	}
}

void check_status()
{
	static unsigned long checkstatus_timeout = 0;

#define STATUS_CHECK_INTERVAL     10000L

	// Send status report every STATUS_REPORT_INTERVAL (60) seconds: we don't need to send updates frequently if there is no status change.
	if ((millis() > checkstatus_timeout) || (checkstatus_timeout == 0))
	{
		heartBeatPrint();
		checkstatus_timeout = millis() + STATUS_CHECK_INTERVAL;
	}
}

void loop()
{
	check_status();
}
