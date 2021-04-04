#include "MCONFIG.h"
#include "MFUNCTIONS.h"


// page 115
MC f(MC C, MC B, char a){
  return MF(C, B, a, [](MC C, MC B, char a, char s){
    SYM(s, 'e', "<", f1(C, B, a)) ;
    NOT(s, 'e', "<", f(C, B, a)) ;
    NONE(s,     "<", f(C, B, a)) ;
  }) ;
}
MC f1(MC C, MC B, char a){
  return MF(C, B, a, [](MC C, MC B, char a, char s){
    SYM(s, a,   "",   C) ;
    NOT(s, a,   ">",  f1(C, B, a)) ;
    NONE(s,     ">",  f2(C, B, a)) ;
  }) ;
}
MC f2(MC C, MC B, char a){
  return MF(C, B, a, [](MC C, MC B, char a, char s){
    SYM(s, a,   "",   C) ;
    NOT(s, a,   ">",  f1(C, B, a)) ;
    NONE(s,     ">",  B) ;
  }) ;
}


// page 118
MC e(MC C, MC B, char a){
  return MF(C, B, a, [](MC C, MC B, char a, char s){
    BLANK(s, "",  f(e1(C, B, a), B, a)) ;
  }) ;
}
MC e1(MC C, MC B, char a){
  return MF(C, [](MC C, char s){
    BLANK(s, " ", C) ;
  }) ;
}  
MC e(MC B, char a){
  return MF(B, a, [](MC B, char a, char s){
    BLANK(s, "",  e(e(B, a), B, a)) ;
  }) ; 
} 


// page 120
MC pe(MC C, char b){
  return MF(C, b, [](MC C, char b, char s){
    BLANK(s, "", f(pe1(C, b), C, 'e')) ;
  }) ;
}  
MC pe1(MC C, char b){
  return MF(C, b, [](MC C, char b, char s){
    ANY(s,  ">>", pe1(C, b)) ;
    const char op[] = {b, '\0'} ;
    NONE(s, op,   C) ;
  }) ;
}  


// page 121
MC l(MC C){ 
  return MF(C, [](MC C, char s){
    BLANK(s, "<", C) ;
  }) ;
}  
MC r(MC C){ 
  return MF(C, [](MC C, char s){
    BLANK(s, ">", C) ;
  }) ;
}

MC fl(MC C, MC B, char a){
  return MF(C, B, a, [](MC C, MC B, char a, char s){
    BLANK(s, "", f(l(C), B, a)) ;
  }) ;
}
MC fr(MC C, MC B, char a){
  return MF(C, B, a, [](MC C, MC B, char a, char s){
    BLANK(s, "", f(r(C), B, a)) ;
  }) ;
}

MC c(MC C, MC B, char a){
  return MF(C, B, a, [](MC C, MC B, char a, char s){
    BLANK(s, "", fl(c1(C), B, a)) ;
  }) ;
}
MC c1(MC C){ 
  return MF(C, [](MC C, char s){
    return pe(C, s)->clone() ;
  }) ;
}


// page 122
MC ce(MC C, MC B, char a){
  return MF(C, B, a, [](MC C, MC B, char a, char s){
    BLANK(s, "", c(e(C, B, a), B, a)) ;
  }) ;
}  
MC ce(MC B, char a){
  return MF(B, a, [](MC B, char a, char s){
    BLANK(s, "", ce(ce(B, a), B, a)) ;
  }) ;
}  

MC re(MC C, MC B, char a, char b){
  return MF(C, B, a, b, [](MC C, MC B, char a, char b, char s){
    BLANK(s, "", f(re1(C, b), B, a)) ;
  }) ;
}  
MC re1(MC C, char b){
  return MF(C, b, [](MC C, char b, char s){
    const char ops[] = {' ', b, '\0'} ;
    BLANK(s, ops, C) ;
  }) ;
}  

MC re(MC B, char a, char b){
  return MF(B, a, b, [](MC B, char a, char b, char s){
    BLANK(s, "", re(re(B, a, b), B, a, b)) ;
  }) ; 
}


