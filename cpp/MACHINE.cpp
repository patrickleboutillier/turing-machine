#include "MACHINE.h"
#include "PRINT.h"


MACHINE::MACHINE(TAPE *tape, MCONFIG begin) : _begin(begin) {
  _tape = tape ;
}


TAPE *MACHINE::get_tape(){
  return _tape ;
}


void MACHINE::run(int steps){
  _run(steps, false) ;
}


void MACHINE::step(int steps){
  _run(steps, true) ;
}


void MACHINE::_run(int steps, bool step){
  int n = 0 ;
  MCONFIG mc = _begin ;

  while (1) {
    n++ ;
    if (n >= steps){
      PRINT::print(n) ;
      _tape->print("?") ;
      return ;
    }
    if (step){
      PRINT::print(n) ;
      _tape->print("?") ; 
      if (n >= (steps - 10)){
      }
    }

    char s = _tape->scan() ;
    mc = mc(s) ;
  }
}
