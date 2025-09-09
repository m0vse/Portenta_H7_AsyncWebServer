This is an attempt to add support for the Arduino Giga R1 Wifi board. It is not currently working and crashes after serving the first request!

# Portenta_H7_AsyncWebServer

[![arduino-library-badge](https://www.ardu-badge.com/badge/Portenta_H7_AsyncWebServer.svg?)](https://www.ardu-badge.com/Portenta_H7_AsyncWebServer)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/Portenta_H7_AsyncWebServer.svg)](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/releases)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/Portenta_H7_AsyncWebServer.svg)](http://github.com/khoih-prog/Portenta_H7_AsyncWebServer/issues)

<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>


---
---

## Table of contents

* [Table of contents](#table-of-contents)
* [Important Note from v1.4.0](#Important-Note-from-v140)
* [Why do we need this Portenta_H7_AsyncWebServer library](#why-do-we-need-this-Portenta_H7_AsyncWebServer-library)
  * [Features](#features)
  * [Why Async is better](#why-async-is-better)
  * [Currently supported Boards](#currently-supported-boards)
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For Portenta_H7 boards using Arduino IDE in Linux](#1-for-portenta_h7-boards-using-arduino-ide-in-linux)
  * [2. To fix compile error relating to dns_gethostbyname and LwIP stack](#2-to-fix-compile-error-relating-to-dns_gethostbyname-and-lwip-stack)
* [Important things to remember](#important-things-to-remember)
* [Principles of operation](#principles-of-operation)
  * [The Async Web server](#the-async-web-server)
  * [Request Life Cycle](#request-life-cycle)
  * [Rewrites and how do they work](#rewrites-and-how-do-they-work)
  * [Handlers and how do they work](#handlers-and-how-do-they-work)
  * [Responses and how do they work](#responses-and-how-do-they-work)
  * [Template processing](#template-processing)
* [Request Variables](#request-variables)
  * [Common Variables](#common-variables)
  * [Headers](#headers)
  * [GET, POST and FILE parameters](#get-post-and-file-parameters)
  * [JSON body handling with ArduinoJson](#json-body-handling-with-arduinojson)
* [Responses](#responses)
  * [Redirect to another URL](#redirect-to-another-url)
  * [Basic response with HTTP Code](#basic-response-with-http-code)
  * [Basic response with HTTP Code and extra headers](#basic-response-with-http-code-and-extra-headers)
  * [Basic response with string content](#basic-response-with-string-content)
  * [Basic response with string content and extra headers](#basic-response-with-string-content-and-extra-headers)
  * [Respond with content coming from a Stream](#respond-with-content-coming-from-a-stream)
  * [Respond with content coming from a Stream and extra headers](#respond-with-content-coming-from-a-stream-and-extra-headers)
  * [Respond with content coming from a Stream containing templates](#respond-with-content-coming-from-a-stream-containing-templates)
  * [Respond with content coming from a Stream containing templates and extra headers](#respond-with-content-coming-from-a-stream-containing-templates-and-extra-headers)
  * [Respond with content using a callback](#respond-with-content-using-a-callback)
  * [Respond with content using a callback and extra headers](#respond-with-content-using-a-callback-and-extra-headers)
  * [Respond with content using a callback containing templates](#respond-with-content-using-a-callback-containing-templates)
  * [Respond with content using a callback containing templates and extra headers](#respond-with-content-using-a-callback-containing-templates-and-extra-headers)
  * [Chunked Response](#chunked-response)
  * [Chunked Response containing templates](#chunked-response-containing-templates)
  * [Print to response](#print-to-response)
  * [ArduinoJson Basic Response](#arduinojson-basic-response)
  * [ArduinoJson Advanced Response](#arduinojson-advanced-response)
* [Param Rewrite With Matching](#param-rewrite-with-matching)
* [Using filters](#using-filters)
* [Bad Responses](#bad-responses)
  * [Respond with content using a callback without content length to HTTP/1.0 clients](#respond-with-content-using-a-callback-without-content-length-to-http10-clients)
* [Async WebSocket Plugin](#async-websocket-plugin)
  * [Async WebSocket Event](#async-websocket-event)
  * [Methods for sending data to a socket client](#methods-for-sending-data-to-a-socket-client)
  * [Direct access to web socket message buffer](#direct-access-to-web-socket-message-buffer)
  * [Limiting the number of web socket clients](#limiting-the-number-of-web-socket-clients)
* [Async Event Source Plugin](#async-event-source-plugin)
  * [Setup Event Source on the server](#setup-event-source-on-the-server)
  * [Setup Event Source in the browser](#setup-event-source-in-the-browser)
* [Remove handlers and rewrites](#remove-handlers-and-rewrites)
* [Setting up the server](#setting-up-the-server)
  * [Setup global and class functions as request handlers](#setup-global-and-class-functions-as-request-handlers)
  * [Methods for controlling websocket connections](#methods-for-controlling-websocket-connections)
  * [Adding Default Headers](#adding-default-headers)
  * [Path variable](#path-variable)
* [Examples](#examples)
  * [1. For Vision-shield Ethernet](#1-for-Vision-shield-Ethernet)
    * [ 1. Async_AdvancedWebServer](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/Async_AdvancedWebServer)
    * [ 2. Async_HelloServer](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/Async_HelloServer)
    * [ 3. Async_HelloServer2](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/Async_HelloServer2)
    * [ 4. Async_HttpBasicAuth](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/Async_HttpBasicAuth)
    * [ 5. Async_PostServer](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/Async_PostServer)
    * [ 6. **MQTTClient_Auth**](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/MQTTClient_Auth)
    * [ 7. **MQTTClient_Basic**](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/MQTTClient_Basic)
    * [ 8. **MQTT_ThingStream**](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/MQTT_ThingStream)
    * [ 9. WebClient](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/WebClient)
    * [10. WebClientRepeating](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/WebClientRepeating)
    * [11. Async_AdvancedWebServer_MemoryIssues_SendArduinoString](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/Async_AdvancedWebServer_MemoryIssues_SendArduinoString) **New**
    * [12. Async_AdvancedWebServer_MemoryIssues_Send_CString](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/Async_AdvancedWebServer_MemoryIssues_Send_CString) **New**
    * [13. Async_AdvancedWebServer_SendChunked](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/Async_AdvancedWebServer_SendChunked) **New**
    * [14. AsyncWebServer_SendChunked](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/AsyncWebServer_SendChunked) **New**
  * [2. For Murata WiFi](#2-for-Murata-WiFi)
    * [ 1. Async_AdvancedWebServer](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/WiFi/Async_AdvancedWebServer)
    * [ 2. Async_HelloServer](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/WiFi/Async_HelloServer)
    * [ 3. Async_HelloServer2](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/WiFi/Async_HelloServer2)
    * [ 4. Async_HttpBasicAuth](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/WiFi/Async_HttpBasicAuth)
    * [ 5. Async_PostServer](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/WiFi/Async_PostServer)
    * [ 6. **MQTTClient_Auth**](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/WiFi/MQTTClient_Auth)
    * [ 7. **MQTTClient_Basic**](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/WiFi/MQTTClient_Basic)
    * [ 8. **MQTT_ThingStream**](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/WiFi/MQTT_ThingStream)
    * [ 9. WebClient](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/WiFi/WebClient)
    * [10. WebClientRepeating](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/WiFi/WebClientRepeating)
    * [11. Async_AdvancedWebServer_MemoryIssues_Send_CString](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/WiFi/Async_AdvancedWebServer_MemoryIssues_Send_CString) **New**
    * [12. Async_AdvancedWebServer_SendChunked](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/WiFi/Async_AdvancedWebServer_SendChunked) **New**
    * [13. AsyncWebServer_SendChunked](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/WiFi/AsyncWebServer_SendChunked) **New**
* [Example Async_AdvancedWebServer](#Example-Async_AdvancedWebServer)
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [ 1. MQTT_ThingStream on PORTENTA_H7_M7 using Ethernet](#1-MQTT_ThingStream-on-PORTENTA_H7_M7-using-Ethernet)
  * [ 2. WebClientRepeating on PORTENTA_H7_M7 using Ethernet](#2-WebClientRepeating-on-PORTENTA_H7_M7-using-Ethernet)
  * [ 3. MQTTClient_Auth on PORTENTA_H7_M7 using Ethernet](#3-MQTTClient_Auth-on-PORTENTA_H7_M7-using-Ethernet)
  * [ 4. MQTTClient_Basic on PORTENTA_H7_M7 using Ethernet](#4-MQTTClient_Basic-on-PORTENTA_H7_M7-using-Ethernet)
  * [ 5. Async_HTTPBasicAuth on PORTENTA_H7_M7 using Ethernet](#5-Async_HTTPBasicAuth-on-PORTENTA_H7_M7-using-Ethernet)
  * [ 6. Async_AdvancedWebServer on PORTENTA_H7_M7 using Ethernet](#6-Async_AdvancedWebServer-on-PORTENTA_H7_M7-using-Ethernet)
  * [ 7. Async_AdvancedWebServer on PORTENTA_H7_M7 using WiFi](#7-Async_AdvancedWebServer-on-PORTENTA_H7_M7-using-WiFi)
  * [ 8. Async_AdvancedWebServer_MemoryIssues_Send_CString on PORTENTA_H7_M7 using Ethernet](#8-Async_AdvancedWebServer_MemoryIssues_Send_CString-on-PORTENTA_H7_M7-using-Ethernet)
  * [ 9. Async_AdvancedWebServer_SendChunked on PORTENTA_H7_M7 using WiFi](#9-Async_AdvancedWebServer_SendChunked-on-PORTENTA_H7_M7-using-WiFi)
  * [10. Async_AdvancedWebServer_SendChunked on PORTENTA_H7_M7 using Ethernet](#10-Async_AdvancedWebServer_SendChunked-on-PORTENTA_H7_M7-using-Ethernet)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)

---
---

### Important Note from v1.4.0

The new `v1.4.0+` has added a new and powerful feature to permit using `CString` in optional `SDRAM` to save heap to send `very large data`.

Check the `marvelleous` PRs of **@salasidis** 
- [request->send(200, textPlainStr, jsonChartDataCharStr); - Without using String Class - to save heap #8](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/pull/8)
- [All memmove() removed - string no longer destroyed #11](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/pull/11)

and these new examples

1. [Async_AdvancedWebServer_MemoryIssues_Send_CString for Ethernet](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/Async_AdvancedWebServer_MemoryIssues_Send_CString)
2. [Async_AdvancedWebServer_MemoryIssues_SendArduinoString for Ethernet](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/Async_AdvancedWebServer_MemoryIssues_SendArduinoString)
3. [Async_AdvancedWebServer_MemoryIssues_Send_CString for WiFi](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/WiFi/Async_AdvancedWebServer_MemoryIssues_Send_CString)

If using Arduino String, to send a buffer around 40 KBytes, the used `Max Heap` is around **111,500 bytes (~3 times)**

If using CString in SDRAM, with the same 40 KByte, the used `Max Heap` is around **14,314 bytes**

If using CString in regular memory, with the same 40 KByte, the used `Max Heap` is around **51,823 bytes (~1 times)**

This is very critical in use-cases where sending `very large data` is necessary, without `heap-allocation-error`.


1. The traditional function used to send `Arduino String` is

https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/blob/42006c1183a97089e38151b35cc8cc520873f9f1/src/Portenta_H7_AsyncWebServer.h#L344

```cpp
void send(int code, const String& contentType = String(), const String& content = String());
```

such as

```cpp
request->send(200, textPlainStr, ArduinoStr);
```
The required HEAP is about **3 times of the String size**

2. To use `CString` but don't destroy it after sending. Use function

https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/blob/42006c1183a97089e38151b35cc8cc520873f9f1/src/Portenta_H7_AsyncWebServer.h#L345

```cpp
void send(int code, const String& contentType, const char *content, bool nonDetructiveSend = true);    // RSMOD
```

such as 

```cpp
request->send(200, textPlainStr, cStr);
```

The required HEAP is also about **3 times of the CString size** because of many `unnecessary copies` of the CString in HEAP.  Avoid this `unefficient` way.


3. To use `CString` without destroying it after sending. Use function

https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/blob/42006c1183a97089e38151b35cc8cc520873f9f1/src/Portenta_H7_AsyncWebServer.h#L345

```cpp
void send(int code, const String& contentType, const char *content, bool nonDetructiveSend = true);    // RSMOD
```

such as 

```cpp
request->send(200, textPlainStr, cStr, false);
```

The required HEAP is also about **1 times of the CString size without using SDRAM, or none if using SDRAM**. This way is the best and most efficient way to use by avoiding of many `unnecessary copies` of the CString in HEAP


---
---

### Why do we need this [Portenta_H7_AsyncWebServer library](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer)

#### Features

This library is based on, modified from:

1. [Hristo Gochkov's ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)

to apply the better and faster **asynchronous** feature of the **powerful** [ESPAsyncWebServer Library](https://github.com/me-no-dev/ESPAsyncWebServer) into **Portenta_H7**. Thus [Portenta_H7_AsyncWebServer](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer) is part of a series of advanced Async libraries, such as AsyncTCP, AsyncUDP, AsyncWebSockets, AsyncHTTPRequest, AsyncHTTPSRequest, etc. to be written or modified to support **Portenta_H7**, using either `Vision-shield Ethernet` or `Murata WiFi`.


#### Why Async is better

- Using asynchronous network means that you can handle **more than one connection at the same time**
- **You are called once the request is ready and parsed**
- When you send the response, you are **immediately ready** to handle other connections while the server is taking care of sending the response in the background
- **Speed is OMG**
- **Easy to use API, HTTP Basic and Digest MD5 Authentication (default), ChunkedResponse**
- Easily extensible to handle **any type of content**
- Supports Continue 100
- **Async WebSocket plugin offering different locations without extra servers or ports**
- Async EventSource (Server-Sent Events) plugin to send events to the browser
- URL Rewrite plugin for conditional and permanent url rewrites
- ServeStatic plugin that supports cache, Last-Modified, default index and more
- Simple template processing engine to handle templates


---

### Currently supported Boards

1. **Portenta_H7 boards** such as Portenta_H7 Rev2 ABX00042, etc., using [**ArduinoCore-mbed mbed_portenta** core](https://github.com/arduino/ArduinoCore-mbed) using `Vision-shield Ethernet` or `Murata WiFi`

<p align="center">
    <img src="https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/raw/main/pics/Portenta_Vision.jpg">
</p>


---
---

## Prerequisites

 1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
 2. [`ArduinoCore-mbed mbed_portenta core 3.5.4+`](https://github.com/arduino/ArduinoCore-mbed) for Arduino **Portenta_H7** boards, such as **Portenta_H7 Rev2 ABX00042, etc.**. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-mbed.svg)](https://github.com/arduino/ArduinoCore-mbed/releases/latest).
 3. [`Portenta_H7_AsyncTCP library v1.4.0+`](https://github.com/khoih-prog/Portenta_H7_AsyncTCP) for Portenta_H7 using `Vision-shield Ethernet` or `Murata WiFi`. [![GitHub release](https://img.shields.io/github/release/khoih-prog/Portenta_H7_AsyncTCP.svg)](https://github.com/khoih-prog/Portenta_H7_AsyncTCP/releases/latest)

---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for `Portenta_H7_AsyncWebServer`, then select / install the latest version. You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/Portenta_H7_AsyncWebServer.svg?)](https://www.ardu-badge.com/Portenta_H7_AsyncWebServer) for more detailed instructions.

### Manual Install

1. Navigate to [Portenta_H7_AsyncWebServer](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer) page.
2. Download the latest release `Portenta_H7_AsyncWebServer-main.zip`.
3. Extract the zip file to `Portenta_H7_AsyncWebServer-main` directory 
4. Copy the whole `Portenta_H7_AsyncWebServer-main` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO:

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**Portenta_H7_AsyncWebServer** library](https://registry.platformio.org/libraries/khoih-prog/Portenta_H7_AsyncWebServer) by using [Library Manager](https://registry.platformio.org/libraries/khoih-prog/Portenta_H7_AsyncWebServer/installation). Search for **Portenta_H7_AsyncWebServer** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

### Packages' Patches

#### 1. For Portenta_H7 boards using Arduino IDE in Linux

  **To be able to upload firmware to Portenta_H7 using Arduino IDE in Linux (Ubuntu, etc.)**, you have to copy the file [portenta_post_install.sh](Packages_Patches/arduino/hardware/mbed_portenta/3.4.1/portenta_post_install.sh) into mbed_portenta directory (~/.arduino15/packages/arduino/hardware/mbed_portenta/3.4.1/portenta_post_install.sh). 
  
  Then run the following command using `sudo`
  
```
$ cd ~/.arduino15/packages/arduino/hardware/mbed_portenta/3.4.1
$ chmod 755 portenta_post_install.sh
$ sudo ./portenta_post_install.sh
```

This will create the file `/etc/udev/rules.d/49-portenta_h7.rules` as follows:

```
# Portenta H7 bootloader mode UDEV rules

SUBSYSTEMS=="usb", ATTRS{idVendor}=="2341", ATTRS{idProduct}=="035b", GROUP="plugdev", MODE="0666"
```

Supposing the ArduinoCore-mbed core version is 3.4.1. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/3.4.1/portenta_post_install.sh`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/x.yy.zz/portenta_post_install.sh`


#### 2. To fix compile error relating to dns_gethostbyname and LwIP stack


#### Notes: Only for cores v2.5.2-. This fix is not necessary for core v3.4.1+

**To be able to compile, run on Portenta_H7 boards**, you have to copy the whole [mbed_portenta Packages_Patches](Packages_Patches/arduino/hardware/mbed_portenta/2.5.2) directory into Arduino mbed_portenta directory (~/.arduino15/packages/arduino/hardware/mbed_portenta/2.5.2). 

Supposing the Arduino mbed_portenta version is 2.5.2. These file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/2.5.2/libraries/SocketWrapper/src/MbedUdp.h`
- `~/.arduino15/packages/arduino/hardware/mbed_portenta/2.5.2/libraries/SocketWrapper/src/MbedUdp.cpp`
- `~/.arduino15/packages/arduino/hardware/mbed_portenta/2.5.2/cores/arduino/mbed/connectivity/lwipstack/include/lwipstack/lwipopts.h`

---
---

## Important things to remember

- This is fully asynchronous server and as such does not run on the loop thread.
- You can not use yield() or delay() or any function that uses them inside the callbacks
- The server is smart enough to know when to close the connection and free resources
- You can not send more than one response to a single request

---

## Principles of operation

### The Async Web server

- Listens for connections
- Wraps the new clients into `Request`
- Keeps track of clients and cleans memory
- Manages `Rewrites` and apply them on the request url
- Manages `Handlers` and attaches them to Requests

### Request Life Cycle

- TCP connection is received by the server
- The connection is wrapped inside `Request` object
- When the request head is received (type, url, get params, http version and host),
  the server goes through all `Rewrites` (in the order they were added) to rewrite the url and inject query parameters,
  next, it goes through all attached `Handlers`(in the order they were added) trying to find one
  that `canHandle` the given request. If none are found, the default(catch-all) handler is attached.
- The rest of the request is received, calling the `handleUpload` or `handleBody` methods of the `Handler` if they are needed (POST+File/Body)
- When the whole request is parsed, the result is given to the `handleRequest` method of the `Handler` and is ready to be responded to
- In the `handleRequest` method, to the `Request` is attached a `Response` object (see below) that will serve the response data back to the client
- When the `Response` is sent, the client is closed and freed from the memory

### Rewrites and how do they work

- The `Rewrites` are used to rewrite the request url and/or inject get parameters for a specific request url path.
- All `Rewrites` are evaluated on the request in the order they have been added to the server.
- The `Rewrite` will change the request url only if the request url (excluding get parameters) is fully match
  the rewrite url, and when the optional `Filter` callback return true.
- Setting a `Filter` to the `Rewrite` enables to control when to apply the rewrite, decision can be based on
  request url, http version, request host/port/target host, get parameters or the request client's localIP or remoteIP.
- The `Rewrite` can specify a target url with optional get parameters, e.g. `/to-url?with=params`

### Handlers and how do they work

- The `Handlers` are used for executing specific actions to particular requests
- One `Handler` instance can be attached to any request and lives together with the server
- Setting a `Filter` to the `Handler` enables to control when to apply the handler, decision can be based on
  request url, http version, request host/port/target host, get parameters or the request client's localIP or remoteIP.
- The `canHandle` method is used for handler specific control on whether the requests can be handled
  and for declaring any interesting headers that the `Request` should parse. Decision can be based on request
  method, request url, http version, request host/port/target host and get parameters
- Once a `Handler` is attached to given `Request` (`canHandle` returned true)
  that `Handler` takes care to receive any file/data upload and attach a `Response`
  once the `Request` has been fully parsed
- `Handlers` are evaluated in the order they are attached to the server. The `canHandle` is called only
  if the `Filter` that was set to the `Handler` return true.
- The first `Handler` that can handle the request is selected, not further `Filter` and `canHandle` are called.

### Responses and how do they work

- The `Response` objects are used to send the response data back to the client
- The `Response` object lives with the `Request` and is freed on end or disconnect
- Different techniques are used depending on the response type to send the data in packets
  returning back almost immediately and sending the next packet when this one is received.
  Any time in between is spent to run the user loop and handle other network packets
- Responding asynchronously is probably the most difficult thing for most to understand
- Many different options exist for the user to make responding a background task

### Template processing

- Portenta_H7_AsyncWebServer contains simple template processing engine.
- Template processing can be added to most response types.
- Currently it supports only replacing template placeholders with actual values. No conditional processing, cycles, etc.
- Placeholders are delimited with `%` symbols. Like this: `%TEMPLATE_PLACEHOLDER%`.
- It works by extracting placeholder name from response text and passing it to user provided function which should return actual value to be used instead of placeholder.
- Since it's user provided function, it is possible for library users to implement conditional processing and cycles themselves.
- Since it's impossible to know the actual response size after template processing step in advance (and, therefore, to include it in response headers), the response becomes [chunked](#chunked-response).

---

## Request Variables

### Common Variables

```cpp
request->version();       // uint8_t: 0 = HTTP/1.0, 1 = HTTP/1.1
request->method();        // enum:    HTTP_GET, HTTP_POST, HTTP_DELETE, HTTP_PUT, HTTP_PATCH, HTTP_HEAD, HTTP_OPTIONS
request->url();           // String:  URL of the request (not including host, port or GET parameters)
request->host();          // String:  The requested host (can be used for virtual hosting)
request->contentType();   // String:  ContentType of the request (not available in Handler::canHandle)
request->contentLength(); // size_t:  ContentLength of the request (not available in Handler::canHandle)
request->multipart();     // bool:    True if the request has content type "multipart"
```

### Headers

```cpp
//List all collected headers
int headers = request->headers();
int i;

for (i=0;i<headers;i++)
{
  AsyncWebHeader* h = request->getHeader(i);
  Serial.printf("HEADER[%s]: %s\n", h->name().c_str(), h->value().c_str());
}

//get specific header by name
if (request->hasHeader("MyHeader"))
{
  AsyncWebHeader* h = request->getHeader("MyHeader");
  Serial.printf("MyHeader: %s\n", h->value().c_str());
}

//List all collected headers (Compatibility)
int headers = request->headers();
int i;

for (i=0;i<headers;i++)
{
  Serial.printf("HEADER[%s]: %s\n", request->headerName(i).c_str(), request->header(i).c_str());
}

//get specific header by name (Compatibility)
if (request->hasHeader("MyHeader"))
{
  Serial.printf("MyHeader: %s\n", request->header("MyHeader").c_str());
}
```

### GET, POST and FILE parameters

```cpp
//List all parameters
int params = request->params();

for (int i=0;i<params;i++)
{
  AsyncWebParameter* p = request->getParam(i);
  
  if (p->isFile())
  { 
    //p->isPost() is also true
    Serial.printf("FILE[%s]: %s, size: %u\n", p->name().c_str(), p->value().c_str(), p->size());
  } 
  else if (p->isPost())
  {
    Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
  } 
  else 
  {
    Serial.printf("GET[%s]: %s\n", p->name().c_str(), p->value().c_str());
  }
}

//Check if GET parameter exists
if (request->hasParam("download"))
  AsyncWebParameter* p = request->getParam("download");

//Check if POST (but not File) parameter exists
if (request->hasParam("download", true))
  AsyncWebParameter* p = request->getParam("download", true);

//Check if FILE was uploaded
if (request->hasParam("download", true, true))
  AsyncWebParameter* p = request->getParam("download", true, true);

//List all parameters (Compatibility)
int args = request->args();

for (int i=0;i<args;i++)
{
  Serial.printf("ARG[%s]: %s\n", request->argName(i).c_str(), request->arg(i).c_str());
}

//Check if parameter exists (Compatibility)
if (request->hasArg("download"))
  String arg = request->arg("download");
```

### JSON body handling with ArduinoJson

Endpoints which consume JSON can use a special handler to get ready to use JSON data in the request callback:

```cpp
#include "AsyncJson.h"
#include "ArduinoJson.h"

AsyncCallbackJsonWebHandler* handler = new AsyncCallbackJsonWebHandler("/rest/endpoint", [](AsyncWebServerRequest *request, JsonVariant &json) 
{
  JsonObject& jsonObj = json.as<JsonObject>();
  // ...
});

server.addHandler(handler);
```
---

## Responses

### Redirect to another URL

```cpp
//to local url
request->redirect("/login");

//to external url
request->redirect("http://esp8266.com");
```

### Basic response with HTTP Code

```cpp
request->send(404); //Sends 404 File Not Found
```

### Basic response with HTTP Code and extra headers

```cpp
AsyncWebServerResponse *response = request->beginResponse(404); //Sends 404 File Not Found
response->addHeader("Server","Portenta_H7_AsyncWebServer");
request->send(response);
```

### Basic response with string content

```cpp
request->send(200, "text/plain", "Hello World!");
```

### Basic response with string content and extra headers

```cpp
AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", "Hello World!");
response->addHeader("Server","AsyncWebServer");
request->send(response);
```

### Respond with content coming from a Stream

```cpp
//read 12 bytes from Serial and send them as Content Type text/plain
request->send(Serial, "text/plain", 12);
```

### Respond with content coming from a Stream and extra headers

```cpp
//read 12 bytes from Serial and send them as Content Type text/plain
AsyncWebServerResponse *response = request->beginResponse(Serial, "text/plain", 12);
response->addHeader("Server","Portenta_H7_AsyncWebServer");
request->send(response);
```

### Respond with content coming from a Stream containing templates

```cpp
String processor(const String& var)
{
  if (var == "HELLO_FROM_TEMPLATE")
    return F("Hello world!");
    
  return String();
}

// ...

//read 12 bytes from Serial and send them as Content Type text/plain
request->send(Serial, "text/plain", 12, processor);
```

### Respond with content coming from a Stream containing templates and extra headers

```cpp
String processor(const String& var)
{
  if (var == "HELLO_FROM_TEMPLATE")
    return F("Hello world!");
  return String();
}

// ...

//read 12 bytes from Serial and send them as Content Type text/plain
AsyncWebServerResponse *response = request->beginResponse(Serial, "text/plain", 12, processor);
response->addHeader("Server","Portenta_H7_AsyncWebServer");
request->send(response);
```

### Respond with content using a callback

```cpp
//send 128 bytes as plain text
request->send("text/plain", 128, [](uint8_t *buffer, size_t maxLen, size_t index) -> size_t 
{
  //Write up to "maxLen" bytes into "buffer" and return the amount written.
  //index equals the amount of bytes that have been already sent
  //You will not be asked for more bytes once the content length has been reached.
  //Keep in mind that you can not delay or yield waiting for more data!
  //Send what you currently have and you will be asked for more again
  return mySource.read(buffer, maxLen);
});
```

### Respond with content using a callback and extra headers

```cpp
//send 128 bytes as plain text
AsyncWebServerResponse *response = request->beginResponse("text/plain", 128, [](uint8_t *buffer, size_t maxLen, size_t index) -> size_t 
{
  //Write up to "maxLen" bytes into "buffer" and return the amount written.
  //index equals the amount of bytes that have been already sent
  //You will not be asked for more bytes once the content length has been reached.
  //Keep in mind that you can not delay or yield waiting for more data!
  //Send what you currently have and you will be asked for more again
  return mySource.read(buffer, maxLen);
});

response->addHeader("Server","Portenta_H7_AsyncWebServer");
request->send(response);
```

### Respond with content using a callback containing templates

```cpp
String processor(const String& var)
{
  if (var == "HELLO_FROM_TEMPLATE")
    return F("Hello world!");
    
  return String();
}

// ...

//send 128 bytes as plain text
request->send("text/plain", 128, [](uint8_t *buffer, size_t maxLen, size_t index) -> size_t 
{
  //Write up to "maxLen" bytes into "buffer" and return the amount written.
  //index equals the amount of bytes that have been already sent
  //You will not be asked for more bytes once the content length has been reached.
  //Keep in mind that you can not delay or yield waiting for more data!
  //Send what you currently have and you will be asked for more again
  return mySource.read(buffer, maxLen);
}, processor);
```

### Respond with content using a callback containing templates and extra headers

```cpp
String processor(const String& var)
{
  if (var == "HELLO_FROM_TEMPLATE")
    return F("Hello world!");
  return String();
}

// ...

//send 128 bytes as plain text
AsyncWebServerResponse *response = request->beginResponse("text/plain", 128, [](uint8_t *buffer, size_t maxLen, size_t index) -> size_t 
{
  //Write up to "maxLen" bytes into "buffer" and return the amount written.
  //index equals the amount of bytes that have been already sent
  //You will not be asked for more bytes once the content length has been reached.
  //Keep in mind that you can not delay or yield waiting for more data!
  //Send what you currently have and you will be asked for more again
  return mySource.read(buffer, maxLen);
}, processor);

response->addHeader("Server","Portenta_H7_AsyncWebServer");
request->send(response);
```

### Chunked Response

Used when content length is unknown. Works best if the client supports HTTP/1.1

```cpp
AsyncWebServerResponse *response = request->beginChunkedResponse("text/plain", [](uint8_t *buffer, size_t maxLen, size_t index) -> size_t 
{
  //Write up to "maxLen" bytes into "buffer" and return the amount written.
  //index equals the amount of bytes that have been already sent
  //You will be asked for more data until 0 is returned
  //Keep in mind that you can not delay or yield waiting for more data!
  return mySource.read(buffer, maxLen);
});

response->addHeader("Server","Portenta_H7_AsyncWebServer");
request->send(response);
```

### Chunked Response containing templates

Used when content length is unknown. Works best if the client supports HTTP/1.1

```cpp
String processor(const String& var)
{
  if (var == "HELLO_FROM_TEMPLATE")
    return F("Hello world!");
    
  return String();
}

// ...

AsyncWebServerResponse *response = request->beginChunkedResponse("text/plain", [](uint8_t *buffer, size_t maxLen, size_t index) -> size_t 
{
  //Write up to "maxLen" bytes into "buffer" and return the amount written.
  //index equals the amount of bytes that have been already sent
  //You will be asked for more data until 0 is returned
  //Keep in mind that you can not delay or yield waiting for more data!
  return mySource.read(buffer, maxLen);
}, processor);

response->addHeader("Server","Portenta_H7_AsyncWebServer");
request->send(response);
```

### Print to response

```cpp
AsyncResponseStream *response = request->beginResponseStream("text/html");
response->addHeader("Server","Portenta_H7_AsyncWebServer");
response->printf("<!DOCTYPE html><html><head><title>Webpage at %s</title></head><body>", request->url().c_str());

response->print("<h2>Hello ");
response->print(request->client()->remoteIP());
response->print("</h2>");

response->print("<h3>General</h3>");
response->print("<ul>");
response->printf("<li>Version: HTTP/1.%u</li>", request->version());
response->printf("<li>Method: %s</li>", request->methodToString());
response->printf("<li>URL: %s</li>", request->url().c_str());
response->printf("<li>Host: %s</li>", request->host().c_str());
response->printf("<li>ContentType: %s</li>", request->contentType().c_str());
response->printf("<li>ContentLength: %u</li>", request->contentLength());
response->printf("<li>Multipart: %s</li>", request->multipart()?"true":"false");
response->print("</ul>");

response->print("<h3>Headers</h3>");
response->print("<ul>");
int headers = request->headers();

for (int i=0;i<headers;i++)
{
  AsyncWebHeader* h = request->getHeader(i);
  response->printf("<li>%s: %s</li>", h->name().c_str(), h->value().c_str());
}

response->print("</ul>");

response->print("<h3>Parameters</h3>");
response->print("<ul>");

int params = request->params();

for (int i=0;i<params;i++)
{
  AsyncWebParameter* p = request->getParam(i);
  
  if (p->isFile())
  {
    response->printf("<li>FILE[%s]: %s, size: %u</li>", p->name().c_str(), p->value().c_str(), p->size());
  } 
  else if (p->isPost())
  {
    response->printf("<li>POST[%s]: %s</li>", p->name().c_str(), p->value().c_str());
  } 
  else 
  {
    response->printf("<li>GET[%s]: %s</li>", p->name().c_str(), p->value().c_str());
  }
}

response->print("</ul>");

response->print("</body></html>");
//send the response last
request->send(response);
```

### ArduinoJson Basic Response

This way of sending Json is great for when the result is **below 4KB**

```cpp
#include "AsyncJson.h"
#include "ArduinoJson.h"


AsyncResponseStream *response = request->beginResponseStream("application/json");
DynamicJsonBuffer jsonBuffer;
JsonObject &root = jsonBuffer.createObject();
root["heap"] = ESP.getFreeHeap();
root["ssid"] = WiFi.SSID();
root.printTo(*response);

request->send(response);
```

### ArduinoJson Advanced Response

This response can handle really **large Json objects (tested to 40KB)**

There isn't any noticeable speed decrease for small results with the method above

Since ArduinoJson does not allow reading parts of the string, the whole Json has to be passed every time a 
chunks needs to be sent, which shows speed decrease proportional to the resulting json packets

```cpp
#include "AsyncJson.h"
#include "ArduinoJson.h"

AsyncJsonResponse * response = new AsyncJsonResponse();
response->addHeader("Server","AsyncWebServer");
JsonObject& root = response->getRoot();
root["IP"] = Ethernet.localIP();
response->setLength();

request->send(response);
```
---

## Param Rewrite With Matching
It is possible to rewrite the request url with parameter matchg. Here is an example with one parameter:
Rewrite for example "/radio/{frequence}" -> "/radio?f={frequence}"

```cpp
class OneParamRewrite : public AsyncWebRewrite
{
  protected:
    String _urlPrefix;
    int _paramIndex;
    String _paramsBackup;

  public:
  OneParamRewrite(const char* from, const char* to)
    : AsyncWebRewrite(from, to) 
    {

      _paramIndex = _from.indexOf('{');

      if ( _paramIndex >=0 && _from.endsWith("}")) 
      {
        _urlPrefix = _from.substring(0, _paramIndex);
        int index = _params.indexOf('{');
        
        if (index >= 0) 
        {
          _params = _params.substring(0, index);
        }
      } 
      else 
      {
        _urlPrefix = _from;
      }
      
      _paramsBackup = _params;
  }

  bool match(AsyncWebServerRequest *request) override 
  {
    if (request->url().startsWith(_urlPrefix)) 
    {
      if (_paramIndex >= 0) 
      {
        _params = _paramsBackup + request->url().substring(_paramIndex);
      } 
      else 
      {
        _params = _paramsBackup;
      }
      
      return true;

    } 
    else 
    {
      return false;
    }
  }
};
```

Usage:

```cpp
  server.addRewrite( new OneParamRewrite("/radio/{frequence}", "/radio?f={frequence}") );
```
---

## Using filters

Filters can be set to `Rewrite` or `Handler` in order to control when to apply the rewrite and consider the handler.
A filter is a callback function that evaluates the request and return a boolean `true` to include the item
or `false` to exclude it.

---

## Bad Responses

Some responses are implemented, but you should not use them, because they do not conform to HTTP.
The following example will lead to unclean close of the connection and more time wasted
than providing the length of the content

### Respond with content using a callback without content length to HTTP/1.0 clients

```cpp
//This is used as fallback for chunked responses to HTTP/1.0 Clients
request->send("text/plain", 0, [](uint8_t *buffer, size_t maxLen, size_t index) -> size_t 
{
  //Write up to "maxLen" bytes into "buffer" and return the amount written.
  //You will be asked for more data until 0 is returned
  //Keep in mind that you can not delay or yield waiting for more data!
  return mySource.read(buffer, maxLen);
});
```
---

## Async WebSocket Plugin

The server includes a web socket plugin which lets you define different WebSocket locations to connect to
without starting another listening service or using different port

### Async WebSocket Event

```cpp

void onEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len)
{
  if (type == WS_EVT_CONNECT)
  {
    //client connected
    Serial.printf("ws[%s][%u] connect\n", server->url(), client->id());
    client->printf("Hello Client %u :)", client->id());
    client->ping();
  } 
  else if (type == WS_EVT_DISCONNECT)
  {
    //client disconnected
    Serial.printf("ws[%s][%u] disconnect: %u\n", server->url(), client->id());
  } 
  else if (type == WS_EVT_ERROR)
  {
    //error was received from the other end
    Serial.printf("ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t*)arg), (char*)data);
  } 
  else if (type == WS_EVT_PONG)
  {
    //pong message was received (in response to a ping request maybe)
    Serial.printf("ws[%s][%u] pong[%u]: %s\n", server->url(), client->id(), len, (len)?(char*)data:"");
  } 
  else if (type == WS_EVT_DATA)
  {
    //data packet
    AwsFrameInfo * info = (AwsFrameInfo*)arg;
    
    if (info->final && info->index == 0 && info->len == len)
    {
      //the whole message is in a single frame and we got all of it's data
      Serial.printf("ws[%s][%u] %s-message[%llu]: ", server->url(), client->id(), (info->opcode == WS_TEXT)?"text":"binary", info->len);
      
      if (info->opcode == WS_TEXT)
      {
        data[len] = 0;
        Serial.printf("%s\n", (char*)data);
      } 
      else 
      {
        for (size_t i=0; i < info->len; i++)
        {
          Serial.printf("%02x ", data[i]);
        }
        
        Serial.printf("\n");
      }
      
      if (info->opcode == WS_TEXT)
        client->text("I got your text message");
      else
        client->binary("I got your binary message");
    } 
    else 
    {
      //message is comprised of multiple frames or the frame is split into multiple packets
      if (info->index == 0)
      {
        if (info->num == 0)
          Serial.printf("ws[%s][%u] %s-message start\n", server->url(), client->id(), (info->message_opcode == WS_TEXT)?"text":"binary");
          
        Serial.printf("ws[%s][%u] frame[%u] start[%llu]\n", server->url(), client->id(), info->num, info->len);
      }

      Serial.printf("ws[%s][%u] frame[%u] %s[%llu - %llu]: ", server->url(), client->id(), info->num, (info->message_opcode == WS_TEXT)?"text":"binary", info->index, info->index + len);
      
      if (info->message_opcode == WS_TEXT)
      {
        data[len] = 0;
        Serial.printf("%s\n", (char*)data);
      } 
      else 
      {
        for (size_t i=0; i < len; i++){
          Serial.printf("%02x ", data[i]);
        }
        Serial.printf("\n");
      }

      if ((info->index + len) == info->len)
      {
        Serial.printf("ws[%s][%u] frame[%u] end[%llu]\n", server->url(), client->id(), info->num, info->len);
        
        if (info->final)
        {
          Serial.printf("ws[%s][%u] %s-message end\n", server->url(), client->id(), (info->message_opcode == WS_TEXT)?"text":"binary");
          
          if (info->message_opcode == WS_TEXT)
            client->text("I got your text message");
          else
            client->binary("I got your binary message");
        }
      }
    }
  }
}
```

### Methods for sending data to a socket client

```cpp
//Server methods
AsyncWebSocket ws("/ws");
//printf to a client
ws.printf((uint32_t)client_id, arguments...);
//printf to all clients
ws.printfAll(arguments...);
//send text to a client
ws.text((uint32_t)client_id, (char*)text);
ws.text((uint32_t)client_id, (uint8_t*)text, (size_t)len);
//send text to all clients
ws.textAll((char*)text);
ws.textAll((uint8_t*)text, (size_t)len);
//send binary to a client
ws.binary((uint32_t)client_id, (char*)binary);
ws.binary((uint32_t)client_id, (uint8_t*)binary, (size_t)len);
ws.binary((uint32_t)client_id, flash_binary, 4);
//send binary to all clients
ws.binaryAll((char*)binary);
ws.binaryAll((uint8_t*)binary, (size_t)len);
//HTTP Authenticate before switch to Websocket protocol
ws.setAuthentication("user", "pass");

//client methods
AsyncWebSocketClient * client;
//printf
client->printf(arguments...);
//send text
client->text((char*)text);
client->text((uint8_t*)text, (size_t)len);
//send binary
client->binary((char*)binary);
client->binary((uint8_t*)binary, (size_t)len);
```

### Direct access to web socket message buffer

When sending a web socket message using the above methods a buffer is created.  Under certain circumstances you might want to manipulate or populate this buffer directly from your application, for example to prevent unnecessary duplications of the data.  This example below shows how to create a buffer and print data to it from an ArduinoJson object then send it.

```cpp
void sendDataWs(AsyncWebSocketClient * client)
{
    DynamicJsonBuffer jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    root["a"] = "abc";
    root["b"] = "abcd";
    root["c"] = "abcde";
    root["d"] = "abcdef";
    root["e"] = "abcdefg";
    size_t len = root.measureLength();
    AsyncWebSocketMessageBuffer * buffer = ws.makeBuffer(len); //  creates a buffer (len + 1) for you.
    
    if (buffer) 
    {
        root.printTo((char *)buffer->get(), len + 1);
        
        if (client) 
        {
            client->text(buffer);
        } 
        else 
        {
            ws.textAll(buffer);
        }
    }
}
```

### Limiting the number of web socket clients

Browsers sometimes do not correctly close the websocket connection, even when the close() function is called in javascript.  This will eventually exhaust the web server's resources and will cause the server to crash.  Periodically calling the cleanClients() function from the main loop() function limits the number of clients by closing the oldest client when the maximum number of clients has been exceeded.  This can called be every cycle, however, if you wish to use less power, then calling as infrequently as once per second is sufficient.

```cpp
void loop()
{
  ws.cleanupClients();
}
```

---

## Async Event Source Plugin

The server includes EventSource (Server-Sent Events) plugin which can be used to send short text events to the browser.
Difference between EventSource and WebSockets is that EventSource is single direction, text-only protocol.

### Setup Event Source on the server

```cpp
AsyncWebServer server(80);
AsyncEventSource events("/events");

void setup()
{
  // setup ......
  events.onConnect([](AsyncEventSourceClient *client)
  {
    if (client->lastId())
    {
      Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
    }
    
    //send event with message "hello!", id current millis
    // and set reconnect delay to 1 second
    client->send("hello!",NULL,millis(),1000);
  });
  
  //HTTP Basic authentication
  events.setAuthentication("user", "pass");
  server.addHandler(&events);
  // setup ......
}

void loop()
{
  if (eventTriggered)
  { 
    // your logic here
    //send event "myevent"
    events.send("my event content","myevent",millis());
  }
}
```

### Setup Event Source in the browser

```javascript
if (!!window.EventSource) 
{
  var source = new EventSource('/events');

  source.addEventListener('open', function(e) 
  {
    console.log("Events Connected");
  }, false);

  source.addEventListener('error', function(e) 
  {
    if (e.target.readyState != EventSource.OPEN) 
    {
      console.log("Events Disconnected");
    }
  }, false);

  source.addEventListener('message', function(e) 
  {
    console.log("message", e.data);
  }, false);

  source.addEventListener('myevent', function(e) 
  {
    console.log("myevent", e.data);
  }, false);
}
```
---

## Remove handlers and rewrites

Server goes through handlers in same order as they were added. You can't simple add handler with same path to override them.
To remove handler:

```arduino
// save callback for particular URL path
auto handler = server.on("/some/path", [](AsyncWebServerRequest *request)
{
  //do something useful
});

// when you don't need handler anymore remove it
server.removeHandler(&handler);

// same with rewrites
server.removeRewrite(&someRewrite);

server.onNotFound([](AsyncWebServerRequest *request)
{
  request->send(404);
});

// remove server.onNotFound handler
server.onNotFound(NULL);

// remove all rewrites, handlers and onNotFound/onFileUpload/onRequestBody callbacks
server.reset();
```
---

## Setting up the server

```cpp
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

#define LED_OFF             HIGH
#define LED_ON              LOW

#define BUFFER_SIZE         64
char temp[BUFFER_SIZE];

void handleRoot(AsyncWebServerRequest *request)
{
  digitalWrite(LED_BUILTIN, LED_ON);

  snprintf(temp, BUFFER_SIZE - 1, "Hello from Async_HelloServer on %s\n", BOARD_NAME);
  request->send(200, "text/plain", temp);
  
  digitalWrite(LED_BUILTIN, LED_OFF);
}

void handleNotFound(AsyncWebServerRequest *request)
{
  digitalWrite(LED_BUILTIN, LED_ON);
  
  String message = "File Not Found\n\n";

  message += "URI: ";
  //message += server.uri();
  message += request->url();
  message += "\nMethod: ";
  message += (request->method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += request->args();
  message += "\n";

  for (uint8_t i = 0; i < request->args(); i++)
  {
    message += " " + request->argName(i) + ": " + request->arg(i) + "\n";
  }

  request->send(404, "text/plain", message);
  digitalWrite(LED_BUILTIN, LED_OFF);
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LED_OFF);

  Serial.begin(115200);
  while (!Serial);

  delay(200);

  Serial.print("\nStart Async_HelloServer on "); Serial.print(BOARD_NAME);
  Serial.print(" with "); Serial.println(SHIELD_TYPE);
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
    handleRoot(request);
  });

  server.on("/inline", [](AsyncWebServerRequest * request)
  {
    request->send(200, "text/plain", "This works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();

  Serial.print(F("HTTP EthernetWebServer is @ IP : "));
  Serial.println(Ethernet.localIP());
}

void loop(void)
{
}
```
---

### Setup global and class functions as request handlers

```cpp
#include <Arduino.h>

#define USE_ETHERNET_PORTENTA_H7        true

#include <Portenta_Ethernet.h>
#include <Ethernet.h>
#warning Using Portenta_Ethernet lib for Portenta_H7.

#include <Portenta_H7_AsyncWebServer.h>

#include <functional>

...

void handleRequest(AsyncWebServerRequest *request){}

class WebClass 
{
public :
  AsyncWebServer classWebServer = AsyncWebServer(81);

  WebClass(){};

  void classRequest (AsyncWebServerRequest *request){}

  void begin()
  {
    // attach global request handler
    classWebServer.on("/example", HTTP_ANY, handleRequest);

    // attach class request handler
    classWebServer.on("/example", HTTP_ANY, std::bind(&WebClass::classRequest, this, std::placeholders::_1));
  }
};

AsyncWebServer globalWebServer(80);
WebClass webClassInstance;

void setup() 
{
  // attach global request handler
  globalWebServer.on("/example", HTTP_ANY, handleRequest);

  // attach class request handler
  globalWebServer.on("/example", HTTP_ANY, std::bind(&WebClass::classRequest, webClassInstance, std::placeholders::_1));
}

void loop() 
{

}
```

### Methods for controlling websocket connections

```cpp
  // Disable client connections if it was activated
  if ( ws.enabled() )
    ws.enable(false);

  // enable client connections if it was disabled
  if ( !ws.enabled() )
    ws.enable(true);
```


### Adding Default Headers

In some cases, such as when working with CORS, or with some sort of custom authentication system, 
you might need to define a header that should get added to all responses (including static, websocket and EventSource).
The DefaultHeaders singleton allows you to do this.

Example:

```cpp
DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
webServer.begin();
```

*NOTE*: You will still need to respond to the OPTIONS method for CORS pre-flight in most cases. (unless you are only using GET)

This is one option:

```cpp
webServer.onNotFound([](AsyncWebServerRequest *request) 
{
  if (request->method() == HTTP_OPTIONS) 
  {
    request->send(200);
  } 
  else 
  {
    request->send(404);
  }
});
```

### Path variable

With path variable you can create a custom regex rule for a specific parameter in a route. 
For example we want a `sensorId` parameter in a route rule to match only a integer.

```cpp
server.on("^\\/sensor\\/([0-9]+)$", HTTP_GET, [] (AsyncWebServerRequest *request) 
{
    String sensorId = request->pathArg(0);
});
```
*NOTE*: All regex patterns starts with `^` and ends with `$`

To enable the `Path variable` support, you have to define the buildflag `-DASYNCWEBSERVER_REGEX`.


For Arduino IDE create/update `platform.local.txt`:

`Windows`: C:\Users\(username)\AppData\Local\Arduino15\packages\\`{espxxxx}`\hardware\\`espxxxx`\\`{version}`\platform.local.txt

`Linux`: ~/.arduino15/packages/`{espxxxx}`/hardware/`{espxxxx}`/`{version}`/platform.local.txt

Add/Update the following line:

```
  compiler.cpp.extra_flags=-DDASYNCWEBSERVER_REGEX
```

For platformio modify `platformio.ini`:

```ini
[env:myboard]
build_flags = 
  -DASYNCWEBSERVER_REGEX
```

*NOTE*: By enabling `ASYNCWEBSERVER_REGEX`, `<regex>` will be included. This will add an 100k to your binary.


---
---

### Examples

#### 1. For Vision-shield Ethernet

 1. [Async_AdvancedWebServer](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/Async_AdvancedWebServer)
 2. [Async_HelloServer](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/Async_HelloServer) 
 3. [Async_HelloServer2](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/Async_HelloServer2)
 4. [Async_HttpBasicAuth](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/Async_HttpBasicAuth)
 5. [Async_PostServer](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/Async_PostServer)
 6. [**MQTTClient_Auth**](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/MQTTClient_Auth)
 7. [**MQTTClient_Basic**](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/MQTTClient_Basic)
 8. [**MQTT_ThingStream**](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/MQTT_ThingStream)
 9. [WebClient](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/WebClient)
10. [WebClientRepeating](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/WebClientRepeating)
11. [Async_AdvancedWebServer_MemoryIssues_SendArduinoString](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/Async_AdvancedWebServer_MemoryIssues_SendArduinoString) **New**
12. [Async_AdvancedWebServer_MemoryIssues_Send_CString](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/Async_AdvancedWebServer_MemoryIssues_Send_CString) **New**
13. [Async_AdvancedWebServer_SendChunked](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/Async_AdvancedWebServer_SendChunked) **New**
14. [AsyncWebServer_SendChunked](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/AsyncWebServer_SendChunked) **New**


#### 2. For Murata WiFi

 1. [Async_AdvancedWebServer](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/WiFi/Async_AdvancedWebServer)
 2. [Async_HelloServer](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/WiFi/Async_HelloServer) 
 3. [Async_HelloServer2](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/WiFi/Async_HelloServer2)
 4. [Async_HttpBasicAuth](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/WiFi/Async_HttpBasicAuth)
 5. [Async_PostServer](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/WiFi/Async_PostServer)
 6. [**MQTTClient_Auth**](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/WiFi/MQTTClient_Auth)
 7. [**MQTTClient_Basic**](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/WiFi/MQTTClient_Basic)
 8. [**MQTT_ThingStream**](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/WiFi/MQTT_ThingStream)
 9. [WebClient](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/WiFi/WebClient)
10. [WebClientRepeating](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/WiFi/WebClientRepeating)
11. [Async_AdvancedWebServer_MemoryIssues_Send_CString](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/WiFi/Async_AdvancedWebServer_MemoryIssues_Send_CString) **New**
12. [Async_AdvancedWebServer_SendChunked](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/WiFi/Async_AdvancedWebServer_SendChunked) **New**
13. [AsyncWebServer_SendChunked](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/WiFi/AsyncWebServer_SendChunked) **New**

---
---

### Example [Async_AdvancedWebServer](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/Async_AdvancedWebServer)

https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/blob/c9d68052df24e2cb959acaf89ae0ce830d67aca3/examples/WiFi/Async_AdvancedWebServer/Async_AdvancedWebServer.ino#L41-L273

You can access the Async Advanced WebServer @ the server IP

<p align="center">
    <img src="https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/raw/main/pics/Async_AdvancedWebServer.png">
</p>

---
---

### Debug Terminal Output Samples

#### 1. MQTT_ThingStream on PORTENTA_H7_M7 using Ethernet

Following is debug terminal output when running example [MQTT_ThingStream](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/MQTT_ThingStream) on PORTENTA_H7_M7 using Ethernet and Portenta_Ethernet Library


```
Start MQTT_ThingStream on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
Portenta_H7_AsyncTCP v1.4.0
Portenta_H7_AsyncWebServer v1.5.0
Using mac index = 17
Connected! IP address: 192.168.2.87
***************************************
STM32_Pub
***************************************
Attempting MQTT connection to broker.emqx.io
...connected
Published connection message successfully!
Subscribed to: STM32_Sub
MQTT Message Send : STM32_Pub => Hello from MQTT_ThingStream on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
MQTT Message receive [STM32_Pub] Hello from MQTT_ThingStream on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
MQTT Message Send : STM32_Pub => Hello from MQTT_ThingStream on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
MQTT Message receive [STM32_Pub] Hello from MQTT_ThingStream on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
```

---

#### 2. WebClientRepeating on PORTENTA_H7_M7 using Ethernet

Following is debug terminal output when running example [WebClient](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/WebClientRepeating) on on PORTENTA_H7_M7 using Ethernet and Portenta_Ethernet Library

```
Start WebClientRepeating on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
Portenta_H7_AsyncTCP v1.4.0
Portenta_H7_AsyncWebServer v1.5.0
Using mac index = 16
Connected! IP address: 192.168.2.87

Connecting...
HTTP/1.1 200 OK
Server: nginx/1.4.2
Date: Thu, 07 Oct 2021 05:16:59 GMT
Content-Type: text/plain
Content-Length: 2263
Last-Modified: Wed, 02 Oct 2013 13:46:47 GMT
Connection: close
Vary: Accept-Encoding
ETag: "524c23c7-8d7"
Accept-Ranges: bytes


           `:;;;,`                      .:;;:.           
        .;;;;;;;;;;;`                :;;;;;;;;;;:     TM 
      `;;;;;;;;;;;;;;;`            :;;;;;;;;;;;;;;;      
     :;;;;;;;;;;;;;;;;;;         `;;;;;;;;;;;;;;;;;;     
    ;;;;;;;;;;;;;;;;;;;;;       .;;;;;;;;;;;;;;;;;;;;    
   ;;;;;;;;:`   `;;;;;;;;;     ,;;;;;;;;.`   .;;;;;;;;   
  .;;;;;;,         :;;;;;;;   .;;;;;;;          ;;;;;;;  
  ;;;;;;             ;;;;;;;  ;;;;;;,            ;;;;;;. 
 ,;;;;;               ;;;;;;.;;;;;;`              ;;;;;; 
 ;;;;;.                ;;;;;;;;;;;`      ```       ;;;;;`
 ;;;;;                  ;;;;;;;;;,       ;;;       .;;;;;
`;;;;:                  `;;;;;;;;        ;;;        ;;;;;
,;;;;`    `,,,,,,,,      ;;;;;;;      .,,;;;,,,     ;;;;;
:;;;;`    .;;;;;;;;       ;;;;;,      :;;;;;;;;     ;;;;;
:;;;;`    .;;;;;;;;      `;;;;;;      :;;;;;;;;     ;;;;;
.;;;;.                   ;;;;;;;.        ;;;        ;;;;;
 ;;;;;                  ;;;;;;;;;        ;;;        ;;;;;
 ;;;;;                 .;;;;;;;;;;       ;;;       ;;;;;,
 ;;;;;;               `;;;;;;;;;;;;                ;;;;; 
 `;;;;;,             .;;;;;; ;;;;;;;              ;;;;;; 
  ;;;;;;:           :;;;;;;.  ;;;;;;;            ;;;;;;  
   ;;;;;;;`       .;;;;;;;,    ;;;;;;;;        ;;;;;;;:  
    ;;;;;;;;;:,:;;;;;;;;;:      ;;;;;;;;;;:,;;;;;;;;;;   
    `;;;;;;;;;;;;;;;;;;;.        ;;;;;;;;;;;;;;;;;;;;    
      ;;;;;;;;;;;;;;;;;           :;;;;;;;;;;;;;;;;:     
       ,;;;;;;;;;;;;;,              ;;;;;;;;;;;;;;       
         .;;;;;;;;;`                  ,;;;;;;;;:         
                                                         
                                                         
                                                         
                                                         
    ;;;   ;;;;;`  ;;;;:  .;;  ;; ,;;;;;, ;;. `;,  ;;;;   
    ;;;   ;;:;;;  ;;;;;; .;;  ;; ,;;;;;: ;;; `;, ;;;:;;  
   ,;:;   ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;,`;, ;;  ;;  
   ;; ;:  ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;;`;, ;;  ;;. 
   ;: ;;  ;;;;;:  ;;  ;; .;;  ;;   ,;,   ;;`;;;, ;;  ;;` 
  ,;;;;;  ;;`;;   ;;  ;; .;;  ;;   ,;,   ;; ;;;, ;;  ;;  
  ;;  ,;, ;; .;;  ;;;;;:  ;;;;;: ,;;;;;: ;;  ;;, ;;;;;;  
  ;;   ;; ;;  ;;` ;;;;.   `;;;:  ,;;;;;, ;;  ;;,  ;;;; 
```

---


#### 3. MQTTClient_Auth on PORTENTA_H7_M7 using Ethernet

Following is debug terminal output when running example [MQTTClient_Auth](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/MQTTClient_Auth) on on PORTENTA_H7_M7 using Ethernet and Portenta_Ethernet Library

```
Start MQTTClient_Auth on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
Portenta_H7_AsyncTCP v1.4.0
Portenta_H7_AsyncWebServer v1.5.0
Using mac index = 9
Connected! IP address: 192.168.2.87
Attempting MQTT connection to broker.emqx.io...connected
Message Send : MQTT_Pub => Hello from MQTTClient_Auth on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
Message arrived [MQTT_Pub] Hello from MQTTClient_Auth on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
Message Send : MQTT_Pub => Hello from MQTTClient_Auth on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
Message arrived [MQTT_Pub] Hello from MQTTClient_Auth on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
Message Send : MQTT_Pub => Hello from MQTTClient_Auth on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
Message arrived [MQTT_Pub] Hello from MQTTClient_Auth on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
```

---

#### 4. MQTTClient_Basic on PORTENTA_H7_M7 using Ethernet

Following is debug terminal output when running example [MQTTClient_Basic](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/MQTTClient_Basic) on on PORTENTA_H7_M7 using Ethernet and Portenta_Ethernet Library

```
Start MQTTClient_Basic on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
Portenta_H7_AsyncTCP v1.4.0
Portenta_H7_AsyncWebServer v1.5.0
Using mac index = 8
Connected! IP address: 192.168.2.87
Attempting MQTT connection to broker.emqx.io...connected
Message Send : MQTT_Pub => Hello from MQTTClient_Basic on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
Message arrived [MQTT_Pub] Hello from MQTTClient_Basic on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
Message Send : MQTT_Pub => Hello from MQTTClient_Basic on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
Message arrived [MQTT_Pub] Hello from MQTTClient_Basic on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
```

---

#### 5. Async_HTTPBasicAuth on PORTENTA_H7_M7 using Ethernet

Following is debug terminal output when running example [Async_HTTPBasicAuth](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/Async_HTTPBasicAuth) on PORTENTA_H7_M7 using Ethernet and Portenta_Ethernet Library

```
Start Async_HTTPBasicAuth on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
Portenta_H7_AsyncTCP v1.4.0
Portenta_H7_AsyncWebServer v1.5.0
Using mac index = 16
Connected! IP address: 192.168.2.87
Async_HttpBasicAuth started @ IP : 192.168.2.87
Open http://192.168.2.87/ in your browser to see it working
Login using username = admin and password = ethernet
[AWS] getMD5: Success
[AWS] genRandomMD5: res =  795d0e2e77f0bd1ac56d88a223e30cc8
[AWS] getMD5: Success
[AWS] genRandomMD5: res =  0bc073c1bf61fa0ae678fa5892cfd2a6
[AWS] requestDigestAuthentication: header =  realm="asyncesp", qop="auth", nonce="795d0e2e77f0bd1ac56d88a223e30cc8", opaque="0bc073c1bf61fa0ae678fa5892cfd2a6"
[AWS] getMD5: Success
[AWS] stringMD5: res =  9384b554a02515c9481a13b3787821da
[AWS] getMD5: Success
[AWS] stringMD5: res =  71998c64aea37ae77020c49c00f73fa8
[AWS] getMD5: Success
[AWS] stringMD5: res =  5908212c923b4d99fd278772873a142f
[AWS] AUTH SUCCESS
```

---

#### 6. Async_AdvancedWebServer on PORTENTA_H7_M7 using Ethernet

Following are debug terminal output and screen shots when running example [Async_AdvancedWebServer](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/Async_AdvancedWebServer) on PORTENTA_H7_M7 using Ethernet and Portenta_Ethernet Library to demonstrate the complex AsyncWebServer feature.


```
Start Async_AdvancedWebServer on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
Portenta_H7_AsyncTCP v1.4.0
Portenta_H7_AsyncWebServer v1.5.0
Using mac index = 4
Connected! IP address: 192.168.2.87
HTTP EthernetWebServer is @ IP : 192.168.2.87
```

You can access the Async Advanced WebServers at the displayed server IP, e.g. `192.168.2.87`

<p align="center">
    <img src="https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/raw/main/pics/Async_AdvancedWebServer.png">
</p>

#### Using Firefox Browser

<p align="center">
    <img src="https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/raw/main/pics/Async_AdvancedWebServer_Firefox.png">
</p>

---

#### 7. Async_AdvancedWebServer on PORTENTA_H7_M7 using WiFi

Following is the debug terminal and screen shot when running example [Async_AdvancedWebServer](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/WiFi/Async_AdvancedWebServer) on Portenta_H7 WiFi to demonstrate the operation of Portenta_H7_AsyncWebServer, based on this [Portenta_H7_AsyncTCP Library](https://github.com/khoih-prog/Portenta_H7_AsyncTCP).

```
Start Async_AdvancedWebServer on PORTENTA_H7_M7 with Portenta_H7 WiFi
Portenta_H7_AsyncTCP v1.4.0
Portenta_H7_AsyncWebServer v1.5.0
Connecting to SSID: HueNet1
SSID: HueNet1
Local IP Address: 192.168.2.94
signal strength (RSSI):-31 dBm
HTTP EthernetWebServer is @ IP : 192.168.2.94
..........
```

You can access the Async Advanced WebServers at the displayed server IP, e.g. `192.168.2.94`

<p align="center">
    <img src="https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/raw/main/pics/Async_AdvancedWebServer_WiFi.png">
</p>

---

#### 8. Async_AdvancedWebServer_MemoryIssues_Send_CString on PORTENTA_H7_M7 using Ethernet

Following is the debug terminal and screen shot when running example [Async_AdvancedWebServer_MemoryIssues_Send_CString](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/Async_AdvancedWebServer_MemoryIssues_Send_CString) on Portenta_H7 Ethernet to demonstrate the new and powerful `HEAP-saving` feature


##### Using SDRAM => not using HEAP (14,314 bytes)

```
Start Async_AdvancedWebServer_MemoryIssues_Send_CString using SDRAM on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
Portenta_H7_AsyncTCP v1.4.0
Portenta_H7_AsyncWebServer v1.5.0
Using mac index = 2
Connected! IP address: 192.168.2.123
HTTP EthernetWebServer is @ IP : 192.168.2.123

HEAP DATA - Pre Create Arduino String  Cur heap: 8458  Res Size: 451648  Max heap: 8472
.
HEAP DATA - Pre Send  Cur heap: 9634  Res Size: 451648  Max heap: 10196

HEAP DATA - Post Send  Cur heap: 9734  Res Size: 451648  Max heap: 12847
......... .......... .......... .......... .......... .......... .......... ..........
Out String Length=31200
.......... .......... .......... .......... .......... .......... .......... ..........
Out String Length=31219
.......... .......... .......... .......... .......... .......... .......... ..........
Out String Length=31255
.......... .......... .......... .......... .......... .......... .......... ..........
Out String Length=31198
.......... .......... .......... .......... .......... .......... .......... ........
HEAP DATA - Post Send  Cur heap: 11201  Res Size: 451648  Max heap: 14314
..
Out String Length=31224
.......... .......... .......... .......... .......... .......... .......... ..........
Out String Length=31235
```

##### Not using SDRAM  ===> small heap (51,833 bytes)

```
Start Async_AdvancedWebServer_MemoryIssues_Send_CString on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
Portenta_H7_AsyncTCP v1.4.0
Portenta_H7_AsyncWebServer v1.5.0
Using mac index = 7
Connected! IP address: 192.168.2.38
HTTP EthernetWebServer is @ IP : 192.168.2.38

HEAP DATA - Pre Create Arduino String  Cur heap: 47434  Res Size: 451760  Max heap: 47448
.
HEAP DATA - Pre Send  Cur heap: 48607  Res Size: 451760  Max heap: 49811

HEAP DATA - Post Send  Cur heap: 48720  Res Size: 451760  Max heap: 51833
......... .......... .......... .......... .......... ....
Out String Length=31200
.......... .......... .......... .......... .......... .......... .......... ..........
Out String Length=31291
```

While using Arduino String, the HEAP usage is very large


#### Async_AdvancedWebServer_MemoryIssues_SendArduinoString  ===> very large heap (111,387 bytes)



```
Start Async_AdvancedWebServer_MemoryIssues_SendArduinoString on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
Portenta_H7_AsyncTCP v1.4.0
Portenta_H7_AsyncWebServer v1.5.0
Using mac index = 0
Connected! IP address: 192.168.2.123
HTTP EthernetWebServer is @ IP : 192.168.2.123

HEAP DATA - Pre Create Arduino String  Cur heap: 7434  Res Size: 452016  Max heap: 7448
.
HEAP DATA - Pre Send  Cur heap: 48611  Res Size: 452016  Max heap: 48611

HEAP DATA - Post Send  Cur heap: 79009  Res Size: 452016  Max heap: 111347
.
HEAP DATA - Post Send  Cur heap: 79029  Res Size: 452016  Max heap: 111387
...
HEAP DATA - Post Send  Cur heap: 79037  Res Size: 452016  Max heap: 111403
....
HEAP DATA - Post Send  Cur heap: 79041  Res Size: 452016  Max heap: 111411
. ..
Out String Length=31247
.......
HEAP DATA - Post Send  Cur heap: 79047  Res Size: 452016  Max heap: 111423
. ....
Out String Length=31233
...... ......
Out String Length=31243
.... .......
Out String Length=31251
... .......
HEAP DATA - Post Send  Cur heap: 79054  Res Size: 452016  Max heap: 111437
..
Out String Length=31280
. ......
```


You can access the Async Advanced WebServers at the displayed server IP, e.g. `192.168.2.123`

<p align="center">
    <img src="https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/raw/main/pics/Async_AdvancedWebServer_CString.png">
</p>


---

#### 9. Async_AdvancedWebServer_SendChunked on PORTENTA_H7_M7 using WiFi

Following is debug terminal output when running example [Async_AdvancedWebServer_SendChunked](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/WiFi/Async_AdvancedWebServer_SendChunked) on PORTENTA_H7_M7 using WiFi, to demo how to use `beginChunkedResponse()` to send large `html` in chunks


```
Start Async_AdvancedWebServer_SendChunked on PORTENTA_H7_M7 with Portenta_H7 WiFi
Portenta_H7_AsyncTCP v1.4.0
Portenta_H7_AsyncWebServer v1.5.0
Connecting to SSID: HueNet1
SSID: HueNet1
Local IP Address: 192.168.2.113
signal strength (RSSI):-31 dBm
AsyncWebServer is @ IP : 192.168.2.113
.[AWS] Total length to send in chunks = 31259
[AWS] Bytes sent in chunk = 948
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
.[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
.[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
.[AWS] Bytes sent in chunk = 519
[AWS] Bytes sent in chunk = 0
```


You can access the Portenta_H7_AsyncWebServer at the displayed server IP

<p align="center">
    <img src="https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/raw/main/pics/AsyncWebServer_SendChunked_WiFi.png">
</p>
  
  
---
 
  
#### 10. Async_AdvancedWebServer_SendChunked on PORTENTA_H7_M7 using Ethernet

Following is debug terminal output when running example [Async_AdvancedWebServer_SendChunked](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Ethernet/Async_AdvancedWebServer_SendChunked) on PORTENTA_H7_M7 using Ethernet and Portenta_Ethernet Library , to demo how to use `beginChunkedResponse()` to send large `html` in chunks


```
Start Async_AdvancedWebServer_SendChunked on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
Portenta_H7_AsyncTCP v1.4.0
Portenta_H7_AsyncWebServer v1.5.0
Using mac index = 3
Connected! IP address: 192.168.2.89
AsyncWebServer is @ IP : 192.168.2.89
.[AWS] Total length to send in chunks = 31259
[AWS] Bytes sent in chunk = 948
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 519
[AWS] Bytes sent in chunk = 0
.[AWS] Total length to send in chunks = 31279
[AWS] Bytes sent in chunk = 948
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 1064
[AWS] Bytes sent in chunk = 539
[AWS] Bytes sent in chunk = 0
```


You can access the Portenta_H7_AsyncWebServer at the displayed server IP

<p align="center">
    <img src="https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/raw/main/pics/AsyncWebServer_SendChunked_Ethernet.png">
</p>
    
  
  
---
---

### Debug

Debug is enabled by default on Serial.

You can also change the debugging level `_PORTENTA_H7_AWS_LOGLEVEL_` from 0 to 4 in the library `cpp` files

```cpp
#define _PORTENTA_H7_AWS_LOGLEVEL_     1
```

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of Arduino IDE, the Arduino `mbed_portenta` core or depending libraries.

Sometimes, the library will only work if you update the `mbed_portenta` core to the latest version because I'm always using the latest cores /libraries.


---

### Issues ###

Submit issues to: [Portenta_H7_AsyncWebServer issues](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/issues)

---
---

## TO DO

 1. Fix bug. Add enhancement
 2. Add support to `Murata` WiFi


## DONE

 1. Add support to Portenta_H7 using `Vision-shield Ethernet`
 2. Add Table of Contents
 3. Fix issue with slow browsers or network. Check [Target stops responding after variable time when using Firefox on Windows 10 #3](https://github.com/khoih-prog/AsyncWebServer_RP2040W/issues/3)
 4. Support using `CString` in optional `SDRAM` to save heap to send `very large data`. Check [request->send(200, textPlainStr, jsonChartDataCharStr); - Without using String Class - to save heap #8](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/pull/8)
 5. Add examples [Async_AdvancedWebServer_SendChunked](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/Async_AdvancedWebServer_SendChunked) and [AsyncWebServer_SendChunked](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/tree/main/examples/AsyncWebServer_SendChunked) to demo how to use `beginChunkedResponse()` to send large `html` in chunks
 6. Use `allman astyle` and add `utils`
 7. Fix `_catchAllHandler` not working bug.
 8. Improve `README.md` so that links can be used in other sites, such as `PIO`
 
---
---

### Contributions and Thanks

1. Based on and modified from [Hristo Gochkov's ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer). Many thanks to [Hristo Gochkov](https://github.com/me-no-dev) for great [ESPAsyncWebServer Library](https://github.com/me-no-dev/ESPAsyncWebServer)
2. Thanks to [rusty-bit](https://github.com/rusty-bit) to initiate the Discussion in [**AsyncWebserver for Portenta H7** #6](https://github.com/khoih-prog/AsyncWebServer_STM32/discussions/6) leading to these [Portenta_H7_AsyncTCP](https://github.com/khoih-prog/Portenta_H7_AsyncTCP) and [Portenta_H7_AsyncWebServer](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer) libraries
3. Thanks to [Jeremy Ellis](https://github.com/hpssjellis) to test and report the compile error and crash issue with mbed_portenta core v2.6.1, leading to v1.2.0
4. Thanks to [salasidis](https://github.com/salasidis) aka [rs77can](https://forum.arduino.cc/u/rs77can) to discuss and make the following marvellous PRs
- [request->send(200, textPlainStr, jsonChartDataCharStr); - Without using String Class - to save heap #8](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/pull/8), leading to `v1.4.0` to support using `CString` in optional `SDRAM` to save heap to send `very large data`
- [All memmove() removed - string no longer destroyed #11](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/pull/11), leading to `v1.4.1` to remove `memmove()` and not to destroy String anymore
5. Thanks to [roma2580](https://github.com/roma2580) to report and help fix the bug in 
- [catchAll handler not working #12](https://github.com/khoih-prog/AsyncWebServer_RP2040W/issues/12)
leading to `v1.5.0` to fix `_catchAllHandler` not working bug

<table>
  <tr>
    <td align="center"><a href="https://github.com/me-no-dev"><img src="https://github.com/me-no-dev.png" width="100px;" alt="me-no-dev"/><br /><sub><b>⭐️⭐️ Hristo Gochkov</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/rusty-bit"><img src="https://github.com/rusty-bit.png" width="100px;" alt="rusty-bit"/><br /><sub><b>rusty-bit</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/hpssjellis"><img src="https://github.com/hpssjellis.png" width="100px;" alt="hpssjellis"/><br /><sub><b>Jeremy Ellis</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/salasidis"><img src="https://github.com/salasidis.png" width="100px;" alt="salasidis"/><br /><sub><b>⭐️ salasidis</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/roma2580"><img src="https://github.com/roma2580.png" width="100px;" alt="roma2580"/><br /><sub><b>>⭐️ roma2580</b></sub></a><br /></td>
  </tr> 
</table>

---

### Contributing

If you want to contribute to this project:

- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [GPLv3](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/blob/main/LICENSE)

---

## Copyright

Copyright 2021- Khoi Hoang



