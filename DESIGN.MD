## MEMORY MODEL

tiny memory model: SS = DS = ES = 0

stack starts at 0x7c00 (and grows downwards as usal)


## CALLING CONVENTION: 

temp: si parameter register


### CALLEE CLEANUP

parameters pushed on the stack before calling 

bp saved in the stack

parameters accessed using [bp-offset]



old bp popped

return, dropping the parameters added (ret [num of bytes of parmeteres])

STACK EXAMPLE

bottom

parameter\                  bp+4
return address\             bp+2
old bp\                     bp+0
locals\
...


