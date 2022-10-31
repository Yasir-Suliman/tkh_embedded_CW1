#include <avr/io.h>

void set_baudrate(int baudrate){
  int ubrr = (F_CPU/16*baudrate) - 1;
  UBRR0L = ubrr;
  UBRR0H = (ubrr >> 8);
}

void init_uart(){
  set_baudrate(9600);
  UCSR0B = UCSR0B |(1 << 3) |(1 << 4);
  UCSR0C = UCSR0C |(1 << 3);
  UCSR0C = UCSR0C |(1 << 1) |(1 << 2);
  UCSR0B = UCSR0B |(1 << 2);
}

//send a character
void send_char_uart(char data){
  int empty = (UCSR0A & (1<<5));// returns 1 when empty and 0 when not empty
  while(!empty){
    empty = (UCSR0A & (1<<5));
  }
  UDR0 = data;
}

//send a string
void send_string_uart(char data[]){
  int i;
  //loops through string and sends each character
  for(i=0; data[i];i++){
    send_char_uart(data[i]);
  }
}

//recieve data
unsigned char read_data_uart(){
  //checks if data is recievd
    while(!(UCSR0A&(1<<RXC0)));
    return UDR0;
}