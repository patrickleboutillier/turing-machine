namespace TATp150 {


extern MC b, c ;


MC b([](char s){
  NONE(s, "0>", c) ;
}) ;
MC c([](char s){
  NONE(s, "1>", b) ;
}) ;


MACHINE m(TAPE::get_tape(), b) ;

} ;

