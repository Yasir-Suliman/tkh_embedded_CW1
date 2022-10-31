#include "avr/io.h"
#include "stdio.h"
#include "adc.h"
#include "UART.h"
#include "dio.h"
#include <util/delay.h>

#define ldr 4 // ldr pin 4
#define pot 5 // potentiometer pin 5
#define btn 3 // button pin 3

void init();

int main(){
  init();

  while(1) // endless loop
  {
    int pot_data = ADC_read(pot); // read potentiometer connected on channel 5
    int button_press = ADC_read(btn); // read button connected on channel 3
    int ldr_data = ADC_read(ldr); // read ldr connected on pin 4
    
    char pot_data_string [5]; // empty string for pot value
    char ldr_data_string [5]; // empty string for ldr value

    itoa(pot_data,pot_data_string,10); //converting pot data from int to string to send over uart
    itoa(ldr_data,ldr_data_string,10); //converting ldr data from int to string to send over uart 
     

    if(button_press != 0){ // runs when button is pressed
      send_string_uart("BtnPressed\n");
      send_string_uart("\n");
      
      // led sequence
      DIO_SetPinState('b', 0, 'h');
      _delay_ms(250);
      DIO_SetPinState('b', 1, 'h');
      _delay_ms(250);
      DIO_SetPinState('b', 2, 'h');
      _delay_ms(250);
      DIO_SetPinState('b', 2, 'l');
      _delay_ms(250);
      DIO_SetPinState('b', 1, 'l');
      _delay_ms(250);
      DIO_SetPinState('b', 0, 'l');
      _delay_ms(250);      
            
    } else{ // runs when button not pressed
      send_string_uart("BtnOFF");
      send_string_uart("\n");
    }

    if(pot_data < 256 & pot_data > 0){ // turning on led on pin 7 when value is from 1-256
      send_string_uart("POT: ");
      send_string_uart(pot_data_string);
      send_string_uart("\n");
      
      DIO_SetPinState('d', 4, 'l');
      DIO_SetPinState('d', 5, 'l');
      DIO_SetPinState('d', 6, 'l');
      DIO_SetPinState('d', 7, 'l');
            
      DIO_SetPinState('d', 7, 'h');
    }
    else if (pot_data <= 512 & pot_data > 256){ // turning on led on pin 6 when value is from 256-512
      // sending pot value
      send_string_uart("POT: ");
      send_string_uart(pot_data_string);
      send_string_uart("\n");
      
      DIO_SetPinState('d', 4, 'l');
      DIO_SetPinState('d', 5, 'l');
      DIO_SetPinState('d', 6, 'l');
      DIO_SetPinState('d', 7, 'l');
      
      DIO_SetPinState('d', 6, 'h');
    }
    else if (pot_data <= 768 & pot_data > 512){ // turning on led on pin 5 when value is from 512-768
      //sending pot value      
      send_string_uart("POT: ");
      send_string_uart(pot_data_string);
      send_string_uart("\n");
      
      DIO_SetPinState('d', 4, 'l');
      DIO_SetPinState('d', 5, 'l');
      DIO_SetPinState('d', 6, 'l');
      DIO_SetPinState('d', 7, 'l');

      DIO_SetPinState('d', 5, 'h');
    }
    else if (pot_data <= 1023 & pot_data > 768){ // turning on led on pin 4 when value is from 768-1023
      // sending pot value
      send_string_uart("POT: ");
      send_string_uart(pot_data_string);
      send_string_uart("\n");
      
      DIO_SetPinState('d', 4, 'l');
      DIO_SetPinState('d', 5, 'l');
      DIO_SetPinState('d', 6, 'l');
      DIO_SetPinState('d', 7, 'l');
      
      DIO_SetPinState('d', 4, 'h');  
    } else if(pot_data == 0){ // turning off all leds when pot value is 0
      // sending pot value
      send_string_uart("POT: ");
      send_string_uart(pot_data_string);
      send_string_uart("\n");
      
      DIO_SetPinState('d', 4, 'l');
      DIO_SetPinState('d', 5, 'l');
      DIO_SetPinState('d', 6, 'l');
      DIO_SetPinState('d', 7, 'l');      
    }

    if(ldr_data < 256){
      // sending ldr value
      send_string_uart("LowLightWarning ");
      send_string_uart(ldr_data_string);
      send_string_uart("\n");

      // blinking ldr warning led
      DIO_SetPinState('d', 3, 'h');
      _delay_ms(250);
      DIO_SetPinState('d', 3, 'l');
      _delay_ms(250);    
    } else{
      // sending ldr value      
      send_string_uart("LDR: ");
      send_string_uart(ldr_data_string);
      send_string_uart("\n");

      // setting ldr warning led to low
      DIO_SetPinState('d', 3, 'l');
    }
    
    _delay_ms(200); // delay for 200ms
  }
}

void init(){
  DIO_init();
  ADC_init(); // Initialize adc
  Serial.begin(9600);

}