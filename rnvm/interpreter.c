#include "rnvm/rnvm.h"
#include "rnvm/rl_util.h"
#include <malloc.h>
#include <string.h>

#define printf(args...)

#define RL_IN_INTERPRET_ZERO_PARAM(p, f) \
    if(rlStrcmpp(_tok[i], &j, #p)){ \
        printf(#p " \n"); \
        rl##f(instance); \
        ++instance->cpu.C; \
    }

#define RL_IN_INTERPRET_ONE_PARAM(p, f) \
    if(rlStrcmpp(_tok[i], &j, #p)){ \
        int a1 = rlScanp(_label, _label_pos, _label_count, _tok[i], &j); \
        printf(#p " %d\n", a1); \
        rl##f(instance, a1); \
        ++instance->cpu.C; \
    }

#define RL_IN_INTERPRET_TWO_PARAMS(p, f) \
    if(rlStrcmpp(_tok[i], &j, #p)){ \
        int a1 = rlScanp(_label, _label_pos, _label_count, _tok[i], &j); \
        int a2 = rlScanp(_label, _label_pos, _label_count, _tok[i], &j); \
        printf(#p " %d %d\n", a1, a2); \
        rl##f(instance, a1, a2); \
        ++instance->cpu.C; \
    }

#define RL_IN_INTERPRET_THREE_PARAMS(p, f) \
    if(rlStrcmpp(_tok[i], &j, #p)){ \
        int a1 = rlScanp(_label, _label_pos, _label_count, _tok[i], &j); \
        int a2 = rlScanp(_label, _label_pos, _label_count, _tok[i], &j); \
        int a3 = rlScanp(_label, _label_pos, _label_count, _tok[i], &j); \
        printf(#p " %d %d %d\n", a1, a2, a3); \
        rl##f(instance, a1, a2, a3); \
        ++instance->cpu.C; \
    }

RLint rlAtoip(char * str, RLuint * index){
    RLint i = 0;
    while(str[*index]<='9'&&str[*index]>='0'){
        i=i*10+str[*index]-'0';
        ++(*index);
    }
    ++(*index);
    return i;
}

RLbool rlStrcmpp(char * str1, RLuint * index, const char * str2){
    RLbool b = !memcmp(str1+(*index)*sizeof(char), str2, strlen(str2));
    //printf("strcmp:%s:%s\n", str1+(*index)*sizeof(char),str2);
    if(b)
        (*index)+=strlen(str2)+1;
    return b;
}

RLint rlScanp(char * label[256], RLuint label_pos[256], RLuint label_count, char * str, RLuint * index){
    if(str[*index]<='9'&&str[*index]>='0'){
        return rlAtoip(str, index);
    }
    RLuint i=*index;
    while(str[i]!='\n'&&str[i]!=' ')++i;
    for(int j=0;j<label_count;++j){
        if(rlStrcmpp(str, index, label[j])){
            (*index)+=strlen(label[j])+1;
            return label_pos[j];
        }
    }
    return 0;
}

void rlInterpret(RLinstance *instance, const char * code){
    char * _code;
    char * _tok[1024];
    _code = (char*)malloc(strlen(code)*sizeof(char));
    memcpy(_code, code, strlen(code)*sizeof(char));
    RLuint _tok_count = 0;
    const char * _delim0 = "\n";
    const char * _delim1 = " ";
    _tok[_tok_count]=strtok(_code, _delim0);
    char * _label[256];
    RLuint _label_pos[256];
    RLuint _label_count = 0;
    //RLuint _line_count = 0;
    while(_tok[_tok_count]){
        if(_tok[_tok_count][strlen(_tok[_tok_count])-1]==':'){
            _tok[_tok_count][strlen(_tok[_tok_count])-1] = '\0';
            _label[_label_count]=_tok[_tok_count];
            _label_pos[_label_count]=_tok_count;
            ++_label_count;
        }else if(strlen(_tok[_tok_count])){
            ++_tok_count;
        }
        _tok[_tok_count]=strtok(NULL, _delim0);
    }
    printf("#labels:\n");
    for(RLuint i=0;i<_label_count;++i){
        printf("%s:%u\n", _label[i], _label_pos[i]);
    }
    printf("\n");
    for(instance->cpu.C=0;instance->cpu.C<_tok_count;){
        RLuint j=0;
        RLuint i=instance->cpu.C;
        RL_IN_INTERPRET_TWO_PARAMS(setiim, Setiim)
        else RL_IN_INTERPRET_TWO_PARAMS(setfim, Setfim)
        else RL_IN_INTERPRET_TWO_PARAMS(seti, Seti)
        else RL_IN_INTERPRET_TWO_PARAMS(setmii, Setmii)
        else RL_IN_INTERPRET_TWO_PARAMS(getmii, Getmii)
        else RL_IN_INTERPRET_TWO_PARAMS(setmfi, Setmfi)
        else RL_IN_INTERPRET_TWO_PARAMS(getmfi, Getmfi)
        else RL_IN_INTERPRET_THREE_PARAMS(addi, Addi)
        else RL_IN_INTERPRET_THREE_PARAMS(subi, Subi)
        else RL_IN_INTERPRET_THREE_PARAMS(muli, Muli)
        else RL_IN_INTERPRET_THREE_PARAMS(divi, Divi)
        else RL_IN_INTERPRET_THREE_PARAMS(remi, Remi)
        else RL_IN_INTERPRET_THREE_PARAMS(addf, Addi)
        else RL_IN_INTERPRET_THREE_PARAMS(subf, Subi)
        else RL_IN_INTERPRET_THREE_PARAMS(mulf, Muli)
        else RL_IN_INTERPRET_THREE_PARAMS(divf, Divi)
        else RL_IN_INTERPRET_TWO_PARAMS(sysi, Sysi)
        else RL_IN_INTERPRET_ZERO_PARAM(retn, Retn)
        else RL_IN_INTERPRET_ONE_PARAM(addsim, Addsim)
        else RL_IN_INTERPRET_ONE_PARAM(subsim, Subsim)
        else RL_IN_INTERPRET_ONE_PARAM(getsi, Getsi)
        else RL_IN_INTERPRET_ONE_PARAM(getbi, Getbi)
        else if(rlStrcmpp(_tok[i], &j, "jumpim")){
            int a1 = rlScanp(_label, _label_pos, _label_count, _tok[i], &j);
            printf("jumpim %d\n", a1);
            rlJumpim(instance, a1);
        }else if(rlStrcmpp(_tok[i], &j, "jziim")){
            int a1 = rlScanp(_label, _label_pos, _label_count, _tok[i], &j);
            int a2 = rlScanp(_label, _label_pos, _label_count, _tok[i], &j);
            printf("jziim %d %d\n", a1, a2);
            rlJziim(instance, a1, a2);
        }else if(rlStrcmpp(_tok[i], &j, "jaiim")){
            int a1 = rlScanp(_label, _label_pos, _label_count, _tok[i], &j);
            int a2 = rlScanp(_label, _label_pos, _label_count, _tok[i], &j);
            printf("jaiim %d %d\n", a1, a2);
            rlJaiim(instance, a1, a2);
        }else if(rlStrcmpp(_tok[i], &j, "xim")){
            int a1 = rlScanp(_label, _label_pos, _label_count, _tok[i], &j);
            printf("xim %d\n", a1);
            rlXim(instance, a1); 
        }
    }
    free(_code);
}