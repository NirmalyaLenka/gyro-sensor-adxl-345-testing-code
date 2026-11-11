# ESP32 + ADXL345 Accelerometer

A compact Arduino example for reading three-axis acceleration from an ADXL345 accelerometer over I2C. The sketch prints X/Y/Z acceleration, vector magnitude, a simple dominant-axis tilt estimate, and a basic low-magnitude warning to the Serial Monitor.

**Terminology:** ADXL345 is an accelerometer, not a gyroscope. It measures linear acceleration and gravity; it does not directly measure angular velocity.

## Features

- Read X, Y, and Z acceleration in m/s²
- Calculate acceleration-vector magnitude
- Estimate a coarse tilt direction from the dominant axis
- Demonstrate a low-magnitude threshold warning
- Configure measurement range and sensor output data rate

The current sketch polls every 500 ms and checks whether the measured magnitude is below 2 m/s². This is a **learning demonstration only**, not reliable free-fall detection or a safety feature. Short events can be missed; real event detection should use the ADXL345's hardware interrupt features and an appropriately validated sampling strategy. The current sketch does not implement tap-event detection.

## Hardware

- ESP32 development board
- ADXL345 breakout/module
- Jumper wires
- Breadboard (optional)

## Wiring — I2C

| ADXL345 module | ESP32 |
| --- | --- |
| VCC | 3.3 V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |
| CS | 3.3 V to select I2C mode |
| SDO | GND for I2C address 0x53 |

The ADXL345 sensor is a low-voltage device. Check the breakout's datasheet before powering it; do not assume every module accepts 5 V. With the ESP32, use 3.3 V logic.

## Bill of materials

| Item | Qty. | Notes |
| --- | ---: | --- |
| ESP32 development board | 1 | ESP32 Dev Module profile used in the guide |
| ADXL345 breakout | 1 | Confirm module pin labels and voltage limits |
| Jumper wires | 6 | VCC, GND, SDA, SCL, CS, SDO |
| Breadboard | 1, optional | For prototyping |
| USB data cable | 1 | Upload and serial monitoring |

This is the current single-sensor prototype BOM. It does not include an enclosure, battery, display, or mechanical mounting hardware.

## Software setup

1. Install the [Arduino IDE](https://www.arduino.cc/en/software).
2. Install ESP32 board support using Espressif's board manager package:
   `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
3. In Library Manager, install **Adafruit ADXL345** and **Adafruit Unified Sensor**.
4. Open `adxl345_esp32.ino`.
5. Select the appropriate ESP32 board and serial port, then compile and upload.
6. Open Serial Monitor at **115200 baud**.

## Configuration

The sketch currently uses:

```cpp
accel.setRange(ADXL345_RANGE_2_G);
accel.setDataRate(ADXL345_DATARATE_100_HZ);
```

Available ranges in the library include ±2 g, ±4 g, ±8 g, and ±16 g. The sensor data rate is configured to 100 Hz, but the sketch only reads and prints data every 500 ms; these are different rates. The loop's polling interval limits how quickly software can react to brief events.

## Repository structure

```text
gyro-sensor-adxl-345-testing-code/
├── adxl345_esp32.ino   # ESP32 firmware sketch
└── README.md           # Wiring, setup, BOM, limitations, and maintenance
```

## Troubleshooting

| Problem | Checks |
| --- | --- |
| Sensor not found | Verify VCC/GND, SDA GPIO 21, SCL GPIO 22, CS high, and SDO low |
| Serial output is unreadable | Set the monitor to 115200 baud |
| Values are unexpectedly zero | Check wiring, sensor orientation, and library installation |
| Tilt label looks wrong | The current method is a coarse dominant-axis estimate, not a calibrated attitude solution |
| Brief motion event is missed | The 500 ms polling/printing loop is too slow for reliable transient detection |

## Libraries

- [Adafruit ADXL345](https://github.com/adafruit/Adafruit_ADXL345) — accelerometer driver
- [Adafruit Unified Sensor](https://github.com/adafruit/Adafruit_Sensor) — common sensor interface
- `Wire` — I2C support supplied by the ESP32 Arduino core

## Potential extensions

- Use ADXL345 interrupt pins for data-ready and validated free-fall detection
- Add a rolling data logger or serial plotter output
- Calibrate axis offsets and document sensor orientation
- Add a proper mounting bracket before using it for motion measurements

## Skills and technologies

`Embedded C++` · `ESP32` · `I2C` · `Accelerometers` · `Sensor interfacing`

## Maintenance & audit

- **Last updated:** 11 November 2026
- **Review scope:** Checked the tracked sketch against the README's feature claims, wiring, BOM, and setup notes.
- **Documentation changes:** Clarified that ADXL345 is an accelerometer, documented the actual 500 ms polling loop, removed the unsupported tap-detection claim, and qualified the free-fall threshold as a demo only.
- **Validation boundary:** No firmware change was made and no compilation or hardware test was run. No `LICENSE` file was found in the current root listing, so no license is claimed here.
