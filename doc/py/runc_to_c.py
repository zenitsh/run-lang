from ast_node import ASTNode

def c_h():
    res = '#include<stdio.h>\nvoid print(int arg){printf("%d",arg);}int input(){int n;scanf("%d",&n);return n;}size_t end();int main(int argn,char**argv){end();}'
    return res

c_dict = {}

def in_c_dict(fname):
    def in_c_dict_d(f):
        def f_i(*args):
            return f(*args)
        c_dict[fname]=f
        return f_i
    return in_c_dict_d

@in_c_dict('define')
def c_def(node : ASTNode)->str:
    res = ''
    if node.value['from'].type=='func':
        res = '{0} {1}({2}){{size_t res;' \
        '<@from>' \
        'return res;}}'.format('size_t', node.value['to'].value, ','.join(['size_t {}'.format(n.value) for n in node.value['from'].value['a'].value]))
        return res
    res = '{0} {1} '.format(node.value['from'].ltype, node.value['to'].value)
    if node.value['to'].value !='':
        res = res + '= {}'.format(node.value['from'].value)+';\n'
    res = res + ';'
    return res

@in_c_dict('func')
def c_func(node : ASTNode)->str:
    return '<@stmt>'

@in_c_dict('call')
def c_call(node : ASTNode)->str:
    res = '{}(<@from>)'.format(node.value['to'].value)
    return res

@in_c_dict('assign')
def c_assign(node : ASTNode)->str:
    res = '<@to> = <@from>'#.format(node.value['to'].value)
    return res

@in_c_dict('expr_op')
def c_expr_op(node : ASTNode)->str:
    op=node.value['op']
    if op=='=':
        op='=='
    res = '(<@a1>{}<@a2>)'.format(op)
    return res

@in_c_dict('if')
def c_if(node : ASTNode)->str:
    res = 'if(<@cond>){' \
        '<@yes>' \
        '}else{' \
        '<@no>' \
        '}'
    return res

@in_c_dict('expr_list')
def c_expr_list(node : ASTNode)->list:
    return ['<@{}>'.format(i) for i in range(len(node.value))]

@in_c_dict('name')
def c_red(node :ASTNode)->str:
    return '*({}*){}'.format(node.ltype,node.value)

@in_c_dict('args')
def c_args(node : ASTNode)->list:
    return ['<@{}>'.format(i) for i in range(len(node.value))]

@in_c_dict('undefined')
def c_undefined(node : ASTNode):
    return ''