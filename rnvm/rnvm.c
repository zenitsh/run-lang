#include <stdio.h>
#include "rnvm.h"

int main(){
    RLinstance *instance = rlCreateInstance(4096);

    const char * code =
    "jumpim start\n"
    "foo2:\n"
    "setiim 200 0\n"
    "sysi 0 0\n"
    "retn\n"
    "foo:\n"
    "setiim 100 0\n"
    "sysi 0 0\n"
    "xim foo2\n"
    "retn\n"
    "start:\n"
    "xim foo\n";

    rlInterpret(instance, code);

    rlDeleteInstance(instance);
    return 0;
}
