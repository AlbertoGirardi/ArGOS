#include "vga_driver.h"
#include "common.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};


static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;
int char_memory_size = 2;


int cursor_position = 0;


int vga_printchar( char c, uint16_t cursor_pos, uint16_t color_bkg ){


    uint16_t* abs_cursor_pos =(uint16_t*) VGA_MEMORY + cursor_pos;

	uint16_t char_data = (uint16_t) c | (uint16_t) color_bkg << 8;
    * abs_cursor_pos = (uint16_t) char_data;

    

    return 0;
}
 