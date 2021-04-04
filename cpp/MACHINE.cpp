#include "MACHINE.h"
#include "PRINT.h"


MACHINE::MACHINE(MCONFIG &begin) : _begin(begin) {
}


MC MACHINE::run(int steps){
  return _run(steps, false) ;
}


MC MACHINE::step(int steps){
  return _run(steps, true) ;
}


MC MACHINE::_run(int steps, bool step){
  int n = 0 ;
  MC mc = _begin.clone() ;

  while (1) {
    n++ ;
    if (n >= steps){
      PRINT::print(n) ;
      TAPE::get_tape()->print("?") ;
      return mc ;
    }
    if (step){
      PRINT::print(n) ;
      TAPE::get_tape()->print("?") ; 
    }

    char s = TAPE::get_tape()->scan() ;
    mc = MCONFIG::move(mc, s) ;
  }
}
