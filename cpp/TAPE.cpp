#include "TAPE.h"
#include "PRINT.h"

#include "MCONFIG.h"


TAPE instance ;


TAPE *TAPE::get_tape(){
  return &instance ;
}


TAPE::TAPE(){
  blank() ;
}


void TAPE::blank(){
  for (int i = 0 ; i < (TAPE_LEN-1) ; i++){
    _squares[i] = ' ' ;
  }
  _squares[TAPE_LEN-1] = '\0' ;
  _pos = 1 ;
  _max_pos = 1 ;
}


void TAPE::init(const char *tape){
  blank() ;
  for (int i = 0 ; tape[i] != '\0' ; i++){
    _squares[_pos+i] = tape[i] ;
  }  
}


bool TAPE::apply_ops(const char *ops){
  for (int i = 0 ; ops[i] != '\0' ; i++){
    switch (ops[i]){
      case '>': 
        _pos++ ; 
        if (_pos > _max_pos){
          _max_pos = _pos ;
        }
        break ;
      case '<': _pos-- ; break ;
      default: _squares[_pos] = ops[i] ;
    }
  }
  return true ;
}


char TAPE::scan(){
  return _squares[_pos] ;
}


void TAPE::print(const char *mc){
  char x = _squares[_pos] ;
  _squares[_pos] = '\0' ;
  PRINT::print("[") ;
  PRINT::print(_squares) ;
  PRINT::print(x) ;
  PRINT::print("/") ;
  PRINT::print(mc) ;
  _squares[_pos] = x ;

  if (_max_pos > _pos){
    char m = _squares[_max_pos] ;
    _squares[_max_pos] = '\0' ;
    PRINT::print(_squares + _pos + 1) ;
    _squares[_max_pos] = m ;
  }

  PRINT::print("]\n") ;
}
