#include <xc.h>
#include "main.h"
#include "switch.h"
#include "clcd.h"
#include "adc.h"
#include "ex_eeprom.h"
#include "operation.h"
#include "view.h"
# include "uart.h"
#include<string.h>
extern unsigned int back=1;
extern unsigned char key;
extern unsigned int i=0;
 extern unsigned int state=1;
 unsigned char read[10][15];
 extern unsigned int count;
 extern unsigned int flag1=0; 
 unsigned int co=0;
  unsigned int m=0,delay=0,nil=0,n=0,flag3=0;
  unsigned int counts=0;
 static unsigned int down=0;
  unsigned char e_p=0;
 unsigned int hrs, min, sec,delay1=0;
extern unsigned char time[9];
  void read_events(void)
  {
      int end;
      if(count>10)
      {
          e_p=((count%10)*12);
          end=10;
      }
      for(int i=0;i<end;i++)
      {
          
          for(int j=0;j<15;j++)
          {
              if(j==8 || j==11)
              {
                  read[i][j]= ' ';
              }
           
              else if(j==14)
              {
                  read[i][j]='\0';
              }
              else
              {
                  read [i][j]=read_E(e_p++);
                  if(e_p>=120)
                      e_p=0;
              }
          }
           
      }
     
  }
void view_log(void)
{
    
    clcd_print("L   TIME   EV SP", LINE1(0));
    if(m==0)
    {
    read_events();
    m=1;
    }
    int end;
  
  if(count > 10)
    {
        end = 10;
    }
    else
    {
        end = count;
    }
    if (key == MK_SW12 && i < end - 1) {
        i++;
    }
    if (key == MK_SW11 && i> 0) {
        i--;
    }
    if(count == 0)
    {
        clcd_print("________________", LINE1(0));
        clcd_print("NO EVENTS STORED", LINE2(0));
//        return;
    }
    else
    {
    clcd_putch((i ) + '0', LINE2(0));
    clcd_print(read[i], LINE2(2));
    }
   
    
     if(key==MK_SW2)
     {
         clcd_clear();
         state=2;
         i=back;
     }
      

  
}
void clear_log(void)
{
     clcd_print("CLEARING...            ", LINE1(0));
    clcd_print("LOGS                   ", LINE2(0));
    
    if(nil++==3000)
        state = 2;
        count = 0;
         flag1=0;
            i=0;
}
void down_log(void)
{
    read_events();  
    clcd_print("DOWNLOADING...    ",LINE1(0));
    clcd_print("LOGS              ",LINE2(0));
    int end;
   
    if(count>9)
    {
        end=10;
    }
    else 
    {
        end=count;
    }
    if(count==0)
    {
        puts("----------------------");
        puts("___NO EVENTS STORED___");
        puts("----------------------");
        state=2;
        
    }
    
    else
    {
        
        while(delay++==50)
        {
            delay=0;
            state=2;
            flag1=0;
            i=0;
            clcd_clear();
            if(down>=9)
            {
                down=0;
            }
           
        puts("\n-----------------");
        puts("\n\r");
        puts("L TIME     EV SP\n\r");
        
        puts("------------------");
        for (int i = 0; i < end; i++)
        {
            puts("\n\r");
           
            putch((down ) + '0');
             down++;
             
            putch(' ');
            puts(read[i]);

        }
        
        puts("\n\r");
        puts("------------------\n\r");
         
        }
        
    }
}
void print_clcd(void)
{
    clcd_putch(hrs / 10 + '0', LINE2(4));
    clcd_putch(hrs % 10 + '0', LINE2(5));

    clcd_putch(':', LINE2(6));

    clcd_putch(min / 10 + '0', LINE2(7));
    clcd_putch(min % 10 + '0', LINE2(8));

    clcd_putch(':', LINE2(9));

    clcd_putch(sec / 10 + '0', LINE2(10));
    clcd_putch(sec % 10 + '0', LINE2(11));

}
void set_time(void )
{
    clcd_print("    HH:MM:SS    ", LINE1(0));
    clcd_print("    ", LINE2(0));
    clcd_print("    ", LINE2(12));
    if (flag3 == 0) {
        hrs = ((time[0] - '0')*10) + (time[1] - '0');
        min = ((time[3] - '0')*10) + (time[4] - '0');
        sec = ((time[6] - '0')*10) + (time[7] - '0');
        flag3++;
    }
    if (key == MK_SW11) 
    {
        if (flag3 == 1)
        { 
            if (++hrs == 24)// Increment hours
            {
                hrs = 0;
            }
        }
        else if (flag3 == 2) 
        { 
            if (++min == 60)// Increment minutes
            {
                min = 0;
            }
        }
        else if (flag3 == 3) 
        { 
            if (++sec == 60) // Increment seconds
            {
                sec = 0;
            }
        }
    }

    if (flag3 == 1)
    {
        if (delay1++ <= 500) 
        {
            print_clcd();
        } 
        else if (delay1++ <= 1000)
        {
            clcd_putch(0xFF, LINE2(4));
            clcd_putch(0xFF, LINE2(5));

        } else
        {
            delay1 = 0;
        }
    }

    if (flag3 == 2)
    {
        if (delay1++ <= 500) 
        {
            print_clcd();
        } 
        else if (delay1++ <= 1000)
        {
            clcd_putch(0xFF, LINE2(7));
            clcd_putch(0xFF, LINE2(8));
        } else {
            delay1 = 0;
        }
    }

    if (flag3 == 3) 
    {
        if (delay1++ <= 500) 
        {
            print_clcd();
        } 
        else if (delay1++ <= 1000) 
        {
            clcd_putch(0xFF, LINE2(10));
            clcd_putch(0xFF, LINE2(11));
        } else 
        {
            delay1 = 0;
        }
    }
    if (key == MK_SW12) {
        if (++flag3 == 4) {
            flag3 = 1;
        }
    }
    if (key == MK_SW1) {
        write_ds1307(HOUR_ADDR, (((hrs / 10) << 4) | (hrs % 10)));
        write_ds1307(MIN_ADDR, (((min / 10) << 4) | (min % 10)));
        write_ds1307(SEC_ADDR, (((sec / 10) << 4) | (sec % 10)));

        state = 2;
    }
    if (key == MK_SW2) {
        state = 2;
        
    }
    
}
        
    
