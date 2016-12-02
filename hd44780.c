/*
* =====================================================================================
*       Filename:  hd44780.c
*
*    Description:  Driver to controll the HD44780 LCD display
*
*        Version:  1.0
*        Created:  26 November 2016 11:43
*
*         Author:  Olivier Pimi , pimium@gmail.com
*   Organization:  Pimium
*
* =====================================================================================
*/
#include "hd44780.h"
#include "inc/LPC11xx.h"

void init_HD44780(void) {
  volatile uint32_t count, count_max = 1000000;

  LPC_IOCON->SWCLK_PIO0_10 &= ~(0x7);
	LPC_IOCON->SWCLK_PIO0_10 |= 0x11;  
	LPC_IOCON->R_PIO0_11 &= ~(0x7);
	LPC_IOCON->R_PIO0_11 |= 0x11;

  HD44780_GPIO->DIR |= (RS | R_W | ENABLE);
  HD44780_GPIO->DIR |= (DATA_4 | DATA_5 | DATA_6 | DATA_7);

  clear_HD44780_RS();
  clear_HD44780_R_W();
  clear_HD44780_ENABLE();
  for (count = 0; count < count_max; count++)
    ;

  write_data(0x3);
  enable();
  for (count = 0; count < count_max; count++)
    ;

  write_data(0x3);
  enable();
  for (count = 0; count < count_max; count++)
    ;

  write_data(0x3);
  enable();
  for (count = 0; count < count_max; count++)
    ;

  write_data(0x2);
  enable();
  for (count = 0; count < count_max; count++)
    ;

	write_data(0x2);
  enable();
  write_data(0x8);
  enable();
  
  write_data(0x0);
  enable();
  write_data(0x8);
  enable();

  write_data(0x0);
  enable();
  write_data(0x6);
  enable();

  write_data(0x0);
  enable();
  write_data(0xD);
  enable();

  write_data(0x8);
  enable();
  write_data(0x6);
  enable();

  write_HD44780_data(0x55);
}

void write_HD44780_data(uint8_t value) {

  // volatile uint32_t count, count_max = 1000;
  clear_HD44780_ENABLE();
  clear_HD44780_RS();
  clear_HD44780_R_W();
  set_HD44780_RS();
  write_data(value >> 4);
  enable();
  write_data(value);
  enable();
  clear_HD44780_RS();
}

void write_data(unsigned int value) {

  if (value & 0x01) {
    HD44780_GPIO->DATA |= DATA_4;
  } else
    HD44780_GPIO->DATA &= ~DATA_4;
  value = value >> 1;

  if (value & 0x01) {
    HD44780_GPIO->DATA |= DATA_5;
  } else
    HD44780_GPIO->DATA &= ~DATA_5;
  value = value >> 1;

  if (value & 0x01) {
    HD44780_GPIO->DATA |= DATA_6;
  } else
    HD44780_GPIO->DATA &= ~DATA_6;
  value = value >> 1;

  if (value & 0x01) {
    HD44780_GPIO->DATA |= DATA_7;
  } else
    HD44780_GPIO->DATA &= ~DATA_7;
  value = value >> 1;
}

// void write_SDA_char(unsigned int position, unsigned int value){
// 	unsigned int data;
// 	unsigned int column0 = *(Font5x7 + 5*(value + 16) + 0);
// 	unsigned int column1 = *(Font5x7 + 5*(value + 16) + 1);
// 	unsigned int column2 = *(Font5x7 + 5*(value + 16) + 2);
// 	unsigned int column3 = *(Font5x7 + 5*(value + 16) + 3);
// 	unsigned int column4 = *(Font5x7 + 5*(value + 16) + 4);

// 	if (position < 8){
// 		data = 0xA0 + position;
// 		write_SDA(data);
// 	} else
// 		return;

// 	for (int i = 0; i < 7; ++i)
// 	{
// 		data = ((column0 & 0x1) << 4) + ((column1 & 0x1) << 3) +
// ((column2
// & 0x1) << 2) + ((column3 & 0x1) << 1) + ((column4 & 0x1) << 0);
// 		write_SDA(data);
// 		column0 = column0 >> 1;
// 		column1 = column1 >> 1;
// 		column2 = column2 >> 1;
// 		column3 = column3 >> 1;
// 		column4 = column4 >> 1;
// 	}
// 	return;
// }

void set_HD44780_RS(void) { HD44780_GPIO->DATA |= RS; }
void clear_HD44780_RS(void) { HD44780_GPIO->DATA &= ~RS; }

void set_HD44780_R_W(void) { HD44780_GPIO->DATA |= R_W; }
void clear_HD44780_R_W(void) { HD44780_GPIO->DATA &= ~R_W; }

void set_HD44780_ENABLE(void) {

  volatile uint32_t count, count_max = 1000000;
  HD44780_GPIO->DATA |= ENABLE;
  for (count = 0; count < count_max; count++)
    ;
}

void clear_HD44780_ENABLE(void) {
  volatile uint32_t count, count_max = 1000000;
  HD44780_GPIO->DATA &= ~ENABLE;
  for (count = 0; count < count_max; count++)
    ;
}

void enable(void){
	
	volatile uint32_t count, count_max = 50000;
	HD44780_GPIO->DATA |= ENABLE;
  for (count = 0; count < count_max; count++)
    ;	
  HD44780_GPIO->DATA &= ~ENABLE;
  for (count = 0; count < count_max; count++)
    ;

}
