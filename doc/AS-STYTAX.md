``` 
setmi <memory> <r>
getmi <memory> <r>
setmf <memory> <f>
getmf <memory> <f>

setioi <io> <r>
getioi <io> <r>
setiof <io> <f>
getiof <io> <f>

setiim <imm> <r>
setfim <imm> <f>

seti <r1> <r2> ; r1 -> r2
setf <f1> <f2>

setif <f> <r>
setfi <r> <f>
addsi <r>
addsim <imm>
subsum <imm>
getsi <r>
getsf <f>
setsi <r>
setsf <f>
swapi <r1> <r2>
swapf <r1> <r2>

addi <r1> <r2> <r3> ; r1 + r2 -> r3
subi <r1> <r2> <r3>
muli <r1> <r2> <r3> ; >32 lost
divi <r1> <r2> <r3>
remi <r1> <r2> <r3>
addf <f1> <f2> <f3>
subf <f1> <f2> <f3>
mulf <f1> <f2> <f3>
#remf <f1> <f2> <f3> ; using loop (not recommand)
divf ...

setv <f1:vec> <f2:vec>
setx <f1:mat> <f2:mat>

mulfi <f1> <r> <f2>
divfi <f1> <r> <f2>
addv <f1:vec> <f2:vec> <f3:vec>
subv <f1:vec> <f2:vec> <f3:vec>
dotv <f1:vec> <f2:vec> <f3:vec>
crsv <f1:vec> <f2:vec> <f3>
mulx <f1:mat> <f2:mat> <f3:vec>
mulxv <f1:mat> <f2:vec> <f3:vec>

andi <r1> <r2> <r3>
ori <r1> <r2> <r3>
xori <r1> <r2> <r3>
li <r1> <r2> <r3>
ri <r1> <r2> <r3>
andiim <r1> <imm> <r3>
oriim <r1> <imm> <r3>
xoriim <r1> <imm> <r3>
liim <r1> <imm> <r3>
riim <r1> <imm> <r3>

jumpi <r>
jumpim <imm>
jzii <r1> <r2>
jaii <r1> <r2>
jziim <r> <imm>
jaiim <r> <imm>
xi <r>
xim <imm> ; ATTENTION: P, B, C are all changed;
; P, B, C are locked: They cannot be changed together execpt xi/xim & retn
retn
sysim <r> <imm>
```