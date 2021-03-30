#include "TAPE.h"
#include "MCONFIG.h"
#include "Lambda.h"
#include "MACHINE.h"
#include <stdio.h>
#include <stdlib.h>

#include "TATp81.h"
 #include "TATp81f.h"
// #include "TATp83.h"
// #include "TATp84.h"
// #include "TATp87.h"
// #include "TATp150.h"
#include "U.h"


void status(){
    printf("size of Lambda<MCONFIG(char): %ld\n", sizeof(Lambda<MCONFIG(char s)>)) ;
    printf("%d Lambda (max %d, max_size %d)\n", NB_LAMBDA, MAX_LAMBDA, MAX_SIZE_LAMBDA) ;
    printf("%d MF\n", NB_MF) ;
}

// MCONFIG MC(" 01:%;ACDLNReuvwxyz") ;
// TAPE t("ee; D A D D C R D A A ; D A A D D C C R D A %") ;

int main(int argc, char *argv[]) {
    int steps = 0 ;
    if (argc > 0){
        steps = atoi(argv[1]) ;
        if (steps < 1){
            steps = 1 ;
        }
    }

    status() ;
    {
        TAPE::get_tape()->blank() ;
        printf("TATp81 run:\t") ;
        TATp81::m.run(20) ;
        TAPE::get_tape()->blank() ;
        printf("TATp81f run:\t") ;
        TATp81f::m.run(20) ;

        TAPE::get_tape()->init("ee; D A D D C R D A A ; D A A D D C C R D A %") ;
        printf("U(TATp150) run:\t") ;
        MACHINE m(TAPE::get_tape(), U::b) ;
        m.run(steps) ;
    }
    status() ;

}


// "ee; D A D D C R D A A ; D A A D D C C R D A %"
