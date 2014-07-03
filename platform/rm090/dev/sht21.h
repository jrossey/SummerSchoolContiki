/*
 * sht21.h
 *
 *  Created on: Jul 1, 2014
 *      Author: pdvalck
 */

#ifndef SHT21_H_
#define SHT21_H_

#include <stdint.h>

#define SHT21_CMD_TEMP_HOLD   0b11100011
#define	SHT21_CMD_HUM_HOLD    0b11100101
#define	SHT21_CMD_TEMP_NOHOLD 0b11110011
#define	SHT21_CMD_HUM_NOHOLD  0b11110101
#define	SHT21_CMD_WRITE_REG   0b11100110
#define	SHT21_CMD_READ_REG    0b11100111
#define SHT21_CMD_RESET       0b11111110

#define SHT21_ADDR            0b1000000

void sht21_on(void);
void sht21_off(void);

uint16_t sht21_hum(void);
float sht21_temp(void);

#endif /* SHT21_H_ */

