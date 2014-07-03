#include <stdlib.h>

#include "contiki.h"
#include "lib/sensors.h"
#include "dev/sht21.h"
#include "dev/sht21-sensor.h"

const struct sensors_sensor sht21_sensor;

enum {
  ON, OFF
};
static uint8_t state = OFF;

static int value(int type){

	int res = 0;

	if(type == SHT21_SENSOR_TEMP)
		res = sht21_temp();

	if(type == SHT21_SENSOR_HUM)
		res = sht21_hum();

	return res;

}

static int status(int type){

	if(type == SENSORS_ACTIVE)
		return state == ON;

	if(type == SENSORS_READY)
		return state == ON;

	return 0;

}

static int configure(int type, int c){

	if(type == SENSORS_ACTIVE && c && state != ON){
		state = ON;
		sht21_on();
	}else{
		state = OFF;
		sht21_off();
	}

	return 0;

}

SENSORS_SENSOR(sht21_sensor, "sht21", value, configure, status);

