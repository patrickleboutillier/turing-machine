namespace TATp81 {


extern MC b, c, e, f ;


MC b([](char s){
  NONE(s, "0>", c) ;
}) ;
MC c([](char s){
  NONE(s, " >", e) ;
}) ;
MC e([](char s){
  NONE(s, "1>", f) ;
}) ;
MC f([](char s){
  NONE(s, " >", b) ;
}) ;


MACHINE m(TAPE::get_tape(), b) ;

} ;