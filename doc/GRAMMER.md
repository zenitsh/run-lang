```
digit -> [0-9]*
float -> [0-9]*.[0-9]*
hex -> 0x[0-9]*
number -> digit | float | hex
name -> [A-Za-z_][A-Za-z0-9_]*
ref -> name (\.name)*
list -> [.+] | ref //if ref is a list
string -> \'.+\'
call -> expr_list -> ref //if ref is a function
expr -> (\(?expr [+-*/%] expr\)?) | number | name | call
expr_list -> expr(,expr)*
def -> def: expr_list as name
assign -> expr_list -> ref //if ref is not a function
if -> if expr: expr_list (else: expr_list)? end
while -> (do: expr_list) while expr: expr_list end
for -> for name in list: expr_list end
```