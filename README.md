# NodeMCU MQTT Temperature

A simple project to connect a DHT22 temperature sensor to the internet using a NodeMCU and post data using MQTT.

## Parts

* NodeMCU (v3)
* DHT22

## Setup

![Wiring diagram](/assets/wiring_bb.png)

There is a shortcut between D0 and RST, this is to enable the module to go into deepsleep and wake up automatically. When flashing the NodeMCU remove this. You may also have to press the Flash button to allow uploads if you change the code.

The DHT22 is linked to pin D7, but this can be changed in the config.h if you wish.

You will also need to set your WIFI_SSID and WIFI_PASS in config.h as well as the address of your MQTT host.

There is a shortcut between D0 and RST, this is to enable the module to go into deepsleep and wake up automatically.
