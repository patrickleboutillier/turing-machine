#ifndef MACHINE_H
#define MACHINE_H

#include "TAPE.h"
#include "MCONFIG.h"


class MACHINE {
  private:
    MCONFIG &_begin ;
    MC _run(int steps, bool step) ;
  public:
    MACHINE(MCONFIG &begin) ;
    MC run(int steps) ;
    MC step(int steps) ;
} ;


#endif
