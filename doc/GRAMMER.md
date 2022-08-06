```
digit -> [0-9]*
float -> [0-9]*.[0-9]*
hex -> 0x[0-9]*
number -> digit | float | hex
name -> [A-Za-z_][A-Za-z0-9_]*
ref -> name (\.name)*
list -> [.+] | ref //if ref is a list
string -> \'.+\' | ref //if ref is a string
call -> expr_list -> ref //if ref is a function
expr_op -> (\(?expr [+-*/%] expr\)?)
expr -> expr_op | number | name | call | assign | func | string | list
expr_list -> expr(,expr)*
func -> \{ name(,name)* | expr_list \}
assign -> expr_list -> ref //if ref is not a function
if -> ?expr:expr_list:expr_list$
while -> %expr:expr_list:expr_list$
for -> %(name:list):expr_list$
switch -> %(expr):number:expr_list:number:expr_list...$
```