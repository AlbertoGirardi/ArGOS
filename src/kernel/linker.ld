OUTPUT_FORMAT("binary")
ENTRY(.entry)
phys = 0x00008c00;


SECTIONS{

    . = phys;

    .entry                                  : {__entry_start = .;       *(.entry)}
    .text                                  : {__text_start = .;       *(.text)}
    .data                                  : {__data_start = .;       *(.data)}
    .rodata                                  : {__rodata_start = .;       *(.rodata)}
    .bss                                  : {__bss_start = .;       *(.bss)}


__end = .;
}