#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <TinyGPS.h>
#include <SoftwareSerial.h>


Adafruit_MPU6050 mpu;
TinyGPS gps;
SoftwareSerial ss(3, 4); 


long lat = 0, lon = 0;

void setup() {
  Serial.begin(9600);
  ss.begin(9600); 

 
  if (!mpu.begin()) {
    Serial.println("Nu am putut găsi un senzor MPU6050. Verificați conexiunile.");
    while (1);
  }
  Serial.println("MPU6050 găsit!");

  
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);  

  Serial.println("Inițializare completă!");
}

void loop() {
  
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  
  while (ss.available() > 0) {
    gps.encode(ss.read());  
  }

  
  gps.get_position(&lat, &lon);

  
  float latitude = lat / 100000.0;000
  float longitude = lon / 100000.0;

  
  Serial.print("Acceleratie X: ");
  Serial.print(a.acceleration.x);
  Serial.print(" m/s^2, Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(" m/s^2, Z: ");
  Serial.print(a.acceleration.z);
  Serial.print(" m/s^2, ");
  
  Serial.print("Giroscop X: ");
  Serial.print(g.gyro.x);
  Serial.print(" rad/s, Y: ");
  Serial.print(g.gyro.y);
  Serial.print(" rad/s, Z: ");
  Serial.print(g.gyro.z);
  Serial.print(" rad/s, ");
  
  Serial.print("Temperatura: ");
  Serial.print(temp.temperature);
  Serial.print(" C, ");
  
  Serial.print("Latitudine: ");
  Serial.print(latitude, 6);  
  Serial.print(", Longitudine: ");
  Serial.println(longitude, 6); 

  delay(500); 
}





