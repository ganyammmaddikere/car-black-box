 #include <xc.h>
#include "main.h"
#include "switch.h"
#include "clcd.h"
#include "adc.h"
#include "eeprom.h"
#include "operation.h"
extern unsigned char key;
extern unsigned int state=1;
unsigned int i=0;
unsigned int menu_flag=0; 
unsigned int back=1,click=0; 

unsigned char menu[4][17]={"VIEW LOG        ","CLEAR LOG       ","DOWNLOAD LOG     ","SET TIME        "};
void menu_v(void)
{
    
       if(key==MK_SW12)
        {           
          if(menu_flag==1)
            {
            if(i<3)
            {
                i++;                 
             }
            else if(i==3)
            {  
                i=3;           
            }
            }
            menu_flag=1;
        }
        if(key == MK_SW11)
        {
            if(menu_flag==0)
            {               
            if(i>0)
               {
                 i--;                 
               } 
            if(i==0)
               {
                  i=0;     
               }
        }
            menu_flag=0;
        }
       click = i;
        if(menu_flag==1)
        {     
            clcd_print("->", LINE2(0));
            clcd_print("  ", LINE1(0));
            click++;    
        } 
             else if(menu_flag==0)
        {
             clcd_print("  ", LINE2(0));
            clcd_print("->", LINE1(0));   
        }
     if(i!=3)
     {
        clcd_print(menu[i], LINE1(2));
        clcd_print(menu[i+1], LINE2(2)); 
     }
    else if (i==3)
    {
        clcd_print(menu[i], LINE2(2));
         clcd_print(menu[i-1], LINE1(2)); 
     }
       if(key==MK_SW1)
       {
           if(click==0)
           {
               state=3;
               
           }
           else if(click==1)
           {
               state=4;
           }
            else if(click==2)
           {
               state=5;
           }
            else if(click==3)
           {
               state=6;
           }
       }
     back=i;
     if (key == MK_SW2) {
        state = 1;
       
        CLEAR_DISP_SCREEN;
        clcd_print("  TIMER  EV   SD", LINE1(0));
    }
    
}  
