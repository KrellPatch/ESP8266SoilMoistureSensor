/*
 * ESP8266SoilMoistureSensor.cpp
 *
 *  Created on: 5 jun. 2020
 *      Author: mark
 */

#include "ESP8266SoilMoistureSensor.h"

ESP8266SoilMoistureSensor::ESP8266SoilMoistureSensor() {
 // ToDo, check best value for 'unset'
	this(0, 0);
}

ESP8266SoilMoistureSensor::ESP8266SoilMoistureSensor(uint8_t readPin) {
	this(readPin, 0);
}

ESP8266SoilMoistureSensor::ESP8266SoilMoistureSensor(uint8_t readPin, uint8_t powerPin) {
	_readPin = readPin;
	_powerPin = powerPin;
	_minCalibration = 0;
	_maxCalibration = 1000;
	_samples = 10;
	_continuous = false;

}

ESP8266SoilMoistureSensor::~ESP8266SoilMoistureSensor() {

}

int 		ESP8266SoilMoistureSensor::read() {
	int value;

	// If not continuous, set powerPin high
	if(!_continuous) digitalWrite(_powerPin, HIGH);
	// measurements
	for(int i = 0; i < _samples; ++i) {
		value += analogRead(_readPin);
	}
	// reset powerpin if required
	if(!_continuous) digitalWrite(_powerPin, LOW);

	// Take average reading and remap to CB value (wet-dry, 0-200)
	value /= _samples;
	value = map(value, _maxCalibration, _minCalibration, 0, 200);

	return value;
} // read()

void 		ESP8266SoilMoistureSensor::setSamples(int samples) {
	_samples = samples;
} // setSamples()

int			ESP8266SoilMoistureSensor::samples() {
	return _samples;
} // samples()

void 		ESP8266SoilMoistureSensor::setContinuous(bool continuous) {
	_continuous = continuous;
} // setContinuous()

bool 		ESP8266SoilMoistureSensor::continuous() {
	return _continuous;
} // continuous()

void		ESP8266SoilMoistureSensor::setReadPin(uint8_t readPin) {
	_readPin = readPin;
} // setReadPin()

uint8_t	ESP8266SoilMoistureSensor::readPin() {
	return _readPin;
} // readPin()

void		ESP8266SoilMoistureSensor::setPowerPin(uint8_t powerPin) {
	_powerPin = powerPin;
} // setPowerPin()

uint8_t	ESP8266SoilMoistureSensor::powerPin() {
	return _powerPin;
} // powerPin()

void		ESP8266SoilMoistureSensor::setMinCalibration(int minCalibration) {
	_minCalibration = minCalibration;
} // setMinCalibration()

int			ESP8266SoilMoistureSensor::minCalibration() {
	return _minCalibration;
} // minCalibration()

void		ESP8266SoilMoistureSensor::setMaxCalibration(int maxCalibration) {
	_maxCalibration = maxCalibration;
} // setMaxCalibration()

int			ESP8266SoilMoistureSensor::maxCalibration() {
	return _maxCalibration;
}

