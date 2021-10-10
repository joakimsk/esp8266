<h1 align="center"> ESP8266 and family </h1> <br>
<p align="center">
  <a href="https://en.wikipedia.org/wiki/ESP8266">
    <img alt="ESP8266" title="ESP8266" src="https://upload.wikimedia.org/wikipedia/commons/8/84/ESP-01.jpg" width="450">
  </a>
</p>

<p align="center">
  The whole family, doing funky wifi stuff.
</p>

## Table of Contents

- [Introduction](##introduction)


## Introduction
This repo contains useful stuff regarding the ESP8266. Intention is to keep all useful stuff in one place, as well as some code.
The ESP8266 is a Low-cost Wi-Fi microchip. Produced by Espressif Systems in Shanghai, China. Can be programmed using Arduino IDE.

## Hardware modules

### Third-party manufacturer Ai-Thinker
- ESP01
- ESP07
- ESP12

Read more here [https://en.wikipedia.org/wiki/ESP8266#Espressif_modules]

### By others
- NodeMCU

## ESP01 in detail
Pinout:
1. GND, Ground (0 V)
2. GPIO 2, General-purpose input/output No. 2
3. GPIO 0, General-purpose input/output No. 0
4. RX, Receive data in, also GPIO3
5. VCC, Voltage (+3.3 V; can handle up to 3.6 V)
6. RST, Reset
7. CH_PD, Chip power-down
8. TX, Transmit data out, also GPIO1

<p align="center">
  <img src = "https://upload.wikimedia.org/wikipedia/commons/0/08/ESP8266_01_PinOut.png" width=700>
</p>

### Programming quirks
The GPIO 2 is used to set the ESP8266 into different modes. This means that if pulled down during power-on or reset, the device goes into serial bootloader instead of running the program. Unless you want to change the firmware on the device, make sure the GPIO 2 is not pulled down to ground. There is an internal pullup resistor that can be enabled. If the blue LED is continously on and you seem to get garbage out on the serial line, it is probably in serial bootloader mode.

The GPIO 0 is used to choose boot mode. Pull up to boot from SPI Flash (normal operation), or pull down to program via UART. When we upload a program, we want to pull GPIO 0 down.

The RST pin needs to be pulled down while the esptool.py tries to connect. If it connects, it should immediately start uploading the program. Afterwards, the power should be cycled, and GPIO 0 be pulled up.


### Tricks to extend ESP01
I2C is suggested to extend IO, using GPIO 0 and GPIO 2 as the I2C bus.

[https://www.forward.com.au/pfod/ESP8266/GPIOpins/ESP8266_01_pin_magic.html]