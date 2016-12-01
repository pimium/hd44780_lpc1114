/*
* =====================================================================================
*       Filename:  sda_5708.c
*
*    Description:  Driver to controll the sda 5708 
*
*        Version:  1.0 
*        Created:  26 November 2016 11:43
*
*         Author:  Olivier Pimi , pimium@gmail.com 
*   Organization:  Pimium 
*
* =====================================================================================
*/
#include "inc/LPC11xx.h"
#include "sda_5708.h"
#include "font5x7.h"

void init_SDA(void){
	volatile uint32_t count, count_max = 1000000;
	
	LPC_GPIO0->DIR |= CS;
	LPC_GPIO0->DIR |= DAT;
	LPC_GPIO1->DIR |= CLK;
	LPC_GPIO1->DIR |= RESET;

	clear_SDA_reset();
	for (count = 0; count < count_max; count++);	// delay
	set_SDA_reset();
	set_SDA_cs();
	clear_SDA_clk();
}

void write_SDA(uint8_t value){

	volatile uint32_t count, count_max = 1000;
	clear_SDA_clk();
	clear_SDA_cs();
	for (count = 0; count < count_max; count++);	// delay
	                                            	// 
	for (int i = 0; i < 8; ++i)
	{
		if (value & 0x01)
		{
			set_SDA_data();
		} else
			clear_SDA_data();

		for (count = 0; count < count_max; count++);	// delay
		set_SDA_clk();
		for (count = 0; count < count_max; count++);
		value = value >> 1;
		clear_SDA_clk();
	}
	set_SDA_cs();
}

void write_SDA_char(unsigned int position, unsigned int value){
	unsigned int data;
	unsigned int column0 = *(Font5x7 + 5*(value + 16) + 0);
	unsigned int column1 = *(Font5x7 + 5*(value + 16) + 1);
	unsigned int column2 = *(Font5x7 + 5*(value + 16) + 2);
	unsigned int column3 = *(Font5x7 + 5*(value + 16) + 3);
	unsigned int column4 = *(Font5x7 + 5*(value + 16) + 4);

	if (position < 8){
		data = 0xA0 + position;
		write_SDA(data);
	} else
		return;

	for (int i = 0; i < 7; ++i)
	{
		data = ((column0 & 0x1) << 4) + ((column1 & 0x1) << 3) + ((column2 & 0x1) << 2) + ((column3 & 0x1) << 1) + ((column4 & 0x1) << 0);
		write_SDA(data);
		column0 = column0 >> 1;
		column1 = column1 >> 1;
		column2 = column2 >> 1;
		column3 = column3 >> 1;
		column4 = column4 >> 1;
	}
	return;
}

void set_SDA_clk(void){
	LPC_GPIO1->DATA |= CLK;
}
void clear_SDA_clk(void){
	LPC_GPIO1->DATA &= ~CLK;
}

void set_SDA_reset(void){
	LPC_GPIO1->DATA |= RESET;
}
void clear_SDA_reset(void){
	LPC_GPIO1->DATA &= ~RESET;
}

void set_SDA_cs(void){
	LPC_GPIO0->DATA |= CS;
}
void clear_SDA_cs(void){
	LPC_GPIO0->DATA &= ~CS;
}

void set_SDA_data(void){
	LPC_GPIO0->DATA |= DAT;
}
void clear_SDA_data(void){
	LPC_GPIO0->DATA &= ~DAT;
}