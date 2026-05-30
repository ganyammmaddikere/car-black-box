#ifndef VIEW_H
#define	VIEW_H
void store_eeprom(void);
void view_log(void);
void read_ev(void);
void clear_log(void);
void down_log(void);
void set_time(void);
void print_clcd(void);
void write_ds1307(unsigned char address1,  unsigned char data);
unsigned char read_ds1307(unsigned char address1);
#define MIN_ADDR		0x01
#define HOUR_ADDR		0x02
#define DAY_ADDR		0x03
#define SEC_ADDR		0x00
#endif



