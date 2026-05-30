#ifndef EX_EEPROM_H
#define	EX_EEPROM_H


#define SLAVE_READ_E		0xA1
#define SLAVE_WRITE_E		0xA0
void write_E(unsigned char address1,  unsigned char data);
unsigned char read_E(unsigned char address1);
#endif





