class ASTNode:
    def __init__(self, type : str, value):
        self.type = type
        self.rtype = 'null'
        self.ltype = 'null'
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
        return "<{}->{}/{}:{}>".format(self.ltype,self.rtype,self.type, v)