#include "TAPE.h"
#include "MCONFIG.h"
#include "MFUNCTIONS.h"
#include "MACHINE.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
  int steps = 0 ;
  if (argc > 0){
    steps = atoi(argv[1]) ;
    if (steps < 1){
      steps = 1 ;
    }
  }

  //m.step(steps) ;
}


// "ee; D A D D C R D A A ; D A A D D C C R D A %"
