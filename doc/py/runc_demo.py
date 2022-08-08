import sys
from ast_node import ASTNode

def __asm_pushi(n : int):
    res = '''getsi 31
    setmii {0} 31
    addsim 4'''.format(n)
    return res

def __asm_popi(n : int):
    res = '''subsim 4
    getsi 31
    getmii {0} 31
    '''.format(n)
    return res

def __asm_if(n : int, L : str):
    res = '''<cond>
    jaii {0} {1}
    <yes>
    {1}:
    '''.format(n, L)
    return res

def __asm_if_else(n : int, L1 : str, L2 : str):
    res = '''<cond>
    jaii {0} {1}
    <yes>
    jumpim {2}
    {1}:
    <no>
    {2}:
    '''.format(n, L1, L2)
    return res

def __asm_while(n : int, L1 : str, L2 : str):
    res = '''{1}:
    <cond>
    jzii {0} {2}
    <loop>
    jumpim {2}
    {2}:'''
    return res

def __asm_do_while(n : int, L1 : str, L2 : str):
    res = '''{1}:
    <first>
    <cond>
    jzii {0} {2}
    <second>
    jumpim {2}
    {2}:'''
    return res

def parse_int(s : str):
    return ASTNode('int', int(s))

def parse_float(s : str):
    return ASTNode('float', float(s))

def parse_number(s : str):
    if '.' in s:
        return parse_float(s)
    return parse_int(s)

def parse_string(s : str):
    i=1
    while i<len(s) and s[i]!='\'':
        i=i+1
    return ASTNode('string', s[:i])

def parse_name(s : str):
    i=0
    while i<len(s) and (s[i].isalpha() or s[i].isdigit() or s[i]=='_'):
        i=i+1
    res = ASTNode('name', s[:i])
    if i<len(s) and s[i]==':':
        res.ltype = s[i+1:]
    return res

def parse_ref(s : str):
    return parse_name(s)#ASTNode('ref', [parse_name(i) for i in s.split('.')])

def parse_expr_op(s : str):
    lv = 0
    stack=[]
    for i in reversed(range(1,len(s)-1)):
        if (s[i]=='\'' and (len(stack)==0 or stack[-1]=='\'')) or s[i]==')' or s[i]=='}' or s[i]=='$':
            stack.append(s[i])
            lv=lv+1
        elif (s[i]=='\'' and stack[-1]=='\'') or s[i]=='(' or s[i]=='{' or s[i]=='?' or s[i]=='%':
            lv=lv-1
            stack.pop()
        if lv==0 and s[i:i+2]=='->':
            return parse_assign(s[1:-1])
    st = 1
    stt = 0
    a1 = None
    op = '.'
    a2 = None
    t='+-*/%|&<>='
    for i in range(1,len(s)-1):
        if (s[i]=='\'' and (len(stack)==0 or stack[-1]=='\'')) or s[i]=='(' or s[i]=='{' or s[i]=='?' or s[i]=='%':
            stack.append(s[i])
            lv=lv+1
        elif (s[i]=='\'' and stack[-1]=='\'') or s[i]==')' or s[i]=='}' or s[i]=='$':
            lv=lv-1
            stack.pop()
        if stt == 2:
            if not s[i] in t:
                op = s[st:i]
                stt = 3
                st = i
        if lv==0:
            if stt == 0:
                if s[i] == ' ':
                    a1 = parse_expr(s[st:i].strip())
                    stt = 1
                elif s[i] in t:
                    a1 = parse_expr(s[st:i].strip())
                    st = i
                    stt = 2
            elif stt == 1:
                if s[i] != ' ':
                    st = i
                    stt = 2
    if stt==1:
        return parse_expr(s[1:-1].strip())
    a2 = parse_expr(s[st:-1].strip())
    return ASTNode('expr_op', {'op':op,'a1':a1,'a2':a2})

def parse_list(s : str):
    res = []
    for i in s.split(','):
        res.append(parse_ref(i))
    return ASTNode('list', res)

