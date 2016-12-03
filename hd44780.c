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
  // for (count = 0; count < count_max; count++)
  //   ;

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
  write_data(0xC);
  enable();
///////

  write_data(0x8);
  enable();
  write_data(0x6);
  enable();

  write_HD44780_address(0x80);
  write_HD44780_data('L');
  write_HD44780_data('P');
  write_HD44780_data('C');
  write_HD44780_data('1');
  write_HD44780_data('1');
  write_HD44780_data('1');
  write_HD44780_data('4');
  write_HD44780_address(0xC0);
  write_HD44780_data('H');
  write_HD44780_data('D');
  write_HD44780_data('4');
  write_HD44780_data('4');
  write_HD44780_data('7');
  write_HD44780_data('8');
  write_HD44780_data('0');
  write_HD44780_address(0x0B);
  write_HD44780_address(0x0C);

  write_HD44780_string(0, "12345678");

}


unsigned int read_HD44780_busy_flag(void) {

	unsigned int busy_flag;
  clear_HD44780_RS();
  set_HD44780_R_W();
  HD44780_GPIO->DIR &= ~((DATA_4 | DATA_5 | DATA_6 | DATA_7));
  enable();
  busy_flag = (HD44780_GPIO->DATA)&DATA_7;
  enable();
  return busy_flag;
}

void write_HD44780_data(unsigned int value) {

  clear_HD44780_R_W();
  set_HD44780_RS();
  write_data(value >> 4);
  enable();
  write_data(value);
  enable();
  clear_HD44780_RS();
}

void write_HD44780_address(unsigned int value) {

  clear_HD44780_R_W();
  clear_HD44780_RS();
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

// Position
// 0  1  2  3  4  5  6  7 First line
// 8  9 10 11 12 13 14 15 Second Line
void write_HD44780_string(unsigned int position, char *str){
	unsigned int pos;
	char *pt;
	pt = str;

	if (position > 15)
		return;
	else if (position > 7)
		pos = 0xC0;
	else
		pos = 0x80;

	write_HD44780_address(pos | (position&0x7));
	while(*pt != 0)
		write_HD44780_data(*(pt++));
	return;
}

void set_HD44780_RS(void) { HD44780_GPIO->DATA |= RS; }
void clear_HD44780_RS(void) { HD44780_GPIO->DATA &= ~RS; }

void set_HD44780_R_W(void) { HD44780_GPIO->DATA |= R_W; }
void clear_HD44780_R_W(void) { HD44780_GPIO->DATA &= ~R_W; }

void set_HD44780_ENABLE(void) {

  HD44780_GPIO->DATA |= ENABLE;
}

void clear_HD44780_ENABLE(void) {//
  HD44780_GPIO->DATA &= ~ENABLE;
}

void enable(void){
	
	volatile uint32_t count, count_max = 50;
	HD44780_GPIO->DATA |= ENABLE;
  for (count = 0; count < count_max; count++)
    ;	
  HD44780_GPIO->DATA &= ~ENABLE;
  for (count = 0; count < count_max; count++)
    ;

}