// page 123
MC cr(MC C, MC B, char a){
  return MF(C, B, a, [](MC C, MC B, char a, char s){
    BLANK(s, "", c(re(C, B, a, a), B, a)) ;
  }) ;
}  
MC cr(MC B, char a){
  return MF(B, a, [](MC B, char a, char s){
    BLANK(s, "", cr(cr(B, a), re(B, a, a), a)) ;
  }) ;
} 

MC cp(MC C, MC U, MC E, char a, char b){
  return MF(C, U, E, a, b, [](MC C, MC U, MC E, char a, char b, char s){
    BLANK(s, "", fl(cp1(C, U, b), f(U, E, b), a)) ;
  }) ;
} 
MC cp1(MC C, MC U, char b){
  return MF(C, U, b, [](MC C, MC U, char b, char s){
    return fl(cp2(C, U, s), U, b)->clone() ;
  }) ;
}
MC cp2(MC C, MC U, char y){
  return MF(C, U, y, [](MC C, MC U, char y, char s){
    SYM(s, y, "", C) ;
    NOT(s, y, "", U) ; // NONE line required here?
  }) ;
} 


MC cpe(MC C, MC U, MC E, char a, char b){
  return MF(C, U, E, a, b, [](MC C, MC U, MC E, char a, char b, char s){
    BLANK(s, "", cp(e(e(C, C, b), C, a), U, E, a, b)) ;
  }) ;
} 
MC cpe(MC U, MC E, char a, char b){
  return MF(U, E, a, b, [](MC U, MC E, char a, char b, char s){
    BLANK(s, "", cpe(cpe(U, E, a, b), U, E, a, b)) ;
  }) ;
}


// page 124, g instead of q
MC g(MC C){
  return MF(C, [](MC C, char s){
    ANY(s,  ">", g(C)) ;
    NONE(s, ">", g1(C)) ;
  }) ;
}
MC g1(MC C){
  return MF(C, [](MC C, char s){
    ANY(s,  ">", g(C)) ;
    NONE(s, "",  C) ;
  }) ;
}


MC g(MC C, char a){
  return MF(C, a, [](MC C, char a, char s){
    BLANK(s, "", g(g1(C, a))) ;
  }) ;
} 
MC g1(MC C, char a){
  return MF(C, a, [](MC C, char a, char s){
    SYM(s, a, "", C) ;
    NOT(s, a, "<", g1(C, a)) ;
    NONE(s,   "<", g1(C, a)) ;
  }) ;
} 


MC pe2(MC C, char a, char b){
  return MF(C, a, b, [](MC C, char a, char b, char s){
    BLANK(s, "", pe(pe(C, b), a)) ; 
  }) ;
} 


// page 125
MC ce2(MC B, char a, char b){
  return MF(B, a, b, [](MC B, char a, char b, char s){
    BLANK(s, "", ce(ce(B, b), a)) ;
  }) ;
}
MC ce3(MC B, char a, char b, char y){
  return MF(B, a, b, y, [](MC B, char a, char b, char y, char s){
    BLANK(s, "", ce(ce2(B, b, y), a)) ;
  }) ;
}
MC ce4(MC B, char a, char b, char y, char o){
  return MF(B, a, b, y, o, [](MC B, char a, char b, char y, char o, char s){
    BLANK(s, "", ce(ce3(B, b, y, o), a)) ;
  }) ;
}
MC ce5(MC B, char a, char b, char y, char o, char e){
  return MF(B, a, b, y, o, e, [](MC B, char a, char b, char y, char o, char e, char s){
    BLANK(s, "", ce(ce4(B, b, y, o, e), a)) ;
  }) ;
}

MC e(MC C){
  return MF(C, [](MC C, char s){
    SYM(s, 'e', ">", e1(C)) ;
    NOT(s, 'e', "<", e(C)) ;
    NONE(s,     "<", e(C)) ;
  }) ;
}    
MC e1(MC C){
  return MF(C, [](MC C, char s){
    ANY(s,  "> >", e1(C)) ; 
    NONE(s, "",    C) ;
  }) ;
}    

