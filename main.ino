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
    
    // Serial.print("POT: ");
    // Serial.println(pot_data);

    if(button_press != 0){ // runs when button is pressed
      DIO_SetPinState('d', 3, 'h'); // setting pin PD3 as high      
    } else{ // runs when button not pressed
      DIO_SetPinState('d', 3, 'l'); // setting pin PD3 as low       
    }
    Serial.print("Button: ");
    Serial.println(button_press);

    if(pot_data > 512){ //
      DIO_SetPinState('d', 4, 'h');
      DIO_SetPinState('d', 5, 'h');
      DIO_SetPinState('d', 6, 'h');
      DIO_SetPinState('d', 7, 'h');
      Serial.print("Warning value is: ");
      Serial.println(pot_data);      
    } else{
      DIO_SetPinState('d', 4, 'l');
      DIO_SetPinState('d', 5, 'l');
      DIO_SetPinState('d', 6, 'l');
      DIO_SetPinState('d', 7, 'l');
      Serial.println(pot_data);      
    }
    char pot_char[16]; // empty string
    // Serial.println(pot_char);
    // itoa(pot_data, pot_char, 10);
    // send_char_uart(pot_char);
    // char data_read = read_data_uart();
    // Serial.println(data_read);

    // if(pot_data < 50 & pot_data > 0){
    //   DIO_SetPinState('d', 4, 'l');
    //   DIO_SetPinState('d', 5, 'l');
    //   DIO_SetPinState('d', 6, 'l');
    //   DIO_SetPinState('d', 7, 'l');
            
    //   DIO_SetPinState('d', 4, 'h');
    //   DIO_SetPinState('d', 5, 'l');
    //   DIO_SetPinState('d', 6, 'l');
    //   DIO_SetPinState('d', 7, 'l');
    //   Serial.println("LEDS: 1000");
    // }
    // else if (pot_data <= 256 & pot_data > 50){
    //   DIO_SetPinState('d', 4, 'l');
    //   DIO_SetPinState('d', 5, 'l');
    //   DIO_SetPinState('d', 6, 'l');
    //   DIO_SetPinState('d', 7, 'l');
      
    //   DIO_SetPinState('d', 4, 'h');
    //   DIO_SetPinState('d', 5, 'h');
    //   DIO_SetPinState('d', 6, 'l');
    //   DIO_SetPinState('d', 7, 'l');
    //   Serial.println("LEDS: 1100");
    // }
    // else if (pot_data <= 512 & pot_data > 256){
    //   DIO_SetPinState('d', 4, 'l');
    //   DIO_SetPinState('d', 5, 'l');
    //   DIO_SetPinState('d', 6, 'l');
    //   DIO_SetPinState('d', 7, 'l');
      
    //   DIO_SetPinState('d', 4, 'h');
    //   DIO_SetPinState('d', 5, 'h');
    //   DIO_SetPinState('d', 6, 'h');
    //   DIO_SetPinState('d', 7, 'l');
    //   Serial.println("LEDS: 1110");      
    // }
    // else if (pot_data <= 768 & pot_data > 512){
    //   DIO_SetPinState('d', 4, 'l');
    //   DIO_SetPinState('d', 5, 'l');
    //   DIO_SetPinState('d', 6, 'l');
    //   DIO_SetPinState('d', 7, 'l');
      
    //   DIO_SetPinState('d', 4, 'h');
    //   DIO_SetPinState('d', 5, 'h');
    //   DIO_SetPinState('d', 6, 'h');
    //   DIO_SetPinState('d', 7, 'h');
    //   Serial.println("LEDS: 1111");      
    // }
    
    _delay_ms(200); // delay for 200ms
  }
}

void init(){
  ADC_init(); // Initialize adc
  Serial.begin(9600);
  //set pins PD3 - PD7 as output
  DIO_SetPinDirection('d', 3, 'o');
  DIO_SetPinDirection('d', 7, 'o');
  DIO_SetPinDirection('d', 6, 'o');
  DIO_SetPinDirection('d', 5, 'o');
  DIO_SetPinDirection('d', 4, 'o');
}