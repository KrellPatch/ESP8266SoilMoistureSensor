# ESP8266SoilMoistureSensor
ESP8266 Arduino library for the Robotdyn Soil Moisture Sensor

Creates a (Robotdyn) Soil Moisture sensor that measures soil moisture levels via default analog A0 pin on the ESP8266.
Power to the sensor is provided during read cycles using (default) D2 pin. This may be changed to any digital pin.
Use read() function to read the values. Values are in CB (200-0) where 200 is dry. 
Values can also be expressed as % humidity by settinf measurePercentage to true.
Sensor can be calibrated for lowest and highest values through min- and maxCalibration setters.
Power to the sensor can also be continuous (not recommended, shortens sensor life) by setting continuous to true.
