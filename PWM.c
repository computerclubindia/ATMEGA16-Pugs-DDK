/* Program:: Panting LED using the principle of Pulse Width Modulation (PWM)
   Author :: Vinay.V.S (Student of Electronics & Communication Engg., NIE Mysore)
   Date   :: 11/7/2011
   
   Description:: 
                 1. This program works on the principle of PWM, ie.. the ON time of the pulse is varied constantly, which in turn results in a varied brightness of the LED. 
                 2. The Green LED named PGM (present already on the board) & an LED connected to any pin of PORTC are made to glow in a fashion, which resembles our breathing/panting style,, ie.. the LED grows gradually in brightness to its maximum level, then goes back to the OFF state, in the order of decreasing brightness & so on.. 

   Optimisations:: For better results, use a 10mm white LED at any one pin of PORTC.
   NOTE:: See to it that, you connect the big fat white LED through a transistor, else you may load down the pin of the microcontroller, thus damaging it.
   
   TIPS FOR CONNECTING THE TRANSISTOR (in my example, I use BC547, an NPN transistor)::
              1. Connect the base of the transistor through a 1k ohm resistor to any one of the pins of PORTC of ATMEGA16.
              2. Connect a 300 ohm (because the drop across the white LED is approx. 3V) resistor in series with the LED & connect this series combination in between the supply (Vcc) & the collector of the transistor. Take care of the polarity of the LED while doing so.
              3. Ground the Emitter of BC547 transistor. This is done by connecting the emitter to the negative of the battery/DC supply source.
              4. ***NOTE*** Very important** Always make a common ground connection between the DDK and the external LED+transistor+battery assembly.Different reference levels may be harmful to the controller.

   Application:: This one may be used as a time reference while performing breathing exercises, viz,, a person can inhale in accordance with the rise in brightness of the LED and exhale with the decrease in brightness of the LED.      
*/

#include <avr/io.h>
#include <util/delay.h>
#define T 10    // Total time period of square pulse = 10ms
#define STEP 0.04 /* 'STEP' specifies the time interval between each increment/decrement in the ON time (ie.. it is the value by which the ON time is incremented/decremented each time within the 'for' loop */
void init_io(void)
{
	// 1 = output, 0 = input
	DDRB = 0b11111111; // All outputs
	DDRC = 0b11111111; // All outputs
}
int main(void)
{ init_io(); // initialising PORTB & PORTC as output ports
  float t1; // Variable 't1' denotes the ON time
  while(1) // infinite loop ; can also use --> 'for(;;)' instead
     {
       for(t1=0.0;t1<=10.0;t1+=STEP) /* loop for causing the inhaling effect ie.. gradually increasing brightness of the LED */
	    {  PORTB=0xff;
               PORTC=0xff;
	       _delay_ms(t1);
	       PORTC=0x00;
               PORTB=0x00;
	       _delay_ms(T-t1); //(T-t1)=OFF time --> (total time - ON time)
	    }
	 
       for(t1=10.0;t1>=0.0;t1-=STEP) /* loop for causing the exhaling effect ie.. gradually decreasing brightness of the LED */
	     {PORTC=0xff;
	       PORTB=0xff;
	       _delay_ms(t1);
	       PORTC=0x00;
	       PORTB=0x00;
	       _delay_ms(T-t1);
	     }
       /*-----------------------------------------------*/	
        PORTB=0x00;
	PORTC=0x00;
	_delay_ms(5.0); /* excessive charge carriers always exist at the P-N junction of the LED, as a result of which, it wont turn off immediately even after the supply is cut-off.. Thus the ports are turned off for an additional short interval of time of 5ms which waits for the excessive charge carriers to be removed completely from the P-N junction, thus turning the LED off */    

     }
}

