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

#ifdef __DEBUG
  #define DPRINT(...)    Serial.print(__VA_ARGS__)     //DPRINT is a macro, debug print
  #define DPRINTLN(...)  Serial.println(__VA_ARGS__)   //DPRINTLN is a macro, debug print with new line
#else
  #define DPRINT(...)     //now defines a blank line
  #define DPRINTLN(...)   //now defines a blank line
#endif

class ESP8266SoilMoistureSensor {
public:
	ESP8266SoilMoistureSensor();
	ESP8266SoilMoistureSensor(uint8_t);
	ESP8266SoilMoistureSensor(uint8_t, uint8_t);
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
