import sys

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

class ASTNode:
    def __init__(self, type : str, value):
        self.type = type
        self.rtype = ''
        self.value = value
    def __str__(self):
        v = self.value
        if type(self.value) == dict:
            v='{'
            r=[]
            for i in self.value.keys():
                r.append("{}:{}".format(i, self.value[i]))
            v=v+', '.join(r)+'}'
        if type(self.value) == list:
            r=[]
            for i in self.value:
                r.append(str(i))
            v='['+', '.join(r)+']'
        return "<{}:{}>".format(self.type, v)

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
    return ASTNode('name', s[:i])

def parse_ref(s : str):
    return ASTNode('ref', s.split('.'))

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
        if lv==0:
            if stt == 0:
                if s[i] == ' ':
                    a1 = parse_expr(s[st:i])
                    stt = 1
            elif stt == 1:
                if s[i] != ' ':
                    st = i
                    stt = 2
            elif stt == 2:
                if s[i] == ' ':
                    op = s[st:i]
                    stt = 3
        if stt == 3:
            if s[i] != ' ':
                st = i
                break
    if stt==1 or (not op in t):
        return parse_expr(s[1:-1])
    a2 = parse_expr(s[st:-1])
    return ASTNode('expr_op', {'op':op,'a1':a1,'a2':a2})

def parse_list(s : str):
    res = []
    for i in s.split(','):
        res.append(parse_ref(i))
    return ASTNode('list', res)

def parse_assign(s : str):
    dv = s.rindex('->')
    return ASTNode('assign' ,{'from':parse_expr(s[:dv].strip()),'to':parse_ref(s[dv+2:].strip())})

def undefined():
    return ASTNode('undefined', 0)

def parse_expr(s : str):
    print(s)
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
    ls.append(s[lst:len(s)].strip())
    for i in range(len(ls)):
        ls[i] = parse_expr(ls[i])
    return ASTNode('expr_list', ls)

def parse_func(s : str):
    lv=1
    st=1
    args=ASTNode('args', [])
    for i in range(st, len(s)):
        if s[i]==',' or s[i]=='|':
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


def analyse(node : ASTNode):
    name_stack = []
    stack = [[node,0,[]]]
    while len(stack)>0:
        parent = stack[-1][0]
        if(stack[-1][1]==0):
            print("\t"*(len(stack)-1)+parent.type)
            if(parent.type=='expr_list'):
                name_stack.append({})
        if parent.type in ['expr_list','list']:
            i=stack[-1][1]
            if i<len(parent.value):
                stack[-1][1]=i+1
                child : ASTNode = parent.value[i]
                stack.append([child,0])
            else:
                stack.pop()
                if(parent.type=='expr_list'):
                    name_stack.pop()
        elif parent.type in ['func','assign','if','while','expr_op']:
            i=stack[-1][1]
            if i<len(parent.value):
                stack[-1][1]=i+1
                if type(list(parent.value.values())[i])==ASTNode:
                    stack.append([list(parent.value.values())[i],0])
            else:
                stack.pop()
        else:
            stack.pop()

if __name__ == '__main__':
    s="{|\'Hello, world!\\n\' -> print} -> foo,foo"
    node = parse_expr_list(s)
    print(node)
    analyse(node)
    s="{x|?((x = 1) | (x = 2)):1:(((x - 1)->F) + ((x - 2)->F))$}->F,input->F->print"
    node = parse_expr_list(s)
    print(node)
    analyse(node)
    s="0->i,%(i < 100)::(i * i)->print$"
    node = parse_expr_list(s)
    print(node)
    analyse(node)
