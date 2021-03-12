module Turing.Machine.U (u) where

import Turing.MConfig
import Turing.MFuncLib
import Turing.Machine


-- The domain for universal Turing machines, page 151
dom = [" ", "0", "1", "D", "A", "C", "u", "v", "w", "x", "y", "z", ":", "L", "R", "N", ";", "::", "e"]


u :: Machine -> Machine
u m = newTMM dom b m


-- page 153
b  = "b"        ==> [Blank          []                      $ f (b1, b1, "::")]
b1 = "b1"       ==> [Blank          [R, R, P ":", R, R,
                                     P "D", R, R, P "A"]    $ anf]

-- page 154
anf  = "anf"    ==> [Blank          []                      $ g'2 dom (anf1, ":")]
anf1 = "anf1"   ==> [Blank          []                      $ con (kom, "y")]

kom  = "kom"    ==> [Sym ";"        [R, P "z", L]           $ con (kmp, "x"),
                     Sym "z"        [L, L]                  $ kom,
                     Sym "e"        []                      $ error "fail: machine is not well constructed",
                     NotOneOf [";", 
                        "z", "e"]   [L]                     $ kom,
                     None           [L]                     $ kom]

-- page 155
kmp = "kmp"     ==> [Blank          []                      $ cpe'4 dom (e'2 dom (e'2 dom (anf, "x"), "y"), sim, "x", "y")]


-- page 156
sim  = "sim"    ==> [Blank          []                      $ f' dom (sim1, sim1, "z" )]
sim1 = "sim1"   ==> [Blank          []                      $ con (sim2, blankSym)]

sim2 = "sim2"   ==> [Sym "A"        []                      $ sim3,
                     Not "A"        [L, P "u", R, R, R]     $ sim2]           

sim3 = "sim3"   ==> [Not "A"        [L, P "y"]              $ e'2 dom (mk, "z"),
                     Sym "A"        [L, P "y", R, R, R]     $ sim3]


-- page 157
mk  = "mk"      ==> [Blank          []                      $ g'2 dom (mk1, ":")]
mk1 = "mk1"     ==> [Not "A"        [R, R]                  $ mk1,
                     Sym "A"        [L, L, L, L]            $ mk2]

mk2 = "mk2"     ==> [Sym "C"        [R, P "x", L, L, L]     $ mk2,
                     Sym ":"        []                      $ mk4,
                     Sym "D"        [R, P "x", L, L, L]     $ mk3]

mk3 = "mk3"     ==> [Not ":"        [R, P "v", L, L, L]     $ mk3,
                     Sym ":"        []                      $ mk4] 

mk4 = "mk4"     ==> [Blank          []                      $ con (l (l (mk5)), " ")]

mk5 = "mk5"     ==> [Any            [R, P "w", R]           $ mk5,
                     None           [P ":"]                 $ sh]


-- page 159
sh = "sh"       ==> [Blank          []                      $ f (sh1, inst, "u")]
sh1 = "sh1"     ==> [Blank          [L, L, L]               $ sh2]
sh2 = "sh2"     ==> [Sym "D"        [R, R, R, R]            $ sh2,
                     Not "D"        []                      $ inst]
sh3 = "sh3"     ==> [Sym "C"        [R, R]                  $ sh4,
                     Not "C"        []                      $ inst]                        
sh4 = "sh4"     ==> [Sym "C"        [R, R]                  $ sh5,
                     Not "C"        []                      $ pe2 dom (inst, "0", ":")]  
sh5 = "sh5"     ==> [Sym "C"        []                      $ inst,
                     Not "C"        []                      $ pe2 dom (inst, "1", ":")]  
                 

-- page 160
inst = "inst"   ==> [Blank          []                      $ g'2 dom (l (inst1), "u")]

inst1 = "inst1" ==> [Sym "L"        [R, E]                  $ ce5 dom (ov, "v", "y", "x", "u", "w"),
                     Sym "R"        [R, E]                  $ ce5 dom (ov, "v", "x", "u", "y", "w"),
                     Sym "N"        [R, E]                  $ ce5 dom (ov, "v", "x", "y", "u", "w")]
                     
ov = "ov"       ==> [Blank          []                      $ e'1 dom (anf)]



{--

14. The Corrected Tables for U: Summary

The table for f(A, B, a) is unchanged on p. 63.
On p. 64, e(A, B, a) and e(B, a) are unchanged, but note that the state q used in the explanation of e(B, a) is a local notation, 
unrelated to the states of that name on p. 66.
On p. 65, pe(A, b), l(A), f'(A, B, a), and c(A, B, a) are unchanged, but r(A) and f''(A, B, a), defined on that page, are not used
 again.
On pp. 65–66, ce(A, B, a), ce(B, a), cp(A, B, C, a, b), cpe(A, B, C, a, b), and cpe(A, B, a, b) are unchanged but re(A, B, a, b), 
re(B, a, b), cr(A, B, a), and cr(B, a) are not used again.
On p. 66, q(A), pe2(A, a, b), and e(A) are unchanged. Also, ce2(B, a, b) and ce3(B, a, b, c) are defined, but it is ce5(B, a, b, c, d, e), 
derived in an analogous way, which is actually used, in the inst function.
On p. 70, con(A, a) is unchanged, but the remark that ‘C is left unmarked’ is confusing and is best ignored.

In the table for U, which begins on p. 70, the state b1 should have the following action: R, R, P :, R, R, PD, R, R, PA, R, R, PD, 
in order to print ": D A D" on the F squares, so that a blank symbol D is available for matching with an instruction.
On p. 70 the table for anf should lead to q(anf1, : ). If the set of instructions for the target machine T is deficient, so that a
state-symbol pair is created which has no matching instruction, machine U will attempt to search beyond the left-hand end of its tape. 
What happens then is undefined. To make it defiite, kom (p. 71) can be augmented by the line:
    kom e fail1,
which indicates the failure, and the last line will be:
    kom not z nor ; nor e kom

The table for kmp (p. 71) should read:
    kmp cpe(e(e(anf, x), y), sim, x, y),
since e(A, B, a) should return to anf, to restore the markings deleted by cpe.
On p. 71, sim2 with scanned symbol ‘not A’ should have the action L, Pu, R, R, R.

The first line of mk (p. 71) should lead to q(mk1, : ). On this same page, sh is unchanged.
On p. 72, inst should lead to q(l(inst1), u) and the line for inst1(N) should read
    inst1(N) ce5(ov, v, x, y, u, w)

The instruction for inst1(L) (p. 72) could try to move the target machine left beyond its end of tape, but there is no way for U to 
represent this condition, so T will seem not to move. To make this kind of error explicit, these changes can be made:
    inst1(L) f(inst4, fail2, x)
    inst4 ce5(ov, v, y, x, u, w)
To correct the fundamental flaw that a right movement inst1(R) (p. 72) could move the state-symbol to the right of all other symbols, 
making a future match with an instruction impossible, the following change is needed:
    inst1 (R) ce5(q(inst2, A), v, x, u, y, w)   finds the last A on the tape
    inst2 R, R inst3                            move to start of scanned symbol
    inst3 none PD ov                            n if blank space, print D
          D ov                                  but not if a symbol follows

Finally, ov (p. 72) is unchanged.

--}
