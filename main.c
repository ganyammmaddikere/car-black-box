/*
 * File:   main.c
 * Author: ganya
 *
 * Created on 22 December, 2024, 6:42 PM
 */


#include <xc.h>
#include "i2c_1.h"
#include "ds1307_1.h"
#include "main.h"
#include "switch.h"
#include "clcd.h"
#include "adc.h"
#include "ex_eeprom.h"
#include "operation.h"
#include "view.h"
#include "uart.h"

unsigned char EV[9][3]={"ON","GN","G1","G2","G3","G4","G5","GR","CN"};
	 static unsigned int i;
     unsigned int adc_reg_val=0;
    static unsigned int adc=0;
     unsigned int add=0;
     unsigned int flag=1;
     unsigned int state=1;
     unsigned int add1=12;
     unsigned int temadd=0;
      unsigned int count=0;
       unsigned int ones=1;
    
     unsigned char clock_reg[3];
unsigned char calender_reg[4];
unsigned char time[9];
unsigned char date[11];


void store_eeprom(void  )
     { 
 
    for(int m=0;m<8;m++)
    {
          write_E(add,time[m]);
          add++;
    }
    for(int j=0;j<2;j++)
    {
         write_E(add,EV[i][j]);
         add++;
    }
     write_E(add++,(adc/10)+'0');
     
      write_E(add++,(adc%10)+'0');
      
      if(add>=120)
      {
          add=0;
      }
      count++;
      
     
     }
unsigned char key;
void key_press(void)
{
	


	key = read_switches(STATE_CHANGE);
    if(flag==1)
    {
	if (key == MK_SW1)
	{ 
		i=8;
        store_eeprom();
	}
	if(key == MK_SW2)
    {
       
        if(i>=0 && i<7)
        {
            i++;
        }
        else if(i==8)
        {
            i=1;
        }
        store_eeprom(); 
    }
    if(key == MK_SW3 )
    {
        if(i==8)
        {
            i=1;   
         }
  else if(i>1)
        {
            i--;
        }
         store_eeprom();
    }
    if(key==MK_SW11)
    {
        flag=0;
         state=2;
    }
    if(flag==1)
    {
    clcd_print(EV[i], LINE2(9));
    }
}
}
void speed(unsigned int adc_reg_val)
{
   
   if(flag==1)
   {
       adc=adc_reg_val/10.25;
    
    clcd_putch('0'+(adc/10),LINE2(14));
    clcd_putch('0'+(adc%10),LINE2(15));
   }
}
static void get_time(void)
{
	clock_reg[0] = read_ds1307(HOUR_ADDR);
	clock_reg[1] = read_ds1307(MIN_ADDR);
	clock_reg[2] = read_ds1307(SEC_ADDR);

	if (clock_reg[0] & 0x40)
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	else
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	time[2] = ':';
	time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);
	time[4] = '0' + (clock_reg[1] & 0x0F);
	time[5] = ':';
	time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);
	time[7] = '0' + (clock_reg[2] & 0x0F);
	time[8] = '\0';
}

void display_time(void)
{
	clcd_print(time, LINE2(0));
}
void init_config(void)
{
	init_matrix_keypad();
	init_clcd();
      init_adc();
      init_i2c();
	init_ds1307();
    init_uart();
    TRISB0= 0;
    RB0=0;
	clcd_print("  TIMER  EV   SD", LINE1(0));
   
}

void main(void)
{
	init_config();

	while(1)
	{
       
   
		key_press();
       
        if(state==1)
        {
        adc_reg_val = read_adc(CHANNEL4);
         flag=1;
         speed(adc_reg_val);
          get_time();
		display_time();
        if(ones==1)
    {
        store_eeprom();
       
       ones=0; 
    }
        }
        else if(state==2)
        {
            menu_v();
        } 
        else if(state==3)
        {
          
            view_log();
        }
        else if(state==4)
        {
            clear_log();
        }
        else if(state==5)
        {
            down_log();
        }
         else if(state==6)
        {
            set_time();
        }
    }    
    
}

