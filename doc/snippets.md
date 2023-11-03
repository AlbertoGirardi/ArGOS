
    screen_write("\t\tabcde\r\n");
    screen_write("a\t\tabcde\r\n");
    screen_write("ab\t\tabcde\r\n");
    screen_write("abc\t\tabcde\r\n");
    screen_write("abcd\tabcde\r\n");
    screen_write("abcde\tabcde\r\n");


//tests tabs




    long long a = 100000000000000; 
    long long q ;

    q = a/1;

    if ( q ==a )
    {
        screen_write("\n\rok1");
    }
    

//testing long division



    if (css == 0x7c00)
    {
        screen_write("stack is ok");
    }



//testing memcmp


char t1[]= "wwwwww";
char t2[]= "wwww33";


    char *testmem = &t1[0];
    char *testmem2 = &t2[0];
screen_printIntDec( memcmp(testmem, testmem2, 6));