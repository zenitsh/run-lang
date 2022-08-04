
#语法

##例子
```
def:
    in(x)
    'hello,{}', x -> format 
        -> print $
as foo
def: $ -> foo as foo1
$ -> foo # =foo
```
这是一个没有数据类型的编程语言,默认所有全是32位整数.

局部变量作为结构体的一种表现方式是本语言的一种特色.

四个局部变量声明符:in,out,both,neither/temp

'->':移动操作符,作用为移动所有权到另外一个地方

'&>':引用操作符,复制引用

'=>':复制操作符,复制所有

无返回值的函数后面和无参数的函数前面可用$注明,不加也可以.

这里foo类型为constant(function pointer)

```
def:
    out(x=0)
    run
as foo
def:
    foo -> temp(f) #f为实例化的foo对象,但是在栈上,通过run不释放内存返回
    f.x -> print
    1 -> f.x
    f.x -> print
    #释放空间
as test
test
```

孤立函数(区别于栈上函数):
```
foo -> alloc(f)
int -> alloc(i)
```
父函数执行完后不会释放局部变量空间