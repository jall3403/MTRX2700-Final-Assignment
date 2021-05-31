#include "derivative.h"
#include "serial.h"

unsigned char serial_string[100];
unsigned char *str_ptr = serial_string;

unsigned char input_string[100];
unsigned char *input_str_ptr = input_string;

unsigned char SCI1_received = 0;
unsigned char SCI0_received = 0;

void initialise_serial(Serial_Port *_serial_port)
{
    unsigned long clock_ratio = CLOCK_SPEED / 16;
    asm("sei");
    if (1 == _serial_port -> port)
    {
        SCI1BDH = 0;
        SCI1BDL = (unsigned char)(clock_ratio / _serial_port ->baud_rate);
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

void set_serial(Serial_Port *_serial_port, unsigned char port, unsigned int baud_rate, unsigned char control_reg_1, unsigned char control_reg_2)
{
    _serial_port -> port = port;
    _serial_port -> baud_rate = baud_rate;
    _serial_port -> CR_1 = control_reg_1;
    _serial_port -> CR_2 = control_reg_2;

    initialise_serial(_serial_port);

}

void copy_string(unsigned char *string)
{
    
    // unsigned char *str_ptr;
    unsigned int i = 0;
   
    serial_string[i] = *string;

    while(*(++string) != '\0')
    {
        i++;
        serial_string[i] = *string;
        



    }
    i++;
    serial_string[i] = '\0';
    
    

    
    
    // str_ptr = serial_string;

    // if(1 == port)
    // {
    //     SCI1DRL = serial_string[0];
    //     SCI1CR2 |= 0x80;
    // }
}

void output_serial(unsigned char port, unsigned char *string)
{
    
    copy_string(string);
    str_ptr = serial_string;
    
    if (1 == port)
    {
        while('\0' != *str_ptr) 
        {
          
        //SCI1DRL = *str_ptr;
        SCI1CR2 |= 0x80;
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




void output_string(unsigned char port, unsigned char *string)
{
    copy_string(string);
    str_ptr = serial_string;
    
    if (1 == port)
    {
        while('\0' != *str_ptr) 
        {
          
        //SCI1DRL = *str_ptr;
        SCI1CR2 |= 0x80;
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

unsigned char is_SCI1_received(void)
{
    return SCI1_received;
}

unsigned char is_SCI0_received(void)
{
    return SCI0_received;
}

void print_from_sci1(unsigned char port)
{
    output_string(port, input_string);
    input_str_ptr = input_string;
    SCI1_received = 0;
}

void print_from_sci0(unsigned char port)
{
    output_string(port, input_string);
    input_str_ptr = input_string;
    SCI0_received = 0;
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt SCI0 void serial_interrupt_0 (void)
{
    if (SCI0SR1 & 0x20)
    {
        if (SCI0DRL == 0x0d)
        {
            *input_str_ptr = '\0';
            //output_string(1, input_string);
            SCI0_received = 1;


                
        }

        else
        {
            *input_str_ptr = SCI0DRL;
            input_str_ptr++;

        }

        //input_str_ptr++;
        

    }
    
    else if (SCI0SR1 & 0x80)
    {
        if ('\0' != *str_ptr) 
        {
          SCI0DRL = *str_ptr;
          str_ptr++;
          
        }
        
        else
        { 
        SCI0CR2 &= 0x7f;
        }
    }

}

interrupt SCI1 void serial_interrupt_1 (void)
{

    //unsigned char local_sci1sri = SCI1SR1;
    //unsigned char local_sci1drl = SCI1DRL;
    if (SCI1SR1 & 0x20)
    {
        if (SCI1DRL == 0x0d)
        {
            *input_str_ptr = '\0';
            //output_string(1, input_string);
            SCI1_received = 1;


                
        }

        else
        {
            *input_str_ptr = SCI1DRL;
            input_str_ptr++;

        }

        //input_str_ptr++;
        

    }
    
    else if (SCI1SR1 & 0x80)
    {
        if ('\0' != *str_ptr) 
        {
          SCI1DRL = *str_ptr;
          str_ptr++;
          
        }
        
        else
        { 
        SCI1CR2 &= 0x7f;
        }
    } 

}
#pragma CODE_SEG DEFAULT


