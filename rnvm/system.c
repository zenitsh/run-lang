#include "rnvm/rnvm.h"
#include <stdio.h>
#include <string.h>

void rlSysi(RLinstance * instance, RLubyte r, RLint imm){
    switch(imm){
        case 0x00:
        printf("\n");
        break;
        case 0x01:
        printf("%d", instance->cpu.R[r]);
        break;
        case 0x02:
        printf("%f", instance->cpu.F[r]);
        break;
        case 0x03:
        scanf("%d", &instance->cpu.R[r]);
        break;
    }
}

void rlSetioi(RLinstance * instance, RLubyte r1, RLubyte r2){}
void rlGetioi(RLinstance * instance, RLubyte r1, RLubyte r2){}
void rlSetiof(RLinstance * instance, RLubyte r1, RLubyte r2){}
void rlGetiof(RLinstance * instance, RLubyte r1, RLubyte r2){}