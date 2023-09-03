# HTU21D - Gecko SDK 4.3.1

HTU21D i2c library library for Silicon Labs Gecko SDK 4.3.1.

Hardware: https://www.silabs.com/development-tools/wireless/bluetooth/bgm220-explorer-kit

## Overview

This example demonstrates usage of HTU21D for reading relative humidity and temperature (RH/T).

### Hardware Required

To run this example, you should have BGM220P Explorer Kit as well as a htu21d. The HTU21D(F) is a new digital humidity sensor with temperature output by MEAS. Setting new standards in terms of size and intelligence, it is embedded in a reflow solderable Dual Flat No leads (DFN) package with a small 3 x 3 x 0.9 mm footprint. It is easy to operate via a simple I2C command, you can read the datasheet [here](https://cdn-shop.adafruit.com/datasheets/1899_HTU21D.pdf).

#### Pin Assignment:

**Note:** The following pin assignments are used by default for BGM220P explorer kit mikro bus pins.

|                      | SDA            | SCL            |
| -------------------- | -------------- | -------------- |
| BGM220P I2C Master   | Port D, Pin 2  | Port D, Pin 3  |
| HTU21D               | SDA            | SCL            |

**Note: ** There’s no need to add an external pull-up resistors for SDA/SCL pin, because the driver will enable the internal pull-up resistors.
**Note: ** Driver is tested with Simplicity Studio 5 IDE with Gecko SDK 4.3.1. Hardware use: BGM220P Explorer kit

### Build and Flash

1. Open Simplicity Studio 5.
2. Select File > Import, and locate the folder with the project or solution to be imported.
Ex: (Folder Path)\HTU21D\examples\bgm220p_implementation
3. Select the project and click Next. If anything about the project is unresolved you can resolve it.
4. Click Next. Name the project or solution and click Finish.
5. Right click project and select Run As and select the appropriate program.
6. Open any UART terminal application and set the baudrate to 115200 with the right COM port.

(To exit the serial monitor, type ``Ctrl-]``.)

See the [Getting Started Guide](https://www.silabs.com/development-tools/wireless/bluetooth/bgm220-explorer-kit?tab=getting-started) for full steps to start with BGM220P explorer kit.

## Example Output

```bash
[I] htu21d initialization successful
[I] Temperature: 32 °C
[I] Humidity: 91 %
[I] Temperature: 32 °C
[I] Humidity: 89 %
[I] Temperature: 32 °C
[I] Humidity: 89 %
[I] Temperature: 32 °C
[I] Humidity: 88 %
[I] Temperature: 32 °C
[I] Humidity: 88 %
[I] Temperature: 32 °C
[I] Humidity: 88 %
[I] Temperature: 32 °C
[I] Humidity: 88 %
[I] Temperature: 32 °C
[I] Humidity: 88 %
[I] Temperature: 32 °C
[I] Humidity: 89 %
[I] Temperature: 32 °C
[I] Humidity: 88 %
```
