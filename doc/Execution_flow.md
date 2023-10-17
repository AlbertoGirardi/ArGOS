# EXECUTION FLOW DURING BOOTING AND MEMORY


## 16 BITS Real Mode
BIOS loads stage1

stage1 loads stage2, kernel loader and kernel into the first meg, after the first sector

## 32 BITS Protected Mode

stage2: 
* sets up GDT
* jumps to kenrel loader

kenel loader: loads kernel and jumps to it