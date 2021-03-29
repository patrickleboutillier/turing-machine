#include "TAPE.h"
#include "MCONFIG.h"
#include "MACHINE.h"
#include <stdio.h>
#include <stdlib.h>

#include "TATp81.h"
#include "TATp81f.h"
// #include "TATp83.h"
// #include "TATp84.h"
// #include "TATp87.h"
// #include "TATp150.h"
// #include "U.h"


// MCONFIG MC(" 01:%;ACDLNReuvwxyz") ;
// TAPE t("ee; D A D D C R D A A ; D A A D D C C R D A %") ;

int main(int argc, char *argv[]) {
    printf("TATp81 run:\t") ;
    TATp81::m.run(20) ;
    printf("TATp81f run:\t") ;
    TATp81f::m.run(20) ;
}


// "ee; D A D D C R D A A ; D A A D D C C R D A %"
