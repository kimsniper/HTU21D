# HTU21D - STM32

HTU21D i2c library for STM32CubeIDE.

## Overview

This example demonstrates usage of HTU21D for reading relative humidity and temperature (RH/T).

### Hardware Required

To run this example, you should have one STM32 based development board (STM32F411CEUX/black pill in my case) as well as a htu21d. The HTU21D(F) is a new digital humidity sensor with temperature output by MEAS. Setting new standards in terms of size and intelligence, it is embedded in a reflow solderable Dual Flat No leads (DFN) package with a small 3 x 3 x 0.9 mm footprint. It is easy to operate via a simple I2C command, you can read the datasheet [here](https://cdn-shop.adafruit.com/datasheets/1899_HTU21D.pdf).

## Example Output

```bash
Initializing HTU21D. . .
HTU21D init successful.
Temperature: 31.7°C
Humidity: 77.3%
Temperature: 31.7°C
Humidity: 77.3%
Temperature: 31.7°C
Humidity: 77.3%
Temperature: 31.7°C
Humidity: 77.3%
Temperature: 31.7°C
Humidity: 77.3%
Temperature: 31.7°C
Humidity: 77.4%
Temperature: 31.7°C
Humidity: 77.4%
Temperature: 31.7°C
Humidity: 77.4%
Temperature: 31.7°C
Humidity: 77.4%
```