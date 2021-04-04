namespace TATp81 {


extern MCONFIG b, c, e, f ;


MCONFIG b([](char s){
  NONE(s, "0>", &c) ;
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