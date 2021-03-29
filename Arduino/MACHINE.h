#ifndef MACHINE_H
#define MACHINE_H

#include "TAPE.h"
#include "MCONFIG.h"


class MACHINE {
  private:
    TAPE *_tape ;
    MCONFIG *_begin ;
    void _run(int steps, bool step) ;
  public:
    MACHINE(TAPE *tape, MC *begin) ;
    TAPE *get_tape() ;
    void run(int steps) ;
    void step(int steps) ;
} ;


#endif
