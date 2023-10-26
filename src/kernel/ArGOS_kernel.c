//KERNEL OF ARGOS OPERATING SYSTEM

char  string[25]="wfeeewweeeewewefefw";

int function(int n){
    char  string[45]="dddddddddddddddddddddddddddddddddd";


    n = 0xb8070+n*2;
    for (char *p = (char *)0xb8070; p < (char *)n; p += 1)
    {
        *p = (char)'a';
        p++;
        *p = (char)0x3f;
    }

    return 0;

}





extern void main()
{

    *(char *)0xb8000 = 'C';

    for (char *p = (char *)0xb8002; p < (char *)0xb805F; p += 1)
    {
        *p = (char)'C';
        p++;
        *p = (char)0x1f;
    }

    function(160);


    while (1)
    {
        /* code */
    }
    

    return;
}