def parse_assign(s : str):
    dv = s.rindex('->')
    lvalue = parse_expr(s[:dv].strip())
    rvalue = parse_ref(s[dv+2:].strip())
    rvalue.rtype = lvalue.ltype
    rv=False
    if lvalue.type == 'func':
        rv = True
    return ASTNode('assign' ,{'from':lvalue,'to':rvalue,'fun':rv})

def undefined():
    return ASTNode('undefined', 0)

def parse_expr(s : str):
    lv=0
    stack=[]
    b=False
    if len(s)==0:
        return undefined()
    for i in reversed(range(len(s))):
        if (s[i]=='\'' and (len(stack)==0 or stack[-1]=='\'')) or s[i]==')' or s[i]=='}' or s[i]=='$':
            stack.append(s[i])
            lv=lv+1
        elif (s[i]=='\'' and stack[-1]=='\'') or s[i]=='(' or s[i]=='{' or s[i]=='?' or s[i]=='%':
            lv=lv-1
            stack.pop()
        if lv==0 and s[i:i+2]=='->':
            b=True
            return parse_assign(s)
    if s[0] == '{':
        return parse_func(s)
    elif s[0] == '(':
        return parse_expr_op(s)
    elif s[0] == '\'':
        return parse_string(s)
    elif s[0] == '?':
        return parse_if(s)
    elif s[0] == '%':
        return parse_while(s)
    elif s[0] in '0123456789':
        return parse_number(s)
    else:
        return parse_ref(s)
    return undefined()

def parse_expr_list(s : str):
    lv = 0
    stack = []
    tok = []
    ls = []
    for i in range(0,len(s)):
        if (s[i]=='\'' and (len(stack)==0 or stack[-1]=='\'')) or s[i]=='(' or s[i]=='{' or s[i]=='?' or s[i]=='%':
            stack.append(s[i])
            lv=lv+1
        elif (s[i]=='\'' and stack[-1]=='\'') or s[i]==')' or s[i]=='}' or s[i]=='$':
            lv=lv-1
            stack.pop()
        if lv==0 and s[i]==',':
            tok.append(i)
    lst = 0
    if len(tok)>0:
        ls.append(s[:tok[0]])
        lst = tok[-1]+1
    for i in range(1, len(tok)):
        ls.append(s[tok[i-1]+1:tok[i]].strip())
    ss=s[lst:len(s)].strip()
    if(len(ss)>0):
        ls.append(ss)
    for i in range(len(ls)):
        ls[i] = parse_expr(ls[i])
    return ASTNode('expr_list', ls)

def parse_func(s : str):
    lv=1
    st=1
    args=ASTNode('args', [])
    for i in range(st, len(s)):
        if s[i]==',' or s[i]=='|':
            if(len(s[st:i].strip())>0):
                args.value.append(parse_name(s[st:i].strip()))
            st=i+1
            if s[i]=='|':
                break
    return ASTNode('func', {'a':args,'stmt':parse_expr_list(s[st:-1])})

def parse_if(s : str):
    lv = 0
    stack = []
    ls = []
    cond = None
    yes = None
    no = None
    st=0
    for i in range(1,len(s)-1):
        if (s[i]=='\'' and (len(stack)==0 or stack[-1]=='\'')) or s[i]=='(' or s[i]=='{' or s[i]=='?' or s[i]=='%':
            stack.append(s[i])
            lv=lv+1
        elif (s[i]=='\'' and stack[-1]=='\'') or s[i]==')' or s[i]=='}' or s[i]=='$':
            lv=lv-1
            stack.pop()
        if lv==0:
            if s[i]==':':
                if cond==None:
                    cond=parse_expr(s[1:i])
                    st=i+1
                else:
                    yes=parse_expr_list(s[st:i])
                    st=i+1
    if yes==None:
        yes=parse_expr_list(s[st:-1])
    else:
        no=parse_expr_list(s[st:-1])                
    return ASTNode('if', {'cond':cond,'yes':yes,'no':no})

