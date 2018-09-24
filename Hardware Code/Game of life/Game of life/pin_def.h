/*
 * IncFile1.h
 *
 * Created: 12-Sep-18 6:27:14 PM
 *  Author: Om
 */ 

#include<avr/io.h>

#ifndef PIN_DEF_H_
#define PIN_DEF_H_

#define CLOCK_PORT PORTB
#define LATCH_PORT PORTB
#define DATA_PORT  PORTB

#define CLOCK_PIN PORTB2
#define LATCH_PIN PORTB3
#define DATA_PIN PORTB4

#define GROUND_PORT PORTD
#define y1 PORTD2
#define y2 PORTD3
#define y3 PORTD4
#define y4 PORTD5
#define y5 PORTD6
#define y6 PORTD7
//clock pin PB2 Arduino Pin(10)
//latch pin  PB3 Arduino Pin(11)
//data pin  PB4 Arduino Pin(12)
//row(1-6) pin (PD2-PD7) Arduino Pin(2-7)

#endif /* INCFILE1_H_ */

