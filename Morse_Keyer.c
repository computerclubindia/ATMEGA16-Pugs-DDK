/* Program :: Morse_Keyer
    Author   :: Vinay.V.S
    Description::   

*/

#include <avr/io.h>
#include <util/delay.h>

void init_io(void)
{
	// 1 = output, 0 = input
	DDRB = 0b11111111; // All outputs
	DDRC = 0b11111111; // All outputs
	DDRD = 0b11111110; // PORTD (RX on PD0). Just for demo
}

int main(void)
{
	init_io();
        int i,y,x,a=0x55,b[8];

        y=a & 0x0F;
        
        for(i=0;i<4;i++)
          {b[i]=y%0x02;
            y=y/0x02;            
           }
         
         x=a & 0xF0;
         x=x>>4;
         
         for(i=4;i<8;i++)
          {b[i]=x%0x02;
           x=x/0x02;           
          }
         
	while (1)
	{      for(i=7;i>=0;i--)
		{  if(b[i]==0x01)
                        {PORTB=0xFF;
                           _delay_ms(1000);}
                   else
                        {PORTB=0x00;
                        _delay_ms(1000);}
                  
                    PORTB=0x00;
                  _delay_ms(50);                
		}
		_delay_ms(4000);
	}

	return 0;
}
