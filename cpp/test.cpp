#include "TAPE.h"
#include "MCONFIG.h"
#include "Lambda.h"
#include "MACHINE.h"
#include "PRINT.h"
#include <stdlib.h>

#include "TATp81.h"
#include "TATp81f.h"
// #include "TATp83.h"
// #include "TATp84.h"
// #include "TATp87.h"
// #include "TATp150.h"
#include "U.h"


void status(){
    PRINT::print("size of Lambda: ") ;
    PRINT::print((int)sizeof(Lambda)) ;
    PRINT::print("\n") ;
    PRINT::print(NB_LAMBDA) ;
    PRINT::print(" Lambda (max ") ;
    PRINT::print(MAX_LAMBDA) ; 
    PRINT::print(", max_size ") ;   
    PRINT::print(MAX_SIZE_LAMBDA) ; 
    PRINT::print(")\n")  ;
}


int main(int argc, char *argv[]) {
    int steps = 0 ;
    if (argc > 1){
        steps = atoi(argv[1]) ;
        if (steps < 1){
            steps = 1 ;
        }
    }

    status() ;
    {
        //TAPE::get_tape()->blank() ;
        //PRINT::print("TATp81 run:\t") ;
        //TATp81::m.run(1) ;
        //TAPE::get_tape()->blank() ;
        //PRINT::print("TATp81f run:\t") ;
        //TATp81f::m.run(20) ;
        //TAPE::get_tape()->blank() ;
        //PRINT::print("TATp150 run:\t") ;
        //TATp150::m.run(10) ;

        TAPE::get_tape()->init("ee; D A D D C R D A A ; D A A D D C C R D A %") ;
        // TAPE::get_tape()->init("ee; D A D D C R D A A ; D A A D D R D A A A ; D A A A D D C C R D A A A A ; D A A A A D D R D A %") ;
        // TAPE::get_tape()->init("ee; D A D D C R D A A ; D A A D D R D A A A ; D A A A D D C C R D A A A A ; D A A A A D D R D A A A A A ; D A A A A A D D C R D A A A A %") ;
        // TAPE::get_tape()->init("ee; D A D D C C C L D A A ; D A D C D C R D A ; D A D C C D C C R D A ; D A D C C C D C C C R D A ; D A D C C C C D C C C C R D A ; D A A D C C C C D C C C C L D A A A ; D A A D C D C L D A A ; D A A D C C D C C L D A A ; D A A D C C C D C C C L D A A ; D A A D D L D A A ; D A A A D C C C D C C R D A ; D A A A D C D C R D A A A A ; D A A A D C C D C C L D A A A ; D A A A D C C C C D C C C C L D A A A ; D A A A D D L D A A A ; D A A A A D C C C C D C R D A A A A A ; D A A A A D C D C R D A A A A ; D A A A A D C C D C C R D A A A A ; D A A A A D C C C D C C C R D A A A A ; D A A A A D D R D A A A A ; D A A A A A D D C C C C R D A ; D A A A A A D C D C R D A A A A A ; D A A A A A D C C D C C R D A A A A A ; D A A A A A D C C C D C C C R D A A A A A ; D A A A A A D C C C C D C C C C R D A A A A A %") ;
        PRINT::print("U(TATp150) run:\t") ;
        MACHINE m(TAPE::get_tape(), U::b) ;
        m.run(steps) ;
    }
    status() ;

}


// "ee; D A D D C R D A A ; D A A D D C C R D A %"
