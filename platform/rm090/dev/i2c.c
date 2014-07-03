/*
 * i2c.c
 *
 *  Created on: Jul 1, 2014
 *      Author: pdvalck
 */

#include "i2c.h"

#include <msp430.h>
#include <stdint.h>

// Initialize the USCI module B1 in I2C mode

void i2c_init(void){

	// Reset
	UCB1CTL1 |= UCSWRST;

	// External I2C enable
	P3DIR |= BIT6;
	P3OUT |= BIT6;

	// Does not work without
	__delay_cycles(16000);

	// I2C function select
	// SDA
	P3SEL |= BIT7;
	P3DIR |= BIT7;
	// SCL
	P5SEL |= BIT4;
	P5DIR |= BIT4;

	// Master, I2C, synchronous
	UCB1CTL0 = UCMST + UCMODE_3 + UCSYNC;

	// Clock selection (100k)
	UCB1CTL1 = UCSSEL__SMCLK + UCSWRST;

	// Clock prescaler (SMCLK = 8 MHz / 80 = 100 KHz)
	UCB1BR0 = 80;
	UCB1BR1 = 0;

	// Disable reset
	UCB1CTL1 &= ~UCSWRST;

}

void i2c_read(uint8_t addr, uint8_t * buf, uint8_t len){

	uint8_t index;

	// Receive mode
	UCB1CTL1 &= ~UCTR;

	// Write slave address
	UCB1I2CSA = addr;

	// Generate a start condition
	UCB1CTL1 |= UCTXSTT;

	for (index = 0; index < len - 1; ++index) {

		// Wait for a received byte
		while(!(UCB1IFG & UCRXIFG));

		// Read received byte
		buf[index] = UCB1RXBUF;

	}

	// Make sure we wait until the address has been transmitted
	while(UCB1CTL1 & UCTXSTT);

	// Send stop condition during reception of last byte
	UCB1CTL1 |= UCTXSTP;

	// Wait and read last byte
	while(!(UCB1IFG & UCRXIFG));
	buf[len - 1] = UCB1RXBUF;

	// Wait for stop condition
	while(UCB1CTL1 & UCTXSTP);

}

void i2c_write(uint8_t addr, uint8_t * buf, uint8_t len){

	uint8_t index;

	// Send mode
	UCB1CTL1 |= UCTR;

	// Write slave address
	UCB1I2CSA = addr;

	// Generate a start condition
	UCB1CTL1 |= UCTXSTT;

	// Write first byte
	UCB1TXBUF = buf[0];

	for (index = 1; index < len; ++index) {

		// Wait until we can transmit another byte
		while(!(UCB1IFG & UCTXIFG));
		UCB1TXBUF = buf[index];

	}

	// Wait until the last byte has started TX before setting stop condtion
	while(!(UCB1IFG & UCTXIFG));
	UCB1CTL1 |= UCTXSTP;

	// Wait for stop condition
	while(UCB1CTL1 & UCTXSTP);

}

