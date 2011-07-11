/* Program :: Morse_Keyer
    Author   :: Vinay.V.S
    Description:: The following program generates the binary pattern of a number or ASCII value of a character stored in the variable 'a' and displays
the pattern one bit at a time on the PGM LED present on-board, starting with the MSB, with a delay of 50ms in between each bit and a delay of 4 sec in between each repetition of the complete 8-bit pattern.
*/

#include <avr/io.h>
#include <util/delay.h>

void init_io(void)
{
	// 1 = output, 0 = input
	DDRB = 0b11111111; // All outputs
}

int main(void)
{
	init_io(); // initialising PORTB as an output port
        int i,y,x;
        int a=0x55; //value whose binary patter will be displayed on the PGM LED
        int b[8];  // array of size 8 for storing the 8-bit binary pattern of the number or ASCII value stored in variable 'a'

        y=a & 0x0F; // masking the upper nibble of the number/ASCII value of a character stored in the variable 'a'
        
     /* Hex-to-Binary Converter & stores the binary pattern in the array 'b[i]' from i=0 to 3*/ 
       for(i=0;i<4;i++)
          {b[i]=y%0x02;
            y=y/0x02;            
           }
         
         x=a & 0xF0; // masking the lower nibble of the binary pattern of the number stored in variable 'a' 
         x=x>>4; // Logical shifting of the binary pattern to the right to facilitate division operation in the Hex - Binary conversion to follow
         
         /* Hex to Binary conversion & storing the binary pattern in the array 'b[i]' from i=4 to 7 */
         for(i=4;i<8;i++)
          {b[i]=x%0x02;
           x=x/0x02;           
          }
         
/* Binary pattern output on the PGM LED (connected to PORTB) on-board*/	
       while (1)
	{      for(i=7;i>=0;i--)
		{  if(b[i]==0x01)
                        {PORTB=0xFF;
                           _delay_ms(1000); // display the bit status for 1 sec
                        }
                   else
                        {PORTB=0x00;
                        _delay_ms(1000); // display the bit status for 1 sec
                        }
                  
                    PORTB=0x00;
                  _delay_ms(50); // tiny OFF time of 50ms to facilitate the distinction between each bit of the binary pattern               
		}
		_delay_ms(4000); // Large delay of 4 sec to facilitate the distinction between the repetition of the same, complete 8-bit pattern of the number
	}

	return 0;
}