def parse_while(s : str):
    lv = 0
    stack = []
    ls = []
    cond = None
    first = None
    second = None
    st=0
    for i in range(1,len(s)-1):
        if (s[i]=='\'' and (len(stack)==0 or stack[-1]=='\'')) or s[i]=='(' or s[i]=='{' or s[i]=='?' or s[i]=='%':
            stack.append(s[i])
            lv=lv+1
        elif (s[i]=='\'' and stack[-1]=='\'') or s[i]==')' or s[i]=='}' or s[i]=='$':
            lv=lv-1
            stack.pop()
        if lv==0:
            if s[i]==':':
                if cond==None:
                    cond=parse_expr(s[1:i])
                    st=i+1
                else:
                    first=parse_expr_list(s[st:i])
                    st=i+1
    if first==None:
        first=parse_expr_list(s[st:-1])
    else:
        second=parse_expr_list(s[st:-1])                
    return ASTNode('while', {'cond':cond,'first':first,'second':second})

def set_in_name_stack(name_stack,k,l,r):
    name_stack[-1][k]=(l,r)

def find_in_name_stack(name_stack,k):
    for i in reversed(range(len(name_stack))):
        if k in name_stack[i].keys():
            return name_stack[i][k]
    return "null", "null"
        
def analyse(node : ASTNode):
    name_stack = [{'print':['null','func'],'input':['string','func'],'res':['int','int']}]
    saved_struct = {}
    if True:
        stack = [[node,0,[]]]
        while len(stack)>0:
            b=False
            tab="\t"*(len(stack)-1)
            parent = stack[-1][0]
            if(stack[-1][1]==0):
                if(parent.type=='expr_list'):
                    name_stack.append({})
                    if len(stack)>1:
                        for ps in stack[-2][2]:
                            set_in_name_stack(name_stack, ps.value, ps.ltype, 'null')
                elif(parent.type=='func'):
                    stack[-1][2]=[]
                    for arg in parent.value['a'].value:
                        stack[-1][2].append(arg)
                elif(parent.type=='assign') and parent.value['fun']:
                    if find_in_name_stack(name_stack, parent.value['to'].value) == ('null', 'null'):
                        parent.type='define'
                        set_in_name_stack(name_stack, parent.value['to'].value, 'null', 'func')
            if parent.type in ['expr_list','list']:
                i=stack[-1][1]
                if i<len(parent.value):
                    stack[-1][1]=i+1
                    child : ASTNode = parent.value[i]
                    stack.append([child,0,[]])
                else:
                    b=True
                    stack.pop()
                    if(parent.type=='expr_list'):
                        name_stack.pop()
            elif parent.type in ['func','assign','if','while','expr_op','define','call']:
                i=stack[-1][1]
                if i<len(parent.value):
                    stack[-1][1]=i+1
                    if type(list(parent.value.values())[i])==ASTNode:
                        stack.append([list(parent.value.values())[i],0,[]])
                else:
                    b=True
                    stack.pop()
            else:
                b=True
                stack.pop()
            if(b):
                if(parent.type=='expr_list'):
                    if(len(parent.value)>0):
                        parent.ltype = parent.value[-1].ltype
                elif(parent.type=='if'):
                    parent.ltype = parent.value['yes'].ltype
                elif(parent.type=='while'):
                    parent.ltype = parent.value['second'].ltype
                elif(parent.type=='int'):
                    parent.ltype, parent.rtype = 'int', 'int'
                elif(parent.type=='float'):
                    parent.ltype, parent.rtype = 'float', 'float'
                elif(parent.type=='string'):
                    parent.ltype, parent.rtype = 'string', 'string'
                elif(parent.type=='list'):
                    parent.ltype, parent.rtype = 'list', 'list'
                elif(parent.type=='func'):
                    parent.ltype, parent.rtype = parent.value['stmt'].ltype, 'func' #int for temp
                elif(parent.type=='name'):
                    parent.ltype, parent.rtype = find_in_name_stack(name_stack, parent.value)
                elif(parent.type=='expr_op'):
                    if parent.value['a1'].ltype == 'string' or parent.value['a2'].ltype == 'string':
                        parent.ltype = 'string'
                    elif parent.value['a1'].ltype == 'int' or parent.value['a2'].ltype == 'int':
                        parent.ltype = 'int'
                    elif parent.value['a1'].ltype == 'float' or parent.value['a2'].ltype == 'float':
                        parent.ltype = 'float'
                elif(parent.type=='define'):
                        set_in_name_stack(name_stack, parent.value['to'].value, parent.value['from'].ltype, 'func')                     
                elif(parent.type=='assign'):
                    if parent.value['to'].rtype == 'func':
                        parent.type = 'call'
                        parent.ltype = parent.value['to'].ltype
                        if parent.value['from'].type!='expr_list':
                            old_from = parent.value['from']
                            parent.value['from']=ASTNode('expr_list', [parent.value['from']])
                            parent.value['from'].ltype, parent.value['from'].rtype = old_from.ltype, old_from.rtype
                    elif find_in_name_stack(name_stack, parent.value['to'].value) == ('null', 'null'):
                        parent.type = 'define'
                        set_in_name_stack(name_stack, parent.value['to'].value, parent.value['from'].ltype, parent.value['from'].rtype)

