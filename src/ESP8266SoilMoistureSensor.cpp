/*
 * ESP8266SoilMoistureSensor.cpp
 *
 *  Created on: 5 jun. 2020
 *      Author: mark
 */

#include "ESP8266SoilMoistureSensor.h"

ESP8266SoilMoistureSensor::ESP8266SoilMoistureSensor(const uint8_t readPin = PIN_A0, const uint8_t powerPin = D2) :
	_readPin {readPin},
	_powerPin {powerPin},
	_samples {10},
	_powerSave {true},
	_minCalibration {5},
	_maxCalibration {650}, // Default value for 3.3V VCC, may be higher when using 5V
	_centiBar {true}
{
	// ToDo: check if all pin values are suitable, otherwise use switch()
	if(_powerPin) pinMode(_powerPin, OUTPUT);
}

ESP8266SoilMoistureSensor::ESP8266SoilMoistureSensor(const uint8_t readPin = PIN_A0) :
	ESP8266SoilMoistureSensor {readPin, D2}
{}

ESP8266SoilMoistureSensor::ESP8266SoilMoistureSensor() :
	ESP8266SoilMoistureSensor {PIN_A0, D2}
{}

ESP8266SoilMoistureSensor::~ESP8266SoilMoistureSensor() {}

// Get a measurement from the sensor. Values are 0 to 200 CB
// where 0 is WET and 200 is extremely dry
// ToDo: rename to currentValue(), save lastValue for comparison purposes
int ESP8266SoilMoistureSensor::value() {
	int value = 0;

	// ToDo: Rethink the logic of continuous and powerPin

	// If not continuous, set powerPin high
	if(_powerSave && _powerPin) digitalWrite(_powerPin, HIGH);
	delay(10); // Give sensor time to adjust to power

	// measurements
	for(int i = 0; i < _samples; ++i) {
		value += analogRead(_readPin);
		// Need delay here? Lets try
		delay(10);
	}
	// Set powerpin off if required
	if(_powerSave && _powerPin) digitalWrite(_powerPin, LOW);

	// Calculate average reading
	value /= _samples;

	if(_centiBar) {
		// return CB value (inverted, 200 = dry, 0 = wet)
		value = map(value, _maxCalibration, _minCalibration, 0, 200);
	} else {
		// Return %H
		value = map(value, _minCalibration, _maxCalibration, 0, 100);
	}

	return value;
} // value()

// Setters and Getters. Use overload functions.

// Sets the number of samples taken to get a good reading. Default 10.
void 		ESP8266SoilMoistureSensor::samples(int samples) 									{ _samples = samples; }
int			ESP8266SoilMoistureSensor::samples() 															{ return _samples; }

// Read pin and power (VCC) pin numbers. Read pin should be Analog Read capable. Default A0 on ESP8266.
// Power pin switches power to the sensors VCC input and is switched off after reading to save
// sensor lifetime. Default D2. On=Off switching is controlled through the powerSave() function. Set to false
// power is always on. Default true.
void 		ESP8266SoilMoistureSensor::readPin(uint8_t readPin) 							{	_readPin = readPin; }
uint8_t ESP8266SoilMoistureSensor::readPin() 															{ return _readPin; }
void 		ESP8266SoilMoistureSensor::powerPin(uint8_t powerPin) 						{ _powerPin = powerPin; }
uint8_t	ESP8266SoilMoistureSensor::powerPin() 														{ return _powerPin; }
void 		ESP8266SoilMoistureSensor::powerSave(bool powerSave) 							{ _powerSave = powerSave; }
bool 		ESP8266SoilMoistureSensor::powerSave() 														{ return _powerSave; }

// Calibration values: set the minimum and maximum value returned by your sensor
// This makes sure the lowest and highest values are consistently mapped to centiBar values
// Defaults 5 and 650
void 		ESP8266SoilMoistureSensor::minCalibration(int minCalibration) 		{	_minCalibration = minCalibration; }
int			ESP8266SoilMoistureSensor::minCalibration() 											{	return _minCalibration; }
void 		ESP8266SoilMoistureSensor::maxCalibration(int maxCalibration) 		{	_maxCalibration = maxCalibration; }
int			ESP8266SoilMoistureSensor::maxCalibration() 											{	return _maxCalibration; }

// Measurement unit; If set to true (default), value() returns values in CentiBar from 200-0.
// If set to false, value() returns % Humidity value from 0-100
void		ESP8266SoilMoistureSensor::centiBar(bool centiBar) {_centiBar = centiBar; }
bool		ESP8266SoilMoistureSensor::centiBar() { return _centiBar; }

