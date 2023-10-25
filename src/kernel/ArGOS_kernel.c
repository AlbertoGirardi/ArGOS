//KERNEL OF ARGOS OPERATING SYSTEM



extern void main(){


    *(char*)0xb8002 = 'C';
    
    *(char*)0xb8000 = 'C';
     *(char*)0xb8004 = 'C';
    
    *(char*)0xb8008 = 'C';
     *(char*)0xb800A = 'C';
    
    *(char*)0xb800C = 'C';
     *(char*)0xb8006 = 'C';
    
    *(char*)0xb8000 = 'C';
   
    return;

}