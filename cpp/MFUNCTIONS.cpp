#include "MCONFIG.h"
#include "MFUNCTIONS.h"


// page 115
MC f(MC C, MC B, char a){
  return MC([C, B, a](char s){
    SYM(s, 'e', "<", f1(C, B, a)) ;
    NOT(s, 'e', "<", f(C, B, a)) ;
    NONE(s,     "<", f(C, B, a)) ;
  }) ;
}
MC f1(MC C, MC B, char a){
  return MC([C, B, a](char s){
    SYM(s, a,   "",   C) ;
    NOT(s, a,   ">",  f1(C, B, a)) ;
    NONE(s,     ">",  f2(C, B, a)) ;
  }) ;
}
MC f2(MC C, MC B, char a){
  return MC([C, B, a](char s){
    SYM(s, a,   "",   C) ;
    NOT(s, a,   ">",  f1(C, B, a)) ;
    NONE(s,     ">",  B) ;
  }) ;
}


// page 118
MC e(MC C, MC B, char a){
  return MC([C, B, a](char s){
    BLANK(s, "",  f(e1(C, B, a), B, a)) ;
  }) ;
}
MC e1(MC C, MC B, char a){
  return MC([C](char s){
    BLANK(s, " ", C) ;
  }) ;
}  
MC e(MC B, char a){
  return MC([B, a](char s){
    BLANK(s, "",  e(e(B, a), B, a)) ;
  }) ; 
} 


// page 120
MC pe(MC C, char b){
  return MC([C, b](char s){
    BLANK(s, "", f(pe1(C, b), C, 'e')) ;
  }) ;
}  
MC pe1(MC C, char b){
  return MC([C, b](char s){
    ANY(s,  ">>", pe1(C, b)) ;
    const char op[] = {b, '\0'} ;
    NONE(s, op,   C) ;
  }) ;
}  


// page 121
MC l(MC C){ 
  return MC([C](char s){
    BLANK(s, "<", C) ;
  }) ;
}  
MC r(MC C){ 
  return MC([C](char s){
    BLANK(s, ">", C) ;
  }) ;
}

MC fl(MC C, MC B, char a){
  return MC([C, B, a](char s){
    BLANK(s, "", f(l(C), B, a)) ;
  }) ;
}
MC fr(MC C, MC B, char a){
  return MC([C, B, a](char s){
    BLANK(s, "", f(r(C), B, a)) ;
  }) ;
}

MC c(MC C, MC B, char a){
  return MC([C, B, a](char s){
    BLANK(s, "", fl(c1(C), B, a)) ;
  }) ;
}
MC c1(MC C){ 
  return MC([C](char s){
    return pe(C, s) ;
  }) ;
}


// page 122
MC ce_3(MC C, MC B, char a){
  return MC([C, B, a](char s){
    BLANK(s, "", c(e(C, B, a), B, a)) ;
  }) ;
}  
MC ce_2(MC B, char a){
  return MC([B, a](char s){
    BLANK(s, "", ce_3(ce_2(B, a), B, a)) ;
  }) ;
}  

MC re_4(MC C, MC B, char a, char b){
  return MC([C, B, a, b](char s){
    BLANK(s, "", f(re1(C, b), B, a)) ;
  }) ;
}  
MC re1(MC C, char b){
  return MC([C, b](char s){
    const char ops[] = {' ', b, '\0'} ;
    BLANK(s, ops, C) ;
  }) ;
}  

MC re_3(MC B, char a, char b){
  return MC([B, a, b](char s){
    BLANK(s, "", re_4(re_3(B, a, b), B, a, b)) ;
  }) ; 
}


// page 123
MC cr_3(MC C, MC B, char a){
  return MC([C, B, a](char s){
    BLANK(s, "", c(re_4(C, B, a, a), B, a)) ;
  }) ;
}  
MC cr_2(MC B, char a){
  return MC([B, a](char s){
    BLANK(s, "", cr_3(cr_2(B, a), re_3(B, a, a), a)) ;
  }) ;
} 

MC cp(MC C, MC U, MC E, char a, char b){
  return MC([C, U, E, a, b](char s){
    BLANK(s, "", fl(cp1(C, U, b), f(U, E, b), a)) ;
  }) ;
} 
MC cp1(MC C, MC U, char b){
  return MC([C, U, b](char s){
    return fl(cp2(C, U, s), U, b) ;
  }) ;
}
MC cp2(MC C, MC U, char y){
  return MC([C, U, y](char s){
    SYM(s, y, "", C) ;
    NOT(s, y, "", U) ; // NONE line required here?
  }) ;
} 


MC cpe_5(MC C, MC U, MC E, char a, char b){
  return MC([C, U, E, a, b](char s){
    BLANK(s, "", cp(e(e(C, C, b), C, a), U, E, a, b)) ;
  }) ;
} 
MC cpe_4(MC U, MC E, char a, char b){
  return MC([U, E, a, b](char s){
    BLANK(s, "", cpe_5(cpe_4(U, E, a, b), U, E, a, b)) ;
  }) ;
}


// page 124, g instead of q
MC g(MC C){
  return MC([C](char s){
    ANY(s,  ">", g(C)) ;
    NONE(s, ">", g1(C)) ;
  }) ;
}
MC g1(MC C){
  return MC([C](char s){
    ANY(s,  ">", g(C)) ;
    NONE(s, "",  C) ;
  }) ;
}


MC g_2(MC C, char a){
  return MC([C, a](char s){
    BLANK(s, "", g(g1_2(C, a))) ;
  }) ;
} 
MC g1_2(MC C, char a){
  return MC([C, a](char s){
    SYM(s, a, "", C) ;
    NOT(s, a, "<", g1_2(C, a)) ;
    NONE(s,   "<", g1_2(C, a)) ;
  }) ;
} 

MC pe2(MC C, char a, char b){
  return MC([C, a, b](char s){
    BLANK(s, "", pe(pe(C, b), a)) ; 
  }) ;
} 


// page 125
MC ce2(MC B, char a, char b){
  return MC([B, a, b](char s){
    BLANK(s, "", ce_2(ce_2(B, b), a)) ;
  }) ;
}
MC ce3(MC B, char a, char b, char y){
  return MC([B, a, b, y](char s){
    BLANK(s, "", ce_2(ce2(B, b, y), a)) ;
  }) ;
}
MC ce4(MC B, char a, char b, char y, char o){
  return MC([B, a, b, y, o](char s){
    BLANK(s, "", ce_2(ce3(B, b, y, o), a)) ;
  }) ;
}
MC ce5(MC B, char a, char b, char y, char o, char e){
  return MC([B, a, b, y, o, e](char s){
    BLANK(s, "", ce_2(ce4(B, b, y, o, e), a)) ;
  }) ;
}

MC e(MC C){
  return MC([C](char s){
    SYM(s, 'e', ">", e1(C)) ;
    NOT(s, 'e', "<", e(C)) ;
    NONE(s,     "<", e(C)) ;
  }) ;
}    
MC e1(MC C){
  return MC([C](char s){
    ANY(s,  "> >", e1(C)) ; 
    NONE(s, "",    C) ;
  }) ;
}    

