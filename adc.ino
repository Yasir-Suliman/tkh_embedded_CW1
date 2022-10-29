#include "avr/io.h"
#include "stdio.h"

//Initializes ADC
void ADC_init(){
  ADCSRA = ADCSRA|(1<<ADEN); //
  ADCSRA = ADCSRA|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
  ADMUX = ADMUX&!(1<<REFS1);
  ADMUX = ADMUX|(1<<REFS0);
}

int ADC_read(int channel){
  ADMUX = ADMUX & ~(0x0f);
  ADMUX |= channel;  
  ADCSRA |= (1 << 6);

  while(ADCSRA & (1 << 6)){}
  
  return ADC;
}
