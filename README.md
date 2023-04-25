Arduino Web Server with WiFi
============================

This is a simple Arduino sketch that sets up a web server on an ESP8266 module with WiFi connectivity. When a user accesses the IP address of the module from their web browser, they will be greeted with a "Hello" message.

Hardware Requirements
---------------------

-   ESP8266 module
-   WiFi network
-   Computer or device with a web browser

Wiring Instructions
-------------------

No wiring is required for this basic example.

Installation and Usage
----------------------

1.  Copy the code into the Arduino IDE
2.  Change the `ssid` and `password` variables to match your WiFi network credentials
3.  Upload the code to the ESP8266 module
4.  Open the Serial Monitor to verify that the module has connected to the WiFi network
5.  Open a web browser and enter the IP address of the module
6.  You should see a "Hello" message displayed in your web browser

Note
----

If you plan to use this code for your own projects, you will need to create a virtual server on your router and use the IP address of the ESP8266 module to connect to it using port 80.

Credits
-------

This code was adapted from the ESP8266WebServer example included with the ESP8266WiFi library.


![image](https://user-images.githubusercontent.com/26854208/234386492-ef6fadd5-ee1f-46c7-b1b3-28d2cee84111.png)
