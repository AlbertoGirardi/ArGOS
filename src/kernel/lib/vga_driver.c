#include "vga_driver.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>



static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;        //vga hardware mapped-memory
int char_memory_size = 2;


int cursor_position = 0;


void vga_printchar_r(unsigned char c, uint16_t cursor_pos, uint16_t color_char  ,uint16_t color_bkg ){

	/*
	Prints a character to the screen, at a given position, with the given colors in hex (so the _r that means raw)
	*/


    uint16_t* abs_cursor_pos =(uint16_t*) VGA_MEMORY + cursor_pos;					//calculating memory position to place charcacter


	uint8_t color_data =  (uint8_t) color_char | (uint8_t) color_bkg << 4;			//color data 
	uint16_t char_data = (uint16_t) c | (uint16_t) color_data << 8;					//calculating data to place into memory

    * abs_cursor_pos = (uint16_t) char_data;										//placing data in  the memory

    

    return ;
}



void vga_printcharTEXT(unsigned char c, uint16_t cursor_pos, enum vga_color color_char,  enum vga_color color_bkg  ){

	/*
	wrapper of vga_printchar_r to use enum colors, specific to vga text mode
	*/

	vga_printchar_r( c, cursor_pos, (uint16_t) color_char, (uint16_t) color_bkg );
	return;

}


void vga_printchar(unsigned char c, uint16_t cursor_pos, enum vga_color color_char,  enum vga_color color_bkg  ){

/* wrapper that abstracts the vga mode*/
	vga_printcharTEXT(c, cursor_pos, color_char, color_bkg);
	return;

}


void vga_move_cursor(uint16_t pos){


	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}