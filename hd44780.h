/*
* =====================================================================================
*       Filename:  hd44780.h
*
*    Description:  Driver file for the HD44780 display device 
*
*        Version:  1.0 
*        Created:  26 November 2016 11:32
*
*         Author:  Olivier Pimi , pimium@gmail.com 
*   Organization:  Pimium 
*
* =====================================================================================
*/
#ifndef HD44780_H
#define HD44780_H

#include "hdr/hdr_gpio_masked_access.h"

#define HD44780_GPIO	LPC_GPIO0

#define DATA_7_pin 8
#define DATA_6_pin 9
#define DATA_5_pin 10
#define DATA_4_pin 11

#define ENABLE_pin 3
#define R_W_pin 2
#define RS_pin 1

#define DATA_7 (1 << DATA_7_pin)
#define DATA_6 (1 << DATA_6_pin)
#define DATA_5 (1 << DATA_5_pin)
#define DATA_4 (1 << DATA_4_pin)

#define ENABLE  (1 << ENABLE_pin)
#define R_W 	(1 << R_W_pin)
#define RS 		(1 << RS_pin)

void init_HD44780(void);
void write_HD44780_data(unsigned int value);
void write_HD44780_address(unsigned int value);
void write_HD44780_string(unsigned int position, char *str);
void write_data(unsigned int value);
void set_HD44780_RS(void);
void clear_HD44780_RS(void);
void set_HD44780_R_W(void);
void clear_HD44780_R_W(void);
void set_HD44780_ENABLE(void);
void clear_HD44780_ENABLE(void);
void enable(void);
#endif /* HD44780_H */
