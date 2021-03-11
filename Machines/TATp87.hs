module Machines.TATp87 where

import Turing.MConfig
import Turing.Machine


dom = [" ", "0", "1", "e", "x"]

b = "b" ==> [Blank          [P "e", R, P "e", R, P "0", R, R, P "0", L, L]      o]
o = "o" ==> [Sym "1"        [R, P "x", L, L, L]                                 o,
             Sym "0"        []                                                  q]
q = "q" ==> [Not blankSym   [R, R]                                              q,
             None           [P "1", L]                                          p]
p = "p" ==> [Sym "x"        [E, R]                                              q,
             Sym "e"        [R]                                                 f,
             None           [L, L]                                              p]
f = "f" ==> [Not blankSym   [R, R]                                              f,
             None           [P "0", L, L]                                       o]

m = newTM dom b
