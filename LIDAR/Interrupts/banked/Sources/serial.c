#include "derivative.h"
#include "serial.h"

// Static variable to store data to be sent
unsigned char serial_string[100];
unsigned char *str_ptr = serial_string;

// Static variable to store data received
unsigned char input_string[100];
unsigned char *input_str_ptr = input_string;

// Flags to update when we have received
unsigned char SCI1_received = 0;
unsigned char SCI0_received = 0;

// Intialises serial by writing to the relevant registers
void initialise_serial(Serial_Port *_serial_port)
{
    unsigned long clock_ratio = CLOCK_SPEED / 16;   // Intermediary calculation for clock speed
    asm("sei");                                     // Disable all interrupts

    // Write to different registers depending on which port is being initialised
    if (1 == _serial_port -> port)
    {
        SCI1BDH = 0;
        SCI1BDL = (unsigned char)(clock_ratio / _serial_port ->baud_rate); // Calculation of serial board rate
        SCI1CR1 = _serial_port -> CR_1;
        SCI1CR2 = _serial_port -> CR_2; 
    }

    if (0 == _serial_port -> port)
    {
        SCI0BDH = 0;
        SCI0BDL = (unsigned char)(clock_ratio / _serial_port ->baud_rate);
        SCI0CR1 = _serial_port -> CR_1;
        SCI0CR2 = _serial_port -> CR_2; 

    }

}

// Sets serial port with values passed in
void set_serial(Serial_Port *_serial_port, unsigned char port, unsigned int baud_rate, unsigned char control_reg_1, unsigned char control_reg_2)
{
    _serial_port -> port = port;
    _serial_port -> baud_rate = baud_rate;
    _serial_port -> CR_1 = control_reg_1;
    _serial_port -> CR_2 = control_reg_2;

    initialise_serial(_serial_port); // Writes the values to the relevant serial port

}

// Copies the string given by a pointer to a static varialbe in memory
void copy_string(unsigned char *string)
{
    
    unsigned int i = 0;
   
   // Set the initial character
    serial_string[i] = *string;

    // Overwrite the string until the null terminating character is found
    while(*(++string) != '\0')
    {
        i++;
        serial_string[i] = *string;
       
    }
    i++;
    serial_string[i] = '\0'; // Add the null character at the end
    
    

    
    
   
}

// ISR for SCI0
interrupt SCI0 void serial_interrupt_0 (void)
{   
    // Check the status registers to see if data has been received or if ready to transmit

    // If received
    if (SCI0SR1 & 0x20)
    {
        // Check if it is the carraige return character
        if (SCI0DRL == 0x0d)
        {
            *input_str_ptr = '\0';        // Add terminating character
            SCI0_received = 1;            // Update flag if data needs to be printed


                
        }

        else
        {   
            *input_str_ptr = SCI0DRL;    // Store value from data register
            input_str_ptr++;

        }

        

    }
    
    // If ready to transmit
    else if (SCI0SR1 & 0x80)
    {
        // If not at the end of the string
        if ('\0' != *str_ptr) 
        {
          SCI0DRL = *str_ptr;           // Write the value to the data register
          str_ptr++;
          
        }
        
        else
        { 
        SCI0CR2 &= 0x7f;                // Disable TIE if at the end of the string
        }
    }

}


// ISR for SCI0
interrupt SCI1 void serial_interrupt_1 (void)
{

    // Check the status registers to see if data has been received or if ready to transmit

    // If received
    if (SCI1SR1 & 0x20)
    {
        // Check if it is the carraige return character
        if (SCI1DRL == 0x0d)
        {
            *input_str_ptr = '\0';         // Add terminating character
            SCI1_received = 1;             // Update flag if data needs to be printed


                
        }

        else
        {
            *input_str_ptr = SCI1DRL;       // Store value from data register
            input_str_ptr++;

        }

        

    }
    
    // If ready to transmit
    else if (SCI1SR1 & 0x80)
    {
        // If not at the end of the string
        if ('\0' != *str_ptr) 
        {
          SCI1DRL = *str_ptr;           // Write the value to the data register
          str_ptr++;
          
        }
        
        else
        { 
        SCI1CR2 &= 0x7f;                // Disable TIE if at the end of the string
        }
    }

    

}




// Sends the string to the relevant port to be printed
void output_string(unsigned char port, unsigned char *string)
{
    copy_string(string);        // Copy string and set pointer to the start
    str_ptr = serial_string;
    
    // Enable TIE according to the port until the end of the string
    if (1 == port)
    {
        while('\0' != *str_ptr) 
        {
          
        SCI1CR2 |= 0x80;    // Enable TIE
        }
        
    }

    else if (0 == port)
    {
        while ('\0' != *str_ptr)
        {
            SCI0CR2 |= 0x80;
        }
    }

}

// Returns true when a string is received from SCI1
unsigned char is_SCI1_received(void)
{
    return SCI1_received;
}

// Returns true when a string is received from SCI0
unsigned char is_SCI0_received(void)
{
    return SCI0_received;
}

// Prints string received from SCI1 to the port given
void print_from_sci1(unsigned char port)
{
    output_string(port, input_string);
    input_str_ptr = input_string;
    SCI1_received = 0;    // Reset flag
}

// Prints string received from SCI0 to the port given
void print_from_sci0(unsigned char port)
{
    output_string(port, input_string);
    input_str_ptr = input_string;
    SCI0_received = 0;      // Reset flag
}


