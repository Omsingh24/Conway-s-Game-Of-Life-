/*
 * Shift registe.c
 *
 * Created: 12-Sep-18 5:17:06 PM
 * Author : Om
 */ 

#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include "pin_def.h"
#include "macros.h"
#include "shiftregister.h"
#include "led_panel.h"
#include <stdlib.h>
#define rule ^
//clock pin PB2 Arduino Pin(10)
//latch pin  PB3 Arduino Pin(11)
//data pin  PB4 Arduino Pin(12)
//row(1-6) pin (PD2-PD7) Arduino Pin(2-7)


int main(void)
{
	DDRB |= ((1<<DDB2) | (1<<DDB3) | (1<<DDB4));
	DDRD |= ((1<<DDD7) | (1<<DDD2) | (1<<DDD3) |(1<<DDD4) |(1<<DDD5) |(1<<DDD6));
	
	
	uint8_t new_gen[8][10]; //all side single cell padding to aoid out of bound array error
	uint8_t row_int; //variable to save int value for shift register
	uint8_t this_gen[8][10]={  
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 1, 0, 0, 0, 1, 1, 0},
			{0, 0, 1, 1, 0, 1, 1, 0, 0, 0},
			{0, 1, 0, 1, 0, 0, 1, 0, 1, 0},
			{0, 0, 0, 1, 0, 0, 0, 1, 1, 0},
			{0, 0, 1, 1, 0, 1, 0, 1, 1, 0},
			{0, 0, 1, 0, 1, 1, 0, 1, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
											};
	uint8_t m; //2^2 counter
	uint8_t flag=0; //flag to check if current generation is equal to previous generation
void game_of_life()
{
	uint8_t up,down,left,right,dul,dur,ddl,ddr,t; //possible neighbours of a cell
	for(uint8_t x=1;x<7;x++) //loop for each row of grid
	{
		for (uint8_t y=1;y<9;y++) //loop for each column of grid
		{
			up=this_gen[x][y-1];  //up neighbour
			down=this_gen[x][y+1]; //down neighbour
			left=this_gen[x-1][y]; //left neighbour
			right=this_gen[x+1][y]; //right neighbour
			dur=this_gen[x+1][y-1]; //diagonal upper right neighbour
			dul=this_gen[x-1][y-1]; //diagonal upper left neighbour
			ddr=this_gen[x+1][y+1]; //diagonal down right neighbour
			ddl=this_gen[x-1][y+1]; //diagonal down left neighbour
			t=up+down+left+right+dul+dur+ddr+ddl; // sum of states of all neighbour
			 if (t<2)  //if neighbours are less tha 2 cell dies
			 {
				  new_gen[x][y]=0;
			 }
			 else if (t>3) //if neighbour is greater than 3 celll dies
			 {
				new_gen[x][y]=0 ;
			 }
			 else if ((t==3) && (this_gen[x][y]==0)) //if cell is equal to 3 and cell is dead ,cell gets alive
			 {
				 new_gen[x][y]=1;
			 }
			 
			 else if (((t==2) || (t==3)) && this_gen[x][y]==1) //if neighbours is 2 or 3 cell stays the same 
			 {
				 new_gen[x][y]=this_gen[x][y];
			 }		
		}
		}


	
}

    while (1) 
    {	
		
		for(uint16_t t=0;t<50;t++) //loop to control the timing between generations
		{
			for(uint8_t i=1;i<7;i++) //loop for each row of grid
			{	
				m=128;
				row_int=0;
				for(uint8_t j=1;j<9;j++) //loop for each column of grid
				{
					row_int=row_int+(this_gen[i][j]*m); //converting row of array into integer.
					m=m/2;
				}
			
				grid_panel(row_int,i); //sending bits to shift register
				latch_pulse(); //latching the shift register to update values
				_delay_ms(1); 
			}
		}
		
	game_of_life(this_gen,new_gen);
	flag=0; //flag=0 if current frame is not equal to preious frame
	
	for(uint8_t i=1;i<7;i++)// loop for each row
	{
		for (uint8_t j=1;j<9;j++) // loop for each column
		{
			
			if(this_gen[i][j]==new_gen[i][j]) //check if each element of current grid is equal to previous grid
			{
				flag=flag+1;  //if current grid==previous grid increment flag by 1
			}
				this_gen[i][j]=new_gen[i][j]; //current gen act as new gen for next gen.
				
			if(flag==48) //if all cells are same in current and previous grid flag==48
			{
				for(uint8_t i=1;i<7;i++)
				{
					for(uint8_t j=1;j<9;j++)
					{
						this_gen[i][j]=(rand()%2); //generate a random current grid.
					}
				}
				
			}
			
			
			
		}
		
	}
	}
}

