namespace TATp81f {


extern MC b, c, e, f ;


// j x@(mC, a) = "j"%x  ==> [Sym a   []    $ c ]
MC j(MC C, char a){
  return MC([C, a](char s){
    SYM(s, a, "", C) ;
  }) ;
}

// i x@(mC)    = "i"%x  ==> [Var           $ (\s -> j (mC, s)) ]
MC i(MC C){
  return MC([C](char s){
    return j(C, s) ;
  }) ;
}


MC b([](char s){
  NONE(s, "0>", i(c)) ;
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