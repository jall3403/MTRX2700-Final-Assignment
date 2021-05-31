#ifndef SERIAL
#define SERIAL

#define SCI1 21
#define SCI0 20
#define CLOCK_SPEED 24000000

typedef struct
{
    unsigned char port;
    unsigned int baud_rate;
    unsigned char CR_1;
    unsigned char CR_2;

}Serial_Port;

void set_serial(Serial_Port *_serial_port, unsigned char port, unsigned int baud_rate, unsigned char control_reg_1, unsigned char control_reg_2);

unsigned char is_SCI1_received(void);
unsigned char is_SCI0_received(void);

void print_from_sci1(unsigned char port);
void print_from_sci0(unsigned char port);
void output_string(unsigned char port, unsigned char *string);

#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt SCI0 void serial_interrupt_0 (void);
interrupt SCI1 void serial_interrupt_1 (void);
#pragma CODE_SEG DEFAULT
#endif