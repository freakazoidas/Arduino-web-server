Arduino Web Server with WiFi and Speaker Control
================================================

This is a simple Arduino sketch that sets up a web server on an ESP8266 module with WiFi connectivity. When a user accesses the IP address of the module from their web browser, they will see the current time and have the ability to beep a connected speaker.

Hardware Requirements
---------------------

-   ESP8266 module
-   Speaker or buzzer
-   WiFi network
-   Computer or device with a web browser

Wiring Instructions
-------------------

1. Connect the IO pin of the speaker to the D5 pin.
2. Connect the GND pin of the speaker to the GND pin.
2. Connect the VCC pin of the speaker to the 3.3v pin on the board.

Installation and Usage
----------------------

1.  Copy the code into the Arduino IDE
2.  Change the `ssid` and `password` variables to match your WiFi network credentials
3.  Upload the code to the ESP8266 module
4.  Open the Serial Monitor to verify that the module has connected to the WiFi network
5.  Open a web browser and enter the IP address of the module
6.  You should see the current time displayed in your web browser and have the ability to beep the speaker

Note
----

If you plan to use this code for your own projects, you will need to create a virtual server on your router and use the IP address of the ESP8266 module to connect to it using port 80.

Credits
-------

This code was adapted from the ESP8266WebServer example included with the ESP8266WiFi library.



![image](https://user-images.githubusercontent.com/26854208/234418710-37272f1f-0c95-42d7-a6b3-8b4a1f82685c.png)

