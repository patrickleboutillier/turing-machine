namespace TATp81 {


extern MC b, c, e, f ;


MC b("b", [](char s){
  NONE(s, "0>", &c) ;
}) ;
MC c("c", [](char s){
  NONE(s, " >", &e) ;
}) ;
MC e("e", [](char s){
  NONE(s, "1>", &f) ;
}) ;
MC f("f", [](char s){
  NONE(s, " >", &b) ;
}) ;


TAPE tape ;
MACHINE m(&tape, &b) ;

} ;