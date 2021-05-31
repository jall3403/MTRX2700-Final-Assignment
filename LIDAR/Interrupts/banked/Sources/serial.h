#ifndef SERIAL
#define SERIAL

// Macros for interrupt vector numbers
#define SCI1 21
#define SCI0 20

#define CLOCK_SPEED 24000000

// Struct for serial port
typedef struct
{
    unsigned char port;         // Port number
    unsigned int baud_rate;
    unsigned char CR_1;         // Value for Control Register 1
    unsigned char CR_2;         // Value for Control Register 2

}Serial_Port;

// Initialises serial port with values passed in
void set_serial(Serial_Port *_serial_port, unsigned char port, unsigned int baud_rate, unsigned char control_reg_1, unsigned char control_reg_2);

// ISRs for SCI0 and SCI1
interrupt SCI0 void serial_interrupt_0 (void);
interrupt SCI1 void serial_interrupt_1 (void);

// Sends the string to the relevant port to be printed
void output_string(unsigned char port, unsigned char *string);

// Checks if data has been received
unsigned char is_SCI1_received(void);
unsigned char is_SCI0_received(void);

// Prints data received from the ports
void print_from_sci1(unsigned char port);
void print_from_sci0(unsigned char port);

#endif