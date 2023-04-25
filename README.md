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

1. Connect the IO pin of the speaker to the D5 pin on the ESP8266 module.
2. Connect the GND pin of the speaker to the GND pin on the ESP8266 module.
3. Connect the VCC pin of the speaker to the 3.3v pin on the board.

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

If you plan to use this code for your own projects and want to access the Arduino web server from outside your local network, you will need to create a virtual server on your router and use the IP address of the ESP8266 module to connect to it using port 80.

Credits
-------

This code was adapted from the ESP8266WebServer example included with the ESP8266WiFi library.


![image](https://user-images.githubusercontent.com/26854208/234419120-4f98e8f9-8dae-42a4-a08f-d7dc5a1c9257.png)
