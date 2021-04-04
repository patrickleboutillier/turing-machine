#include "MF.h"

namespace TATp81f {


extern MCONFIG b, c, e, f ;


// j x@(mC, a) = "j"%x  ==> [Sym a   []    $ c ]
MC j(MC C, char a){
  return MF(C, a, [](MC C, char a, char s){
    SYM(s, a, "", C) ;
  }) ;
}

// i x@(mC)    = "i"%x  ==> [Var           $ (\s -> j (mC, s)) ]
MC i(MC C){
  return MF(C, [](MC C, char s){
    return j(C, s)->clone() ;
  }) ;
}


MCONFIG b([](char s){
  NONE(s, "0>", i(&c)) ;
}) ;
MCONFIG c([](char s){
  NONE(s, " >", &e) ;
}) ;
MCONFIG e([](char s){
  NONE(s, "1>", &f) ;
}) ;
MCONFIG f([](char s){
  NONE(s, " >", &b) ;
}) ;


MACHINE m(&b) ;

} ;