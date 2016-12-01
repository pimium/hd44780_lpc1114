/*
* =====================================================================================
*       Filename:  sda_5708.h
*
*    Description:  Driver file for the sda 5708 device 
*
*        Version:  1.0 
*        Created:  26 November 2016 11:32
*
*         Author:  Olivier Pimi , pimium@gmail.com 
*   Organization:  Pimium 
*
* =====================================================================================
*/
#ifndef SDA_5708_H
#define SDA_5708_H

#include "hdr/hdr_gpio_masked_access.h"

#define DATA_7_pin 8
#define DATA_6_pin 9
#define DATA_5_pin 10
#define DATA_4_pin 11

#define ENABLE_pin 9
#define R_W_pin 10
#define RS_pin 11

#define DATA_7 (1 << DATA_7_pin)
#define DATA_6 (1 << DATA_6_pin)
#define DATA_5 (1 << DATA_5_pin)
#define DATA_4 (1 << DATA_4_pin)

#define ENABLE  (1 << ENABLE_pin)
#define R_W 	(1 << R_W_pin_)
#define RS 		(1 << RS_pin)

void init_SDA(void);
void write_SDA_char(unsigned int position, unsigned int value);
void write_SDA(uint8_t value);

void set_SDA_clk(void);
void clear_SDA_clk(void);
void set_SDA_cs(void);
void clear_SDA_cs(void);
void set_SDA_reset(void);
void clear_SDA_reset(void);
void set_SDA_data(void);
void clear_SDA_data(void);
#endif /* SDA_5708_H */
