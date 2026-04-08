# gyro-sensor-adxl-345-testing-code
# ESP32 + ADXL345 Accelerometer 

Read **X, Y, Z acceleration**, detect **tilt direction**, and monitor **free fall** using an ADXL345 accelerometer with an ESP32 microcontroller.

---

##  Components Required

| Component | Quantity |
|-----------|----------|
| ESP32 Dev Board | 1 |
| ADXL345 Sensor Module | 1 |
| Jumper Wires | 6 |
| Breadboard (optional) | 1 |

---

##  Wiring Diagram (I2C Mode)

```
ADXL345         ESP32
-------         -----
VCC    ──────►  3.3V
GND    ──────►  GND
SDA    ──────►  GPIO 21
SCL    ──────►  GPIO 22
CS     ──────►  3.3V   (enables I2C mode)
SDO    ──────►  GND    (sets I2C address to 0x53)
```

>  **Important:** Use **3.3V** only! The ADXL345 is NOT 5V tolerant.  
>  Connect **CS to 3.3V** to enable I2C mode (floating CS defaults to SPI).  
> **SDO to GND** sets I2C address `0x53`. SDO to 3.3V sets address `0x1D`.

---

##  Setup & Installation

### 1. Install Arduino IDE
Download from [arduino.cc](https://www.arduino.cc/en/software)

### 2. Add ESP32 Board Support
1. Open **Arduino IDE** → **File** → **Preferences**
2. Add this URL to *Additional Boards Manager URLs*:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
3. Go to **Tools** → **Board** → **Boards Manager**
4. Search for `esp32` and click **Install**

### 3. Install Required Libraries
1. Go to **Sketch** → **Include Library** → **Manage Libraries**
2. Search and install the following:
   - **Adafruit ADXL345** by Adafruit
   - **Adafruit Unified Sensor** by Adafruit

### 4. Upload the Sketch
1. Open `adxl345_esp32.ino` in Arduino IDE
2. Select your board: **Tools** → **Board** → **ESP32 Dev Module**
3. Select the correct **Port** under **Tools** → **Port**
4. Click **Upload** 

---

##  Serial Monitor Output

Open Serial Monitor at **115200 baud** to see live readings:

```
=================================
  ESP32 + ADXL345 Sensor Demo   
=================================
Sensor Name : ADXL345
Max Range   : 156.96 m/s^2
Resolution  : 0.04 m/s^2
---------------------------------
ADXL345 initialized successfully!

--- Accelerometer Readings ---
X Axis    : 0.1570 m/s^2
Y Axis    : -0.3530 m/s^2
Z Axis    : 9.7340 m/s^2
Magnitude : 9.7467 m/s^2
Tilt      : Flat / Level
------------------------------
```

---

##  Configuration

### Measurement Range
Change sensitivity range in the code:
```cpp
accel.setRange(ADXL345_RANGE_2_G);   // ±2g  — most sensitive (default)
accel.setRange(ADXL345_RANGE_4_G);   // ±4g
accel.setRange(ADXL345_RANGE_8_G);   // ±8g
accel.setRange(ADXL345_RANGE_16_G);  // ±16g — least sensitive
```

### Data Rate
Change how frequently the sensor samples:
```cpp
accel.setDataRate(ADXL345_DATARATE_100_HZ);  // 100 samples/sec (default)
accel.setDataRate(ADXL345_DATARATE_200_HZ);  // 200 samples/sec
accel.setDataRate(ADXL345_DATARATE_50_HZ);   // 50 samples/sec
```

---

##  Features

| Feature | Description |
|---------|-------------|
| X / Y / Z Axes | Raw acceleration in m/s² |
| Magnitude | Total vector magnitude of acceleration |
| Tilt Detection | Detects Left, Right, Forward, Backward, Upside Down, Flat |
| Free Fall Detection | Triggers when total magnitude drops below 2 m/s² |

---

##  Troubleshooting

| Problem | Solution |
|--------|----------|
| `ADXL345 sensor not found!` | Check CS → 3.3V and SDO → GND; verify SDA/SCL pins |
| Garbage in Serial Monitor | Set baud rate to **115200** |
| All values read 0.0 | CS pin might be floating — connect firmly to 3.3V |
| Board not detected | Install CP210x or CH340 USB driver for your ESP32 board |
| Sensor found but bad data | Try pulling SDA/SCL lines up with 4.7kΩ resistors to 3.3V |

---

##  Project Structure

```
esp32-adxl345/
│
├── adxl345_esp32.ino   # Main Arduino sketch
└── README.md           # This file
```

---

##  Libraries Used

- [Adafruit ADXL345](https://github.com/adafruit/Adafruit_ADXL345) — ADXL345 accelerometer driver
- [Adafruit Unified Sensor](https://github.com/adafruit/Adafruit_Sensor) — unified sensor abstraction layer
- [Wire](https://www.arduino.cc/reference/en/language/functions/communication/wire/) — built-in I2C library

---

##  Project Ideas

-  Gesture-controlled robot or car
-  Motion-based game controller
-  Shock/vibration logger for fragile packages
-  Workout rep counter
-  Tilt-based servo motor control

---

##  License

This project is open source and available under the [MIT License](LICENSE).

---

##Contributing

Pull requests are welcome! Feel free to open an issue for bugs or feature requests.

---

