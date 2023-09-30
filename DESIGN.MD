## MEMORY MODEL

tiny memory model:

     SS = DS = ES = 0

stack starts at 0x7c00 (and grows downwards as usal)


## CALLING CONVENTION: 

temp: si parameter register


### CALLEE CLEANUP

parameters pushed on the stack before calling 

- bp saved in the stack

- parameters accessed using [bp-offset]

- old bp popped

- return, dropping the parameters added (ret [num of bytes of parmeteres])

#### STACK EXAMPLE

    bottom
    ...                        bp+4+2*n_param
    parameter                  bp+4
    return address             bp+2
    old bp                     bp=0
    locals                     bp-2
    ...
    top


#### function snippet


    function:

        push bp
        mov bp, sp      ;calling convention: saving old bp and setting new one to start of function
        pusha           ;save all regs to stack

        ;;; DO STUFF

        jmp function_end
   



    function_end:
        popa            ;reload all saved regs from stack
        pop bp          ;restore bp to last saved value

        ret 2*arg_num   ;return popping also all args



