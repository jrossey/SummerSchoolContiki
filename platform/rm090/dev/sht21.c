/*
 * sht21.c
 *
 *  Created on: Jul 1, 2014
 *      Author: pdvalck
 */

#include <dev/i2c.h>
#include <dev/sht21.h>

#include "contiki.h"
#include <stdint.h>

static void delay_ms(uint8_t count){

	while(count-- > 0)
		__delay_cycles(16000);

}

void sht21_on(void){

	// Init I2C
	i2c_init();

	// Power up SHT21
	P4DIR |= BIT5;
	P4OUT |= BIT5;

	// Wait a bit
	delay_ms(20);

}

void sht21_off(void){

	// Power down SHT21
	P4DIR |= BIT5;
	P4OUT &= ~BIT5;

}

uint16_t sht21_hum(void){

	uint8_t cmd = SHT21_CMD_HUM_HOLD;
	uint8_t buf[2];

	double hum;

	i2c_write(SHT21_ADDR, &cmd, 1);
	i2c_read(SHT21_ADDR, buf, 2);

	hum = 256 * buf[0] + buf[1];
	hum /= 65536.0;
	hum *= 125;
	hum -= 6;
	hum *= 100;

	return (uint16_t)hum;

}

float sht21_temp(void){

	uint8_t cmd = SHT21_CMD_TEMP_HOLD;
	uint8_t buf[2];

	double temp;

	i2c_write(SHT21_ADDR, &cmd, 1);
	i2c_read(SHT21_ADDR, buf, 2);

	temp = 256 * buf[0] + buf[1];
	temp /= 65536.0;
	temp *= 175.72;
	temp -= 46.85;
	temp *= 100;

	return (uint16_t)temp;

}

