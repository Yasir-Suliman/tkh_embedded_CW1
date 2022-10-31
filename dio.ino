#include <stdio.h>
#include <util/delay.h>

void DIO_init(){
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

// set Pin to INPUT or OUTput
void DIO_SetPinDirection(unsigned char port, int pin, unsigned char direction){ //
  if (port == 'b' & pin <= 7 & pin >= 0){ // pin must be from 0-7
    if(direction == 'o'){
      DDRB = DDRB|(1<<pin); //bit set to 1 for output
    }else if(direction == 'i'){
      DDRB = DDRB&!(1<<pin); // bit cleared to 0 for input
    }
  }
  if (port == 'c' & pin <= 7 & pin >= 0){ // pin must be from 0-7
    if(direction == 'o'){
      DDRC = DDRC|(1<<pin); // bit set to 1 for output
    }else if(direction == 'i'){
      DDRC = DDRC&!(1<<pin); // bit cleared to 0 for input
    }
  }
  if (port == 'd' & pin <= 7 & pin >= 0){ // pin must be from 0-7
    if(direction == 'o'){
      DDRD = DDRD|(1<<pin); //bit set to 1 for output
    }else if(direction == 'i'){
      DDRD = DDRD&!(1<<pin); //bit cleared to 0 for input
    }
  }
}

// if pin is output it will set it to either HIGH or LOW
// if pin is input it will activate internal pull up resistor
void DIO_SetPinState(unsigned char port, int pin, unsigned char state){
  if (port == 'b' & pin <= 7 & pin >= 0){ // pin must be from 0-7
    if(state == 'h'){
      PORTB = PORTB|(1<<pin); //pin is set to 1 for high
    }else if(state == 'l'){
      PORTB &= ~(1<<pin); //pin is cleared to 0 for low
    }
  }
  if (port == 'd' & pin <= 7 & pin >= 0){ // pin must be from 0-7
    if(state == 'h'){
      PORTD = PORTD|(1<<pin); //pin is set to 1 for high
    }else if(state == 'l'){
      PORTD &= ~(1<<pin); //pin is cleared to 0 for low
    }
  }
  if (port == 'c' & pin <= 7 & pin >= 0){ // pin must be from 0-7
    if(state == 'h'){
      PORTC = PORTC|(1<<pin); //pin is set to 1 for high
    }else if(state == 'l'){
      PORTC &= ~(1<<pin); //pin is cleared to 0 for low
    }
  }
}
  