import runc_to_c

def generate_c(node : ASTNode):
    stack = [[node,0]]
    l_stack = [['stmt']]
    compiled_stack = [{}]
    while len(stack)>0:
        b = False
        tab="\t"*(len(stack)-1)
        parent = stack[-1][0]
        if(stack[-1][1]==0):
            compiled_stack.append({})
            l_stack.append([])
        if parent.type in ['expr_list','list','args']:
            i=stack[-1][1]
            if i<len(parent.value):
                stack[-1][1]=i+1
                child : ASTNode = parent.value[i]
                stack.append([child,0])
                l_stack[-1].append(str(i))
            else:
                b = True
                stack.pop()
        elif parent.type in ['func','assign','if','while','expr_op','define','call']:
            i=stack[-1][1]
            if i<len(parent.value):
                stack[-1][1]=i+1
                if type(list(parent.value.values())[i])==ASTNode:
                    stack.append([list(parent.value.values())[i],0])
                    l_stack[-1].append(list(parent.value.keys())[i])
            else:
                b = True
                stack.pop()
        else:
            b = True
            stack.pop()
        if b:
            raw=''
            if parent.type in runc_to_c.c_dict.keys():
                func = runc_to_c.c_dict[parent.type]
                raw:str=func(parent)
                if type(raw)!=str:
                    if l_stack[-2][-1] in ['stmt','yes','no','first','second']:
                        raw=''.join(['{};'.format(i) for i in raw])
                    else:
                        raw=','.join(raw)
                for key in compiled_stack[-1].keys():
                    raw=raw.replace("<@{}>".format(key), str(compiled_stack[-1][key]))
            else:
                raw = str(parent.value)
            compiled_stack[-2][l_stack[-2][-1]]=raw
            compiled_stack.pop()
            l_stack.pop()
    return runc_to_c.c_h()+compiled_stack[0]['stmt']
            

if __name__ == '__main__':
    if len(sys.argv)>2:
        if sys.argv[1][0]=='-':
            f=open(sys.argv[2])
            source=''.join([line.strip() for line in f.readlines()])
            f.close()
            node = parse_expr_list(source)
            analyse(node)
            if 'p' in sys.argv[1]:
                print(node)
            if 'c' in sys.argv[1]:
                print(generate_c(node))
    elif len(sys.argv)==2 and sys.argv[1]=='-e':
        #s="{|\'Hello, world!\\n\' -> print} -> foo,foo"
        #node = parse_expr_list(s)
        #print(node)
        #analyse(node)
        s="{x|?((x=1)|(x=2)):1->return:(((x-1)->F)+((x-2)->F))->return$}->F,->input->F->print"
        node = parse_expr_list(s)
        analyse(node)
        print(node)
        res = generate_c(node)
        print(res)
        #s="0->i,%(i < 100)::(i * i)->print$"
        #node = parse_expr_list(s)
        #print(node)
        #analyse(node)
