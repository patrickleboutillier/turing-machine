module Machines.TATp84 where

import Turing.MConfig
import Turing.Machine


b = "b" ==> [None     [P "0"]         b,  
             Sym "0"  [R, R, P "1"]   b,
             Sym "1"  [R, R, P "0"]   b]

m = newTM b
