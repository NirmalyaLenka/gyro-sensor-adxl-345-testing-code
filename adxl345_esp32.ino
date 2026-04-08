/*
 * ADXL345 Accelerometer Sensor with ESP32
 * Reads X, Y, Z Acceleration values
 * Detects Tilt, Free Fall, and Tap events
 *
 * Wiring (I2C):
 *   ADXL345 VCC  -> ESP32 3.3V
 *   ADXL345 GND  -> ESP32 GND
 *   ADXL345 SDA  -> ESP32 GPIO 21
 *   ADXL345 SCL  -> ESP32 GPIO 22
 *   ADXL345 CS   -> ESP32 3.3V (keeps it in I2C mode)
 *   ADXL345 SDO  -> ESP32 GND  (sets I2C address to 0x53)
 *
 * Required Library: Adafruit ADXL345 Library
 */

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

// Create ADXL345 object with unique ID
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void printSensorDetails() {
  sensor_t sensor;
  accel.getSensor(&sensor);
  Serial.println("=================================");
  Serial.println("  ESP32 + ADXL345 Sensor Demo   ");
  Serial.println("=================================");
  Serial.print("Sensor Name : "); Serial.println(sensor.name);
  Serial.print("Max Range   : "); Serial.print(sensor.max_value); Serial.println(" m/s^2");
  Serial.print("Resolution  : "); Serial.print(sensor.resolution); Serial.println(" m/s^2");
  Serial.println("---------------------------------");
}

String getTiltDirection(float x, float y, float z) {
  String direction = "Flat";
  if (abs(x) > abs(y) && abs(x) > abs(z)) {
    direction = (x > 0) ? "Tilted RIGHT" : "Tilted LEFT";
  } else if (abs(y) > abs(x) && abs(y) > abs(z)) {
    direction = (y > 0) ? "Tilted FORWARD" : "Tilted BACKWARD";
  } else if (z < -7.0) {
    direction = "UPSIDE DOWN";
  } else {
    direction = "Flat / Level";
  }
  return direction;
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Initialize I2C with ESP32 default pins
  Wire.begin(21, 22);

  // Initialize ADXL345
  if (!accel.begin()) {
    Serial.println("ERROR: ADXL345 sensor not found!");
    Serial.println("Check wiring:");
    Serial.println("  VCC -> 3.3V");
    Serial.println("  GND -> GND");
    Serial.println("  SDA -> GPIO 21");
    Serial.println("  SCL -> GPIO 22");
    Serial.println("  CS  -> 3.3V");
    Serial.println("  SDO -> GND");
    while (1) { delay(1000); }
  }

  printSensorDetails();

  // Set measurement range
  // Options: ADXL345_RANGE_2_G, ADXL345_RANGE_4_G, ADXL345_RANGE_8_G, ADXL345_RANGE_16_G
  accel.setRange(ADXL345_RANGE_2_G);

  // Set data rate
  // Options: ADXL345_DATARATE_100_HZ (default), _200_HZ, _50_HZ, etc.
  accel.setDataRate(ADXL345_DATARATE_100_HZ);

  Serial.println("ADXL345 initialized successfully!");
  Serial.println();
}

void loop() {
  // Get new sensor event
  sensors_event_t event;
  accel.getEvent(&event);

  float x = event.acceleration.x;
  float y = event.acceleration.y;
  float z = event.acceleration.z;

  // Calculate total acceleration magnitude
  float magnitude = sqrt(x * x + y * y + z * z);

  // Get tilt direction
  String tilt = getTiltDirection(x, y, z);

  // Detect free fall (all axes near 0)
  bool freeFall = (magnitude < 2.0);

  // Print readings
  Serial.println("--- Accelerometer Readings ---");
  Serial.print("X Axis    : ");
  Serial.print(x, 4);
  Serial.println(" m/s^2");

  Serial.print("Y Axis    : ");
  Serial.print(y, 4);
  Serial.println(" m/s^2");

  Serial.print("Z Axis    : ");
  Serial.print(z, 4);
  Serial.println(" m/s^2");

  Serial.print("Magnitude : ");
  Serial.print(magnitude, 4);
  Serial.println(" m/s^2");

  Serial.print("Tilt      : ");
  Serial.println(tilt);

  if (freeFall) {
    Serial.println("⚠️  FREE FALL DETECTED!");
  }

  Serial.println("------------------------------");
  Serial.println();

  delay(500); // Read every 500ms
}
