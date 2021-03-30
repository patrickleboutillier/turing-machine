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
#include "U.h"


void status(){
    printf("size of Lambda: %ld\n", sizeof(Lambda<MCONFIG(char s)>)) ;
    printf("%d MC (max %d, max size %d), %d MF\n", NB_MC, MAX_MC, MAX_SIZE_MC, NB_MF) ;
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
        printf("TATp81 run:\t") ;
        TATp81::m.run(20) ;
        printf("TATp81f run:\t") ;
        TATp81f::m.run(20) ;

        printf("U(TATp150) run:\t") ;
        TAPE tape("ee; D A D D C R D A A ; D A A D D C C R D A %") ;
        MACHINE m(&tape, U::b) ;
        m.run(steps) ;
    }
    status() ;

}


// "ee; D A D D C R D A A ; D A A D D C C R D A %"
