#include "MACHINE.h"
#include <stdio.h>


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
  MCONFIG::set_tape(_tape) ;

  while (1) {
    n++ ;
    if (n >= steps){
      printf("%6d ", n) ;
      _tape->print(mc) ;
      return ;
    }
    if (step){
      printf("%6d ", n) ;
      _tape->print(mc) ; 
      if (n >= (steps - 10)){
      }
    }

    char s = _tape->scan() ;
    mc = mc(s) ;
  }
}
