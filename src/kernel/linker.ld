OUTPUT_FORMAT("binary")
ENTRY(.entry)


/*adapted from osdec meaty skeleton*/

ENTRY(_start)

/* Tell where the various sections of the object files will be put in the final
   kernel image. */
SECTIONS
{
	. = 0x9000;

	.text BLOCK(4K) : ALIGN(4K)
	{
		
		*(.text)
	}

	/* Read-only data. */
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}

	/* Read-write data (initialized) */
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}

	/* Read-write data (uninitialized) and stack */
	.bss BLOCK(4K) : ALIGN(4K)
	{	
		__bss_start = .;
		*(COMMON)
		*(.bss)

		__bss_end = .;
	}

	/* The compiler may produce other sections, put them in the proper place in
	   in this file, if you'd like to include them in the final kernel. */
}
