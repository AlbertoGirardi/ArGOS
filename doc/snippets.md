
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



//testing print number functions

 screen_printIntDec(3);
    screen_write(nl);
    screen_printIntDec(-5);
    screen_write(nl);

    screen_printIntDec(-583887755);
    screen_write(nl);
    screen_printIntDec(35199997777);
    screen_write(nl);

    screen_printIntHex(-0x123aabbccdd);

    screen_write(nl);

    char n1[30];
    char* num = &n1[0];
    
    int_to_stringDEC(333, num);

    screen_write(num);


     
    screen_printIntDec(1000);
    
    screen_write(nl);
    screen_printIntDec(54321);

    screen_write(nl);
    screen_printIntDec(2011);

    screen_write(nl);
    screen_printIntDec(0);
    screen_write(nl);
    screen_printIntDec(1);

    screen_write(nl);
    screen_printIntDec(10101010);



    screen_write(nl);
    
  
    screen_write(nl);

    print_esp();

    screen_write(nl);

    test3();
    screen_write(nl);

    print_esp();
