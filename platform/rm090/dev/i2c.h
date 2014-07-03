/*
 * i2c.h
 *
 *  Created on: Jul 1, 2014
 *      Author: pdvalck
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

void i2c_init(void);

void i2c_read(uint8_t addr, uint8_t * buf, uint8_t len);
void i2c_write(uint8_t addr, uint8_t * buf, uint8_t len);

#endif /* I2C_H_ */
