namespace TATp81f {


extern MC b, c, e, f ;


// j x@(mC, a) = "j"%x  ==> [Sym a   []    $ c ]
MF<MC(MC C, char a)> j("j", [](MC C, char a, char s){
  SYM(s, a, "", C) ;
}) ;

// i x@(mC)    = "i"%x  ==> [Var           $ (\s -> j (mC, s)) ]
MF<MC(MC C)> i("i", [](MC C,  char s) {
  return j(C, s) ;
}) ;


MC b("b", [](char s){
  NONE(s, "0>", i(c)) ;
}) ;
MC c("c", [](char s){
  NONE(s, " >", e) ;
}) ;
MC e("e", [](char s){
  NONE(s, "1>", f) ;
}) ;
MC f("f", [](char s){
  NONE(s, " >", b) ;
}) ;


TAPE tape ;
MACHINE m(&tape, b) ;

} ;