# REAL MODE 16 BITS

## MEMORY MODEL

tiny memory model:

     SS = DS = ES = 0

stack starts at 0x7c00 (and grows downwards as usal)


## CALLING CONVENTION: 

temp: si parameter register


### CALLEE CLEANUP

0. parameters pushed on the stack before calling(from LEFT to right) 

1. bp saved in the stack

2. parameters accessed using [bp-offset]

3. old bp popped

4. return, dropping the parameters added (ret [num of bytes of parmeteres])

#### STACK EXAMPLE

    bottom
    ...                            bp+4+2*n_param

    parameter 1                    bp+8
    parameter 2                    bp+6
    parameter 3                    bp+4
    return address                 bp+2
    old bp                         bp=0
    locals                         bp-2
    ...
    top


#### function snippet

function(arg1, arg2, arg3)

caller:

    push arg1
    push arg2
    push arg3
    call function


callee:

    function:

        push bp
        mov bp, sp      ;calling convention: saving old bp and setting new one to start of function
        pusha           ;save all regs to stack

        ;;; DO STUFF

        jmp function_end
   



    function_end:
        popa            ;reload all saved regs from stack
        pop bp          ;restore bp to last saved value

        ret 3*arg_num   ;return popping also all args





to graph log

```
git log --graph --abbrev-commit --decorate --format=format:'%C(bold blue)%h%C(reset) - %C(bold green)(%ar)%C(reset) %C(white)%s%C(reset) %C(dim white)- %an%C(reset)%C(auto)%d%C(reset)' --all
lg2 = log --graph --abbrev-commit --decorate --format=format:'%C(bold blue)%h%C(reset) - %C(bold cyan)%aD%C(reset) %C(bold green)(%ar)%C(reset)%C(auto)%d%C(reset)%n''          %C(white)%s%C(reset) %C(dim white)- %an%C(reset)
```




