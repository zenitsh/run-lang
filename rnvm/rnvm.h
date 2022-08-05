#ifndef __RNVM_H
#define __RNVM_H

#include "rnvm/rl_util.h"
#include "rnvm/rl_instance.h"

void rlSetmi(RLinstance * instance, RLuint mem, RLubyte r);
void rlGetmi(RLinstance * instance, RLuint mem, RLubyte r);
void rlSetmf(RLinstance * instance, RLuint mem, RLubyte r);
void rlGetmf(RLinstance * instance, RLuint mem, RLubyte r);
void rlSetiim(RLinstance * instance, RLint imm, RLubyte r);
void rlSetfim(RLinstance * instance, RLfloat imm, RLubyte r);
void rlSeti(RLinstance * instance, RLubyte r1, RLubyte r2);
void rlSetf(RLinstance * instance, RLubyte r1, RLubyte r2);
void rlSetif(RLinstance * instance, RLubyte r1, RLubyte r2);
void rlSetfi(RLinstance * instance, RLubyte r1, RLubyte r2);
void rlAddsi(RLinstance * instance, RLubyte r);
void rlAddsim(RLinstance * instance, RLint imm);
void rlPushi(RLinstance * instance, RLubyte r);
void rlPushf(RLinstance * instance, RLubyte r);
void rlPopi(RLinstance * instance, RLubyte r);
void rlPopf(RLinstance * instance, RLubyte r);
//rlSwapi
//rlSwapf
void rlAddi(RLinstance * instance, RLubyte r1, RLubyte r2, RLubyte r3);
//rlSubi
//rlMuli
//riDivi
//riRemi
//rlJumpi
void rlJumpim(RLinstance * instance, RLuint imm);
void rlXim(RLinstance * instance, RLuint imm);
void rlRetn(RLinstance * instance);
void rlSysi(RLinstance * instance, RLubyte r, RLint imm);

void rlInterpret(RLinstance * instance, const char * code);
RLinstance * rlCreateInstance(RLuint size);
void rlDeleteInstance(RLinstance* instance);

#endif