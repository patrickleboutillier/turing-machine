#include "MFUNCTIONS.h"

namespace U {


extern MF<MC(MC, char)> con, con1, con2 ;


// page 152
MF<MC(MC, char)> con("con", [](MC C, char a, char s){
  NOT(s, 'A', ">>", con(C, a)) ;
  const char ops[] = {'<', a, '>', '\0'} ;
  SYM(s, 'A', ops,  con1(C, a)) ;
}) ;
MF<MC(MC, char)> con1("con1", [](MC C, char a, char s){
  const char ops[] = {'>', a, '>', '\0'} ;
  SYM(s, 'A', ops, con1(C, a)) ;
  SYM(s, 'D', ops, con2(C, a)) ;
  const char ops2[] = {'D', '>', a, '>', '>', '>', '\0'} ;
  NONE(s, ops2, C) ;
}) ;
MF<MC(MC, char)> con2("con2", [](MC C, char a, char s){
  const char ops[] = {'>', a, '>', '\0'} ;
  SYM(s, 'C', ops,  con2(C, a)) ;
  NOT(s, 'C', ">>", C) ;
  NONE(s,     ">>", C) ;
}) ;


extern MC b, b1, anf, anf1, kom, kmp, sim, sim1, sim2, sim3, 
  mk, mk1, mk2, mk3, mk4, mk5, sh, sh1, sh2, sh3, sh4, sh5, inst, inst1, ov ;


// page 153
MC b("b", [](char s){
  BLANK(s, "", f(b1, b1, '%')) ;
}) ;
MC b1("b1", [](char s){
  const char ops[] = {'>', '>', ':', '>', '>', 'D', '>', '>', 'A', '\0'} ;
  BLANK(s, ops, anf) ;
}) ;

// page 154
MC anf("anf", [](char s){
  BLANK(s, "", g_2(anf1, ':')) ;
}) ;
MC anf1("anf1", [](char s){
  BLANK(s, "", con(kom, 'y')) ;
}) ;

MC kom("kom", [](char s){
  SYM(s, ';', ">z<", con(kmp, 'x')) ;
  SYM(s, 'z', "<<",  kom) ;
  NONE(s,     "<",   kom) ; 
  ANY(s,      "<",   kom) ;
}) ;

MC kmp("kmp", [](char s){
  BLANK(s, "", cpe_4(e_2(e_2(anf, 'x'), 'y'), sim, 'x', 'y')) ;
}) ;

MC sim("sim", [](char s){
  BLANK(s, "", fl(sim1, sim1, 'z')) ;
}) ;
MC sim1("sim1", [](char s){
  BLANK(s, "", con(sim2, ' ')) ;
}) ;
MC sim2("sim2", [](char s){
  SYM(s, 'A', "",      sim3) ;
  NOT(s, 'A', "<u>>>", sim2) ; 
}) ;
MC sim3("sim3", [](char s){
  NOT(s, 'A', "<y",    e_2(mk, 'z')) ;
  SYM(s, 'A', "<y>>>", sim3) ;
}) ;


MC mk("mk", [](char s){
  BLANK(s, "", g_2(mk1, ':')) ;
}) ;
MC mk1("mk1", [](char s){
  NOT(s, 'A', ">>",   mk1) ;
  SYM(s, 'A', "<<<<", mk2) ;
}) ;
MC mk2("mk2", [](char s){
  SYM(s, 'C', ">x<<<", mk2) ;
  SYM(s, ':', "",      mk4) ;
  SYM(s, 'D', ">x<<<", mk3) ;
}) ;
MC mk3("mk3", [](char s){
  NOT(s, ':', ">v<<<", mk3) ;
  SYM(s, ':', "",      mk4) ;
}) ;
MC mk4("mk4", [](char s){
  BLANK(s, "", con(l(l(mk5)), ' ')) ;
}) ;
MC mk5("mk5", [](char s){
  ANY(s, ">w>", mk5) ;
  NONE(s, ":", sh) ;
}) ;


MC sh("sh", [](char s){
  BLANK(s, "", f(sh1, inst, 'u')) ;
}) ;
MC sh1("sh1", [](char s){
  BLANK(s, "<<<", sh2) ;
}) ;
MC sh2("sh2", [](char s){
  SYM(s, 'D', ">>>>", sh3) ;
  NOT(s, 'D', "",     inst) ;
}) ;
MC sh3("sh3", [](char s){
  SYM(s, 'C', ">>", sh4) ;
  NOT(s, 'C', "",  inst) ;
}) ;
MC sh4("sh4", [](char s){
  SYM(s, 'C', ">>", sh5) ;
  NOT(s, 'C', "",   pe2(inst, '0', ':')) ;
}) ;
MC sh5("sh5", [](char s){
  SYM(s, 'C', "", inst) ;
  NOT(s, 'C', "", pe2(inst, '1', ':')) ;
}) ;


// page 160
MC inst("inst", [](char s){
  BLANK(s, "", g_2(l(inst1), 'u')) ;
}) ;
MC inst1("inst1", [](char s){
  SYM(s, 'L', "> ", ce5(ov, 'v', 'y', 'x', 'u', 'w')) ;
  SYM(s, 'R', "> ", ce5(ov, 'v', 'x', 'u', 'y', 'w')) ;
  SYM(s, 'N', "> ", ce5(ov, 'v', 'x', 'y', 'u', 'w')) ;
}) ;

MC ov("ov", [](char s){
  BLANK(s, "", e_1(anf)) ;
}) ;

/*
                 
-- page 160
inst  = "inst"  ==> [Blank          []                      $ g'2 (l (inst1), "u")]

inst1 = "inst1" ==> [Sym "L"        [R, E]                  $ ce5 (ov, "v", "y", "x", "u", "w"),
                     Sym "R"        [R, E]                  $ ce5 (ov, "v", "x", "u", "y", "w"),
                     Sym "N"        [R, E]                  $ ce5 (ov, "v", "x", "y", "u", "w")]
                     
ov    = "ov"    ==> [Blank          []                      $ e'1 (anf)]

 */


} ;
