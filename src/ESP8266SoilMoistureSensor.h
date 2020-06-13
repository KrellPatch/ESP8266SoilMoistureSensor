/*
 * ESP8266SoilMoistureSensor.h
 *
 *  Created on: 5 jun. 2020
 *      Author: mark
 */

#ifndef ESP8266SOILMOISTURESENSOR_H_
#define ESP8266SOILMOISTURESENSOR_H_

#include "Arduino.h"

#define VERSION_ 1.0

#define __DEBUG

#ifdef __DEBUG
  #define DPRINT(...)    Serial.print(__VA_ARGS__)     //DPRINT is a macro, debug print
  #define DPRINTLN(...)  Serial.println(__VA_ARGS__)   //DPRINTLN is a macro, debug print with new line
#else
  #define DPRINT(...)     //now defines a blank line
  #define DPRINTLN(...)   //now defines a blank line
#endif

// Creates a (Robotdyn) Soil Moisture sensor
// that measures soil moisture levels via default analog A0 pin
// Power to the sensor is provided during read cycles using (default) D2 pin
// Use read() function to read the values. Values are in CB (200-0) where 200 is dry.
// Vaslues can also be expressed as % humidity by settinf measurePercentage to true.
// Sensor can be calibrated for lowest and highest values through min- and
// maxCalibration setters.
// Power to the sensor can also be continuous (not recommended, shotens sensor life)
// by setting continuous to true.
class ESP8266SoilMoistureSensor {
public:
	ESP8266SoilMoistureSensor();
	ESP8266SoilMoistureSensor(const uint8_t);
	ESP8266SoilMoistureSensor(const uint8_t, const uint8_t);
	virtual ~ESP8266SoilMoistureSensor();

	int 		read();
	void 		setSamples(int);
	int			samples();
	void 		setContinuous(bool);
	bool 		continuous();
	void		setReadPin(uint8_t);
	uint8_t	readPin();
	void		setPowerPin(uint8_t);
	uint8_t	powerPin();
	void		setMinCalibration(int);
	int			minCalibration();
	void		setMaxCalibration(int);
	int			maxCalibration();
	void		setMeasurePercentage(bool);
	bool		measurePercentage();

private:
	uint8_t	_readPin;
	uint8_t	_powerPin;
	int			_samples;
	bool		_continuous;
	int			_minCalibration;
	int			_maxCalibration;
	bool		_measurePercentage;
};

#endif /* ESP8266SOILMOISTURESENSOR_H_ */
