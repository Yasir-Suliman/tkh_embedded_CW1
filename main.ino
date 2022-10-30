#include "avr/io.h"
#include "stdio.h"
#include "adc.h"
#include "UART.h"
#include "dio.h"
#include <util/delay.h>

void init();

int main(){
  init();

  while(1) // endless loop
  {
    int pot_data = ADC_read(0b00000101); // read potentiometer connected on channel 5
    int button_press = ADC_read(0b00000011); // read button connected on channel 3
    int ldr_data = ADC_read(0b00000100);

    Serial.println(ldr_data);
    
    // Serial.print("POT: ");
    // Serial.println(pot_data);

    if(button_press != 0){ // runs when button is pressed
      // send_string_uart("BtnPressed");
    
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
      //send_string_uart("BtnOFF");
    }

    if(pot_data < 256 & pot_data > 0){
      DIO_SetPinState('d', 4, 'l');
      DIO_SetPinState('d', 5, 'l');
      DIO_SetPinState('d', 6, 'l');
      DIO_SetPinState('d', 7, 'l');
            
      // DIO_SetPinState('d', 4, 'l');
      // DIO_SetPinState('d', 5, 'l');
      // DIO_SetPinState('d', 6, 'l');
      DIO_SetPinState('d', 7, 'h');
    }
    else if (pot_data <= 512 & pot_data > 256){
      DIO_SetPinState('d', 4, 'l');
      DIO_SetPinState('d', 5, 'l');
      DIO_SetPinState('d', 6, 'l');
      DIO_SetPinState('d', 7, 'l');
      
      // DIO_SetPinState('d', 4, 'l');
      // DIO_SetPinState('d', 5, 'l');
      DIO_SetPinState('d', 6, 'h');
      // DIO_SetPinState('d', 7, 'h');
    }
    else if (pot_data <= 768 & pot_data > 512){
      DIO_SetPinState('d', 4, 'l');
      DIO_SetPinState('d', 5, 'l');
      DIO_SetPinState('d', 6, 'l');
      DIO_SetPinState('d', 7, 'l');
      
      // DIO_SetPinState('d', 4, 'l');
      DIO_SetPinState('d', 5, 'h');
      // DIO_SetPinState('d', 6, 'h');
      // DIO_SetPinState('d', 7, 'h');   
    }
    else if (pot_data <= 1024 & pot_data > 768){
      DIO_SetPinState('d', 4, 'l');
      DIO_SetPinState('d', 5, 'l');
      DIO_SetPinState('d', 6, 'l');
      DIO_SetPinState('d', 7, 'l');
      
      DIO_SetPinState('d', 4, 'h');
      // DIO_SetPinState('d', 5, 'h');
      // DIO_SetPinState('d', 6, 'h');
      // DIO_SetPinState('d', 7, 'h');     
    } else if(pot_data == 0){
      DIO_SetPinState('d', 4, 'l');
      DIO_SetPinState('d', 5, 'l');
      DIO_SetPinState('d', 6, 'l');
      DIO_SetPinState('d', 7, 'l');      
    }

    if(ldr_data < 256){
      //send_string_uart("LowLightWarning");
      DIO_SetPinState('d', 3, 'h');
      _delay_ms(250);
      DIO_SetPinState('d', 3, 'l');
      _delay_ms(250);    
    } else{
      DIO_SetPinState('d', 3, 'l');
    }
    
    _delay_ms(200); // delay for 200ms
  }
}

void init(){
  ADC_init(); // Initialize adc
  Serial.begin(9600);
  //set pins PB0 - PB2 as output
  DIO_SetPinDirection('b', 0, 'o');
  DIO_SetPinDirection('b', 1, 'o');
  DIO_SetPinDirection('b', 2, 'o');
  
  //set pins PD4 - PD7 as output
  DIO_SetPinDirection('d', 7, 'o');
  DIO_SetPinDirection('d', 6, 'o');
  DIO_SetPinDirection('d', 5, 'o');
  DIO_SetPinDirection('d', 4, 'o');
  DIO_SetPinDirection('d', 3, 'o');

  // set pins PC3 - PC5 as input
  DIO_SetPinDirection('c', 3, 'i');
  DIO_SetPinDirection('c', 4, 'i');
  DIO_SetPinDirection('c', 5, 'i');
}