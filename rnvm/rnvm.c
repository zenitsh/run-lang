#include <stdio.h>
#include "rnvm/rnvm.h"

int main(){
    RLinstance *instance = rlCreateInstance(4096);

    const char * code = 
    "jumpim start\n"
    "F:\n"
        "getsi 31\n"//P -> R31
        "setmii 0 31\n"//R0 -> [R31]
        "addsim 8\n"//P -> P + 8

        "setiim 1 31\n"//1 -> R31
        "subi 0 31 2\n"//R0 - R31 -> R2
        "jziim 2 L0\n"//IF R2 != 0
        "setiim 2 31\n"//2 -> R31
        "subi 0 31 2\n"//R0 - R31 -> R2
        "jziim 2 L0\n"//IF R2 != 0
        
        "setiim 1 31\n"//1 -> R[31]
        "subi 0 31 0\n"//R0 - R31 -> R0
        "xim F\n"//EXECUTE F
        "getsi 31\n"//P -> R31
        "setiim 4 30\n"//4 -> R30
        "subi 31 30 31\n"//R31 - R30 -> R31
        "setmii 0 31\n"//R0 -> [R31]
        "subi 31 30 31\n"//R31 - R30 -> R31
        "getmii 0 31\n"//[R31] -> R0
        "setiim 2 31\n"//2 -> R31
        "subi 0 31 0\n"//R0 - R31 -> R0
        "xim F\n"
        "getsi 31\n"//P -> R31
        "setiim 4 30\n"//4 -> R30
        "subi 31 30 31\n"//R31 - R30 -> R31
        "getmii 1 31\n"//[R31] -> R1
        "addi 0 1 0\n"//R0 + R1 -> R0

        "retn\n"//RETURN
        "L0:\n"
            "setiim 1 0\n"//1 -> R0
            "retn\n"//RETURN
    "start:\n"
        "sysi 0 3\n"// IN -> R0
        "xim F\n"//EXECUTE F
        "sysi 0 1\n"//SYSTEM 1 R0
        "sysi 0 0\n";//SYSTEM 0 R0

    rlInterpret(instance, code);

    rlDeleteInstance(instance);
    return 0;
